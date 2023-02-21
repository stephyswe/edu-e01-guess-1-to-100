#include <stdio.h>
#include <stdbool.h>

#ifndef SCORE_H
#define SCORE_H

// Struct: Score
// Description: confirm highscore and row
typedef struct
{
    // Score isHighScore
    bool isHighScore;

    // Score row
    int row;
} Score;

#endif