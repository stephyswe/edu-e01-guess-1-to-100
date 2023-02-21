#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>

// struct files
#include "FileData.h"
#include "Player.h"

// define constants
#define FILENAME_SIZE 1024
#define MAX_LINE 2048
#define FILE_SCORE "scoreboard.txt"

// error number
extern int errno;

void checkFileExist(FILE *file_ptr)
{
    // Error number
    int errnum;

    // Check if file exists
    char there_was_error = 0;
    char opened_in_read = 1;

    // strings
    char answer[8];
    char *strIntro = "Vill du skapa en ny fil (scoreboard.txt)? (Ja/Nej): ";

    char *strErrorValue = "Value of errno: %d\n";
    char *strErrorOpeningFile = "Error opening file: %s\n";
    char *strErrorPrinted = "Error printed by perror\n";
    char *strErrorOpening = "Error opening file: %s\n";
    char *strErrorDisc = "Disc full or no permission\n";

    char *strErrorInput = "Felaktig inmatning. Försök igen. \n";

    // strings file
    char *strFileSuccess = "The file %s was created successfully. \n";
    char *strYes = "Ja";
    char *strNo = "Nej";

    // Check if file exists
    if (file_ptr == NULL)
    {
        // Get error number
        errnum = errno;

        // Print error message
        fprintf(stderr, strErrorValue, errno);

        // Print error message
        perror(strErrorPrinted);

        // Print error message
        fprintf(stderr, strErrorOpeningFile, strerror(errnum));

        // Print error message
        printf(strErrorOpening, file_ptr);

        // Ask user if they want to create a new file
        printf(strIntro);

        // loop while answer is not "Ja" or "Nej"
        while (scanf(" %s", &answer) == 1 && strcmp(answer, strYes) != 0)
        {
            if (strcmp(answer, strYes) == 0)
            {

                // create file
                file_ptr = fopen(FILE_SCORE, "r");

                // Check if file exists. if Not set there_was_error to 1
                if (file_ptr == NULL)
                    there_was_error = 1;
            }
            else if (strcmp(answer, strNo) == 0)
            {
                // Exit program
                exit(EXIT_FAILURE);
            }
            else
            {
                printf(strErrorInput);
            }
        }

        // Check if there was an error
        if (there_was_error)
        {
            // Print error message
            printf(strErrorDisc);

            // Exit program
            exit(EXIT_FAILURE);
        }

        // Check if file was opened in read mode
        else
            // Print success message
            printf(strFileSuccess, FILE_SCORE);
    }
}

FileData readFile()
{
    // Read file
    FileData fdata;

    // Open file
    fdata.file_ptr = fopen(FILE_SCORE, "r");

    // Check if file exists
    checkFileExist(fdata.file_ptr);

    // Return file data
    return fdata;
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

    // open the original file for reading, and the temp file for writing
    file = fopen(filename, "r");
    temp = fopen(temp_filename, "w");

    // check if either file failed to open, if either did exit with error status
    // checkFileExist(file);
    checkFileExist(temp);

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

            // Scenario: File Empty

            // go to the end of the file
            fseek(file, 0, SEEK_END); // goto end of file

            // if the file is empty, write the new line to the file
            if (ftell(file) == 0)
            {
                fputs(newline, temp);
                fputs("\n", temp);
            }

            // Scenario: Line Empty
            else if (current_line == write_line)
            {
                fputs(newline, temp);
                fputs("\n", temp);
            }

            // Scenario: Line is greater than current line
            else if (write_line > current_line)
            {
                fputs(buffer, temp);
                fputs("\n", temp);
                fputs(newline, temp);
            }

            // stop reading
            keep_reading = false;
        }

        // scenario: write_line is same as current_line
        else if (current_line == write_line)
        {
            fputs(newline, temp);
            fputs("\n", temp);
            fputs(buffer, temp);
        }
        // otherwise write this line to the temp file
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
