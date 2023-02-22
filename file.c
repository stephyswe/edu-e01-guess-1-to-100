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

// define constants
#define FILENAME_SIZE 1024
#define MAX_LINE 2048
#define FILE_SCORE "scoreboard.txt"

FileData readFile()
{
    // Read file
    FileData fdata;

    // Open file
    fdata.file_ptr = fopen(FILE_SCORE, "r");

    // Return file data
    return fdata;
}

void createFileWithEmptyRow(char *filename)
{
    if (access(filename, F_OK) == -1)
    {
        FILE *file_ptr = fopen(filename, "w");
        if (file_ptr == NULL)
        {
            printf("Error creating file");
            exit(1);
        }
        fclose(file_ptr);
    }
}

void scoreToFile(int write_line, Player player)
{
    // file pointers for the original file and temp file
    FILE *file, *temp;

    // store the filename and temp filename
    char filename[FILENAME_SIZE] = FILE_SCORE;
    char temp_filename[FILENAME_SIZE];

    // buffer will store each line from the original file
    char buffer[MAX_LINE];

    // newline will store the new line of text to be written to the file
    char newline[MAX_LINE];

    // cast integer player_value to string newline
    sprintf(newline, "%s %s %d", player.date, player.name, player.points);

    // we'll make a temp file with "temp__filename" format
    strcpy(temp_filename, "temp____");

    // append the original filename to the temp filename
    strcat(temp_filename, filename);

    // flush stdin to get the \n char from the last scanf out, otherwise the
    // below fgets will 'fail' as it will immediately encounter a newline
    fflush(stdin);

    // check if file exists
    createFileWithEmptyRow(FILE_SCORE);

    // open the original file for reading, and the temp file for writing
    file = fopen(filename, "r");
    temp = fopen(temp_filename, "w");

    // we'll keep reading the file so long as keep_reading is true
    bool keep_reading = true;

    // will keep track of the current line number we are reading from the file
    int current_line = 1;

    do
    {
        // read the next line of the file into the buffer
        fgets(buffer, MAX_LINE, file);
        // if we've reached the end of the file, stop reading
        if (feof(file) || current_line == 5)
        {
            // Scenario: empty row
            if (current_line == write_line)
            {
                fputs(newline, temp);
                fputs("\n", temp);
            }

            // stop reading
            keep_reading = false;
        }

        // scenario: found row
        else if (current_line == write_line)
        {
            fputs(newline, temp);
            fputs("\n", temp);
            fputs(buffer, temp);
        }
        // scenario: same row
        else
            fputs(buffer, temp);

        // increment the current line as we will now be reading the next line
        current_line++;

    } while (keep_reading);

    // close our access to both files as we are done with them
    fclose(file);
    fclose(temp);

    // delete the original file, rename temp file to the original file's name
    remove(filename);
    rename(temp_filename, filename);
}
