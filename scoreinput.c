#include <stdio.h>
#include <stdbool.h>

#include "Score.h"

// Function: scoreAdd
// Description: Adds score
// Parameters: int tries, int row
// Returns: struct Score
// Side-effects: None
// Error-handling: None
// Status: 'Working'
Score scoreAdd(int tries, int row) {

    // Create score struct
    Score score;

    // Set score
    score.isHighScore = true;

    // Set points
    score.points = tries;

    // Set row
    score.row = row;

    // Return score
    return score;
}