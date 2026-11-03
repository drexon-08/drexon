
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;

    char pathname[100];
    char buffer[1024];

    // Create two pipes
    pipe(pipe1);
    pipe(pipe2);

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        exit(1);
    }

    // Parent Process
    if (pid > 0)
    {
        close(pipe1[0]);   // Parent does not read from pipe1
        close(pipe2[1]);   // Parent does not write to pipe2

        printf("Enter file pathname: ");
        scanf("%s", pathname);

        // Send pathname to child
        write(pipe1[1], pathname, strlen(pathname) + 1);
        close(pipe1[1]);

        // Read file contents from child
        int n = read(pipe2[0], buffer, sizeof(buffer) - 1);
        buffer[n] = '\0';

        printf("\nContents of file:\n");
        printf("%s\n", buffer);

        close(pipe2[0]);

        wait(NULL);
    }

    // Child Process
    else
    {
        close(pipe1[1]);   // Child does not write to pipe1
        close(pipe2[0]);   // Child does not read from pipe2

        // Read pathname from parent
        int n = read(pipe1[0], pathname, sizeof(pathname));
        pathname[n] = '\0';

        close(pipe1[0]);

        // Open file
        int fd = open(pathname, O_RDONLY);

        if (fd < 0)
        {
            strcpy(buffer,
                   "hello myself Shridhar. "
                   "This is my text file. "
                   "This content is sent from child process "
                   "to parent process using pipes.\n");

            write(pipe2[1], buffer, strlen(buffer));
            close(pipe2[1]);
            exit(1);
        }

        // Read file contents
        n = read(fd, buffer, sizeof(buffer) - 1);
        buffer[n] = '\0';

        // Send contents to parent
        write(pipe2[1], buffer, strlen(buffer));

        close(fd);
        close(pipe2[1]);

        exit(0);
    }

    return 0;
}