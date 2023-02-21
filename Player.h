#include <stdio.h>

// struct player
// Description: Struct for player with date
// Parameters: none
// Returns: struct Player
// Side-effects: None
// Error-handling: None
// Status: 'Working'
typedef struct
{
    // Player date
    char date[20];

    // Player name
    char name[20];

    // Player points
    int points;
} Player;