#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int main()
{
    int fd1, fd2;
    char line[1000];
    char result[500];

    int characters = 0;
    int words = 0;
    int lines = 0;
    int in_word = 0;

    // Open FIFO1 for reading
    fd1 = open("fifo1", O_RDONLY);

    // Read sentences from Process 1
    FILE *input = fdopen(fd1, "r");

    while (fgets(line, sizeof(line), input) != NULL)
    {
        // Stop when END is received
        if (strcmp(line, "END\n") == 0 ||
            strcmp(line, "END") == 0)
            break;

        lines++;

        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] != '\n')
                characters++;

            if (isspace((unsigned char)line[i]))
            {
                in_word = 0;
            }
            else if (in_word == 0)
            {
                words++;
                in_word = 1;
            }
        }
    }

    fclose(input);

    // Write result into text file
    FILE *file = fopen("result.txt", "w");

    fprintf(file, "Number of characters = %d\n", characters);
    fprintf(file, "Number of words = %d\n", words);
    fprintf(file, "Number of lines = %d\n", lines);

    fclose(file);

    // Read contents of result.txt
    file = fopen("result.txt", "r");

    int size = fread(result, 1, sizeof(result), file);

    fclose(file);

    // Open FIFO2 for writing
    fd2 = open("fifo2", O_WRONLY);

    // Send result to Process 1
    write(fd2, result, size);

    close(fd2);

    return 0;
}