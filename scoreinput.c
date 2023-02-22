#include <stdio.h>
#include <stdbool.h>

// struct files
#include "Score.h"
#include "FileData.h"

// header files
#include "file.h"

// Define variables
#define MAX_SCORES 6

Score scoreCheck(int tries)
{
    // Create score struct
    Score score;

    // Read file
    FileData fdata = readFile();

    // Set score
    score.isHighScore = false; // start as highscore false

    // Set rowline
    int row_line = 1;

    // variables
    int number;

    // loop through file
    while (fgets(fdata.file_name, sizeof(fdata.file_name), fdata.file_ptr) != NULL)
    {
        // try to get score from string
        if (sscanf(fdata.file_name, "%*s %*s %*s %d", &number) != 1)
        {
            // line doesn't match expected format, skip it
            continue;
        }

        // if number is higher than tries, highscore found
        if (number > tries)
        {
            // High score found! create a new score.
            score = (Score){.isHighScore = true, .row = row_line};
            break;
        }

        // add to rowline
        row_line++;
    }

    // count lines in file. If less than MAX_SCORES, add to last row
    if (row_line < MAX_SCORES && !score.isHighScore)
    {
        // create a new score
        score = (Score){.isHighScore = true, .row = row_line};
    }

    // close file
    fclose(fdata.file_ptr);

    // return score
    return score;
}