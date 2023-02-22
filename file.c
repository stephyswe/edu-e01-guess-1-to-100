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

FileData readFile(char *filename)
{
    // Read file
    FileData fdata;

    // check if file exists
    createFileWithEmptyRow(filename);

    // Open file
    fdata.file_ptr = fopen(filename, "r");

    // Return file data
    return fdata;
}

FileData writeFile(char *filename)
{
    // Read file
    FileData fdata;

    // check if file exists
    createFileWithEmptyRow(filename);

    // Open file
    fdata.file_ptr = fopen(filename, "w");

    // Return file data
    return fdata;
}

void scoreToFile(int write_line, Player player)
{
    // store the filename and temp filename
    char temp_filename[FILENAME_SIZE];

    // newline will store the new line of text to be written to the file
    char newline[MAX_LINE];

    // we'll keep reading the file so long as keep_reading is true
    bool keep_reading = true;

    // will keep track of the current line number we are reading from the file
    int current_line = 1;

    // cast integer player_value to string newline
    // ensures that the destination buffer is not overflowed
    snprintf(newline, MAX_LINE, "%s %s %d", player.date, player.name, player.points);

    // time_t - use a unique temporary file name for each run, for example by using a timestamp
    // snprintf will write the string "temp____" followed by the filename to
    // ensures that the destination buffer is not overflowed
    time_t t = time(NULL);
    snprintf(temp_filename, FILENAME_SIZE, "temp_%ld.txt", t);

    // flush stdin to get the \n char from the last scanf out, otherwise the
    // below fgets will 'fail' as it will immediately encounter a newline
    fflush(stdin);

    // open the original file for reading, and the temp file for writing
    FileData file = readFile(FILE_SCORE);
    FileData temp = writeFile(temp_filename);

    do
    {
        // read the next line of the file into the buffer
        fgets(file.file_row, MAX_LINE, file.file_ptr);
        // if we've reached the end of the file, stop reading
        if (feof(file.file_ptr) || current_line == 5)
        {
            // Scenario: empty row - fprintf() allows to write new line on same row
            if (current_line == write_line)
                fprintf(temp.file_ptr, "%s\n", newline);

            // stop reading
            keep_reading = false;
        }

        // scenario: found row - fprintf() allows to write new line on same row
        else if (current_line == write_line)
            fprintf(temp.file_ptr, "%s\n%s%s", newline, file.file_row, "\n");

        // scenario: same row
        else
            fputs(file.file_row, temp.file_ptr);

        // increment the current line as we will now be reading the next line
        current_line++;

    } while (keep_reading);

    // close our access to both files as we are done with them
    fclose(file.file_ptr);
    fclose(temp.file_ptr);

    // delete the original file, rename temp file to the original file's name
    remove(FILE_SCORE);
    rename(temp_filename, FILE_SCORE);
}
