#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int in, out;
    ssize_t nread;
    char block[1024];

    // Check arguments
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open source file
    in = open(argv[1], O_RDONLY);
    if (in == -1)
    {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open destination file
    out = open(argv[2],
               O_WRONLY | O_CREAT | O_TRUNC,
               0666);

    if (out == -1)
    {
        perror("Error opening destination file");
        close(in);
        exit(EXIT_FAILURE);
    }

    // Copy file contents
    while ((nread = read(in, block, sizeof(block))) > 0)
    {
        if (write(out, block, nread) != nread)
        {
            perror("Error writing file");
            close(in);
            close(out);
            exit(EXIT_FAILURE);
        }
    }

    // Check read error
    if (nread == -1)
    {
        perror("Error reading file");
    }

    // Close files
    close(in);
    close(out);

    return 0;
}
