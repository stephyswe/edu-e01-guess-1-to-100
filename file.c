#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>

// struct files
#include "FileData.h"
#include "Player.h"

// header files
#include "file.h"

// define constants
#define FILENAME_SIZE 1024
#define MAX_LINE 2048
#define MAX_LINES 5

void createFileWithEmptyRow(char *filename)
{
    // check if file exists
    if (access(filename, F_OK) == -1)
    {
        // create file
        FILE *file_ptr = fopen(filename, "w");

        // check if file is created
        if (file_ptr == NULL)
        {
            printf("Error creating file");
            exit(1);
        }

        // close file
        fclose(file_ptr);
    }
}

FileData useFile(char *filename, char *mode)
{
    // Read file
    FileData fdata;

    // check if file exists
    createFileWithEmptyRow(filename);

    // Open file
    fdata.file_ptr = fopen(filename, mode);

    // Return file data
    return fdata;
}

void scoreToFile(int line_to_write, Player player)
{
    // store the filename and temp filename
    char temp_filename[FILENAME_SIZE];

    // newline will store the new line of text to be written to the file
    char newline[MAX_LINE];

    // cast integer player_value to string newline
    // ensures that the destination buffer is not overflowed
    snprintf(newline, MAX_LINE, "%s %s %d", player.date, player.name, player.points);

    // create a temporary filename
    // snprintf will write the string "temp____" followed by the filename to
    // ensures that the destination buffer is not overflowed
    time_t t = time(NULL);
    snprintf(temp_filename, FILENAME_SIZE, "temp_%ld.txt", t);

    // open the original file for reading, and the temp file for writing
    FileData file = useFile(FILE_SCORE, "r");
    FileData temp = useFile(temp_filename, "w");

    // keep track of the current line number we are reading from the file
    int current_line = 1;

    // loop through each line in the file
    while (fgets(file.file_row, MAX_LINE, file.file_ptr))
    {
        // if we've reached the end of the file or the max number of lines, stop reading
        if (current_line == MAX_LINES || feof(file.file_ptr))
        {
            // scenario: empty row
            if (current_line == line_to_write)
                fprintf(temp.file_ptr, "%s\n", newline);
            // stop reading
            break;
        }

        // scenario: found row
        if (current_line == line_to_write)
            fprintf(temp.file_ptr, "%s\n%s", newline, file.file_row);
        // scenario: same row
        else
            fputs(file.file_row, temp.file_ptr);

        // increment the current line as we will now be reading the next line
        current_line++;
    }

    // close our access to both files as we are done with them
    fclose(file.file_ptr);
    fclose(temp.file_ptr);

    // delete the original file, rename temp file to the original file's name
    remove(FILE_SCORE);
    rename(temp_filename, FILE_SCORE);
}
