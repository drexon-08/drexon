
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd1, fd2, n;
    char sentence[1000];
    char buffer[500];

    // Open FIFO1 for writing
    fd1 = open("fifo1", O_WRONLY);

    printf("Enter sentences (type END to stop):\n");

    while (1)
    {
        fgets(sentence, sizeof(sentence), stdin);

        // Send sentence to Process 2
        write(fd1, sentence, strlen(sentence));

        if (strcmp(sentence, "END\n") == 0 ||
            strcmp(sentence, "END") == 0)
            break;
    }

    close(fd1);

    // Open FIFO2 for reading
    fd2 = open("fifo2", O_RDONLY);

    printf("\nResult received from Process 2:\n");

    // Read and display result
    while ((n = read(fd2, buffer, sizeof(buffer))) > 0)
    {
        write(STDOUT_FILENO, buffer, n);
    }

    close(fd2);

    return 0;
}