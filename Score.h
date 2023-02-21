#include <stdio.h>
#include <stdbool.h>

#ifndef SCORE_H
#define SCORE_H

// Function: Struct Score
// Description: Struct for score
// Parameters: None
// Returns: None
// Side-effects: None
// Error-handling: None
// Status: 'Working'
typedef struct
{
    // Score isHighScore
    bool isHighScore;

    // Score points
    int points;

    // Score row
    int row;
} Score;

#endif