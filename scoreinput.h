#include <stdio.h>
#include <stdlib.h>

// struct files
#include "Score.h"

// Function: scoreAdd
// Description: Adds score
// Parameters: int tries, int row
// Returns: struct Score
Score scoreAdd(int tries, int row);

// Function: scoreCheck
// Description: Checks if score is highscore
// Parameters: int tries
// Returns: struct Score
Score scoreCheck(int tries);