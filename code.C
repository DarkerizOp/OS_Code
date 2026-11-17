
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MSG_SIZE 256

/* Write exactly the requested number of bytes. */
int write_full(int fd, const void *buffer, size_t size)
{
    const char *ptr = buffer;
    size_t total = 0;

    while (total < size)
    {
        ssize_t n = write(fd, ptr + total, size - total);

        if (n < 0)
        {
            if (errno == EINTR)
                continue;

            return -1;
        }

        if (n == 0)
            return -1;

        total += (size_t)n;
    }

    return 0;
}

/* Return 1 on success, 0 on EOF, -1 on error. */
int read_full(int fd, void *buffer, size_t size)
{
    char *ptr = buffer;
    size_t total = 0;

    while (total < size)
    {
        ssize_t n = read(fd, ptr + total, size - total);

        if (n == 0)
        {
            return (total == 0) ? 0 : -1;
        }

        if (n < 0)
        {
            if (errno == EINTR)
                continue;

            return -1;
        }

        total += (size_t)n;
    }

    return 1;
}

/* Read a message from the terminal. */
void get_message(const char *prompt, char *message)
{
    printf("%s", prompt);
    fflush(stdout);

    if (fgets(message, MSG_SIZE, stdin) == NULL)
    {
        snprintf(message, MSG_SIZE, "quit");
        return;
    }

    size_t len = strcspn(message, "\n");

    if (message[len] == '\n')
    {
        message[len] = '\0';
    }
    else
    {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            /* Discard remaining input characters. */
        }
    }
}

int main(void)
{
    int pipe_ab[2];
    int pipe_ba[2];

    pid_t pid;

    char message[MSG_SIZE];

    /* Pipe 1: User A to User B. */
    if (pipe(pipe_ab) == -1)
    {
        perror("Pipe A-to-B creation failed");
        return EXIT_FAILURE;
    }

    /* Pipe 2: User B to User A. */
    if (pipe(pipe_ba) == -1)
    {
        perror("Pipe B-to-A creation failed");
        close(pipe_ab[0]);
        close(pipe_ab[1]);
        return EXIT_FAILURE;
    }

    /* Create the child process. */
    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");

        close(pipe_ab[0]);
        close(pipe_ab[1]);
        close(pipe_ba[0]);
        close(pipe_ba[1]);

        return EXIT_FAILURE;
    }

    /* ---------------- CHILD PROCESS ---------------- */

    if (pid == 0)
    {
        /* Child does not write to Pipe 1. */
        close(pipe_ab[1]);

        /* Child does not read from Pipe 2. */
        close(pipe_ba[0]);

        while (1)
        {
            int result = read_full(
                pipe_ab[0], message, sizeof(message)
            );

            if (result == 0)
                break;

            if (result == -1)
            {
                perror("User B read failed");
                close(pipe_ab[0]);
                close(pipe_ba[1]);
                _exit(EXIT_FAILURE);
            }

            message[MSG_SIZE - 1] = '\0';

            printf("\nUser B received: %s\n", message);

            if (strcmp(message, "quit") == 0)
                break;

            get_message("User B: ", message);

            if (write_full(
                    pipe_ba[1], message, sizeof(message)) == -1)
            {
                perror("User B write failed");
                close(pipe_ab[0]);
                close(pipe_ba[1]);
                _exit(EXIT_FAILURE);
            }

            if (strcmp(message, "quit") == 0)
                break;
        }

        close(pipe_ab[0]);
        close(pipe_ba[1]);

        printf("User B: Communication ended.\n");
        fflush(stdout);

        _exit(EXIT_SUCCESS);
    }

    /* ---------------- PARENT PROCESS ---------------- */

    /* Parent does not read from Pipe 1. */
    close(pipe_ab[0]);

    /* Parent does not write to Pipe 2. */
    close(pipe_ba[1]);

    printf("====================================\n");
    printf("   ANONYMOUS PIPE COMMUNICATION\n");
    printf("====================================\n");
    printf("User A (Parent) is ready.\n");
    printf("Type 'quit' to terminate.\n");

    while (1)
    {
        get_message("\nUser A: ", message);

        /* Send message to User B. */
        if (write_full(
                pipe_ab[1], message, sizeof(message)) == -1)
        {
            perror("User A write failed");
            break;
        }

        if (strcmp(message, "quit") == 0)
            break;

        /* Receive reply from User B. */
        int result = read_full(
            pipe_ba[0], message, sizeof(message)
        );

        if (result == 0)
        {
            printf("User B closed the communication.\n");
            break;
        }

        if (result == -1)
        {
            perror("User A read failed");
            break;
        }

        message[MSG_SIZE - 1] = '\0';

        printf("User A received: %s\n", message);

        if (strcmp(message, "quit") == 0)
            break;
    }

    /* Close parent's file descriptors. */
    close(pipe_ab[1]);
    close(pipe_ba[0]);

    /* Wait for child termination. */
    int status;

    while (waitpid(pid, &status, 0) == -1)
    {
        if (errno == EINTR)
            continue;

        perror("waitpid failed");
        return EXIT_FAILURE;
    }

    if (WIFEXITED(status))
    {
        printf("\nChild exit status: %d\n",
               WEXITSTATUS(status));
    }
    else
    {
        printf("\nChild terminated abnormally.\n");
    }

    printf("Anonymous Pipe communication completed.\n");

    return EXIT_SUCCESS;
}
