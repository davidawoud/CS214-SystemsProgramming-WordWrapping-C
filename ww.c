#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#define BUFFER_SIZE 128
#define TRUE 1
#define FALSE 0

int wrapfile(int input_file, int output_file, int width) {
	char buffer[BUFFER_SIZE];
	int bufferOffset = 0, currLineLength = 0, currWordLength = 0;
	int failure = FALSE;
	int whitespaceSequence = FALSE, newLineCounter = 0;
    char *buffer_leftover;
    int buffer_leftover_size = 0;

	while (read(input_file, buffer, BUFFER_SIZE) != 0) { //Keeps reading until no input is left
        for (int x = 0; x < BUFFER_SIZE; x++) {
			if (!isspace(buffer[x])) {  //Checks for non whitespace character
				if (whitespaceSequence){ //Occurs when the first letter of the next word is found
					whitespaceSequence = FALSE;
					if (currWordLength + currLineLength < width) { //Checks to see if word fits
                        if (currLineLength != 0) { //If start of line, no space
							write(output_file, " " , 1);
                            currLineLength++;
						}
                        if (buffer_leftover_size != 0)
                        {
                            write(output_file, buffer_leftover, buffer_leftover_size);
                            free(buffer_leftover);
                            buffer_leftover = NULL;
                            buffer_leftover_size = 0;
                            write(output_file, buffer + bufferOffset, currWordLength - buffer_leftover_size);
                        }
                        else
                        {
                            write(output_file, buffer + bufferOffset, currWordLength);
                        }
                        currLineLength += currWordLength;
						currWordLength = 0;
						bufferOffset = x;
					}
					else
                    {
						if (currWordLength > width) {
                            write(output_file, "\n", 1);
							write(output_file, buffer + bufferOffset, currWordLength);
							failure = TRUE;
                            write(output_file, "\n", 1);
                            currWordLength = 0;
                            currLineLength = 0;

						}
						else
						{
							write(output_file, "\n", 1);
							write(output_file, buffer + bufferOffset, currWordLength);
                            currLineLength = currWordLength;
						}
						bufferOffset = x;
                        currWordLength = 0;
                    }

                    if (newLineCounter >= 2) { //If there are >2 \n, new line
						write(output_file,"\n\n", 2);
                        currLineLength = 0;
					}
                    newLineCounter = 0;
				}
				currWordLength++;
			}
			else { //Whitespace character
				if (!whitespaceSequence) { //End of word
					whitespaceSequence = TRUE;
				}
				if (buffer[x] == '\n') { //If there are two new line characters in one sequence, new paragraph
					newLineCounter++;
				}
			}
		}

        buffer_leftover_size = currWordLength;
        buffer_leftover = malloc(currWordLength * sizeof(char));
        for (int i = 0; i < buffer_leftover_size; i++)
        {
            *(buffer_leftover + (i*sizeof(char))) = buffer[bufferOffset];
            bufferOffset++;
        }
        bufferOffset = 0;
	}

    if (failure)
	    return EXIT_FAILURE;
    else
	    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    int wrapping_width = 0;
    char *path;
    int input_fd = -1;
    DIR * input_dir;
    struct stat input_stats;
    int output_fd = -1;
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
        wrapping_width = atoi(argv[1]);
        path = argv[2];
        // read from a file code
        stat(path, &input_stats);
        // Check for file existence
        if (input_stats.st_mode)
        {
            if (S_ISDIR(input_stats.st_mode))
            {
                input_dir = opendir(path);
            }
            else
            {
                input_fd = open(path, O_RDONLY);
                output_fd = STDOUT_FILENO; //this means we are writing to standard output
            }
        }
        else
        {
            //puts(input_stats.st_mode);
            perror("Input file does not exist");
            return EXIT_FAILURE;
        }
    }
    else
    {
        wrapping_width = atoi(argv[1]);
        input_fd = STDIN_FILENO; //this means we are reading from standard input
    }

    //check file or directory
    if(S_ISDIR(input_stats.st_mode))
    {
        struct dirent *de;
        de = readdir(input_dir);
        while (de != NULL)
        {
            char *file_name = de->d_name;
            if(!(file_name[0] == '.' || strncmp("wrap.", file_name, strlen("wrap.")) == 0))
            {
                int file_fd = open(path + '/' + *file_name, O_RDONLY);
                output_fd = open(path + '/wrap.' + *file_name, O_WRONLY|O_CREAT|O_TRUNC, 600);
                if(S_ISDIR(file_fd))
                {
                    de = readdir(input_dir);
                    continue;
                }
                wrapfile(file_fd, output_fd, wrapping_width);
            }

            de = readdir(input_dir);
        }
        closedir(input_dir);
    }
    else
    {
        wrapfile(input_fd, output_fd, wrapping_width);
    }
    
    if(input_fd != STDIN_FILENO)
        close(input_fd);
    return 0;
}
