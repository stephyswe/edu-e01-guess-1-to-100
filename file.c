#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileData.h"

#define FILE_SCORE "score.txt"

extern int errno;

void checkFileExist(FILE *file_ptr)
{
    // Error number
    int errnum;

    // Check if file exists
    char there_was_error = 0;
    char opened_in_read  = 1;

     // strings
    char answer[8];
    char *strIntro = "Vill du skapa en ny fil (score.txt)? (Ja/Nej): ";
    char *strYes = "Ja";
    char *strNo = "Nej";

    // Check if file exists
    if (file_ptr == NULL)
    {
        // Get error number
        errnum = errno;

        // Print error message
        fprintf(stderr, "Value of errno: %d\n", errno);

        // Print error message
        perror("Error printed by perror");

        // Print error message
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));

        // Print error message
        printf("Error opening file %s \n", file_ptr);

        // Ask user if they want to create a new file
        printf("Do you want to create a new file? (Ja/Nej) \n");

        // loop while answer is not "Ja" or "Nej"
        while (scanf(" %s", &answer) == 1 && strcmp(answer, strYes) != 0) {
             if (strcmp(answer, strYes) == 0){

                // create file
                file_ptr = fopen(FILE_SCORE, "r");

                // Check if file exists. if Not set there_was_error to 1
                if (file_ptr == NULL)
                    there_was_error = 1;
            }
            else if (strcmp(answer, strNo) == 0){
                // Exit program
                exit(EXIT_FAILURE);
            }
            else{
                printf("Felaktig inmatning. Försök igen. \n");
        }
        }

        // Check if there was an error
        if (there_was_error)
        {
            // Print error message
            printf("Disc full or no permission\n");

            // Exit program
            exit(EXIT_FAILURE);
        }

        // Check if file was opened in read mode
        else
            // Print success message
            printf("The file %s was created successfully. \n", FILE_SCORE);
    }
}

// Function: readFile
// Description: Reads file
// Parameters: None
// Returns: struct FileData
// Side-effects: None
// Error-handling: None
// Status: 'Working'
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