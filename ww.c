#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 128
#define TRUE 1
#define FALSE 0

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

int wrapfile(int input_file, int output_file, int width) {
	char buffer[BUFFER_SIZE];
	int bufferOffset = 0, currLineLength = 0, currWordLength = 0;
	int whitespaceSequence = FALSE, newLineSequence = FALSE;

	while (read(input_file, buffer, BUFFER_SIZE) != 0) { //Keeps reading until no input is left
		for (int x = 0; x < BUFFER_SIZE, x++) {
			if (buffer[x] != ' ' && buffer[x] != '\n' && buffer[x] != '\t') {  //Checks for non whitespace character
				if (currWordLength != 0){ //Occurs when the first letter of the next word is found
					if (currWordLength + currLineLength <= width) {
						if ()
						write(output_file, buffer + bufferOffset, currWordLength);
					}


					currWordLength = 0;
				}
			}
			else {
				if (!whitespaceSequence) {
					currWordLength = x - bufferOffset + 1;
				}
			}

		}
	}
}
