#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 128

//wrap a file method --HERE--

int main(int argc, char **argv)
{
    int input_fd = -1;
    struct stat input_stats;
    int outout_fd = -1;
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
        char *path;
        *path = argv[2];
        // read from a file code
        stat(path, &input_stats);
        // Check for file existence
        if (input_stats.st_mode & F_OK)
        {
            if (S_ISDIR(input_stats.st_mode))
            {
                input_fd = opendir(path);
            }
            else
            {
                input_fd = opend(path, O_RDONLY);
            }
        }
        else
        {
            perror("Input file does not exist");
            return EXIT_FAILURE;
        }
    }
    else
        input_fd = STDIN_FILENO; //this means we are reading from standard input

    //check file or directory
    if(S_ISDIR(input_fd))
    {
        while ()
    }
    else
    {
        ..
    }

    //read & add to a data structure

    //write to wrap.*
    
    if(input_fd != STDIN_FILENO)
        close(input_fd);
    return 0;
}