#include <stdio.h>
#include <stdbool.h>

// struct files
#include "Score.h"
#include "FileData.h"

// header files
#include "file.h"

Score scoreAdd(int row)
{
    // Create score struct
    Score score;

    // Set score
    score.isHighScore = true;

    // Set row
    score.row = row;

    // Return score
    return score;
}

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
    char line[256];

    // loop through file
    while (fgets(fdata.file_name, sizeof(line), fdata.file_ptr) != NULL)
    {
        // get score from string
        sscanf(fdata.file_name, "%*s %*s %*s %d", &number);

        // if number is higher than tries, highscore found
        if (number > tries)
        {
            // High score found! create a new score.
            score = scoreAdd(row_line);
            break;
        }
        // add to rowline
        row_line++;
    }

    // count lines in file. If less than 6, add to last row
    if (row_line < 6 && score.isHighScore == false)
    {
        // create a new score
        score = scoreAdd(row_line);
    }

    // close file
    fclose(fdata.file_ptr);

    // return score
    return score;
}