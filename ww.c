#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

int main(int argc, char **argv)
{
    int input_fd = 0;
    if (argc < 2)
    {
        perror("Too few arguments");
        return EXIT_FAILURE;
    }
    if (argc > 3)
    {
        perror("Too many arguments");
        return EXIT_FAILURE;
    }
    if (argc == 3)
    {
        if (!(input_fd = open(argv[2],'r')))
        {
            perror("Input file does not exist");
            return EXIT_FAILURE;
        }
    }
    else
        input_fd = -1;
    
    if(input_fd != -1)
        close(input_fd);
    return 0;
}