Connor Lum
ckl55

David Halim
dbh72

Our testing strategy first looked at whether or not the code was able to print the text within the word width limit and standardized white space. We also tested specific cases where the buffer cut off in the middle of a word. We called the code using a file as well as on a directory, and checked the files to see if they had the right spacing and width. The directory had a subdirectory as well as an empty file. We tested with a word greater than the word width to make sure it returned a failure after finishing, as well as on input with only one word.