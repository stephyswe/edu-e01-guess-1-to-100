#include <stdio.h>

#ifndef PLAYER_H
#define PLAYER_H

// Function: Player
// Description: date, name and points
typedef struct
{
    // Player date
    char date[20];

    // Player name
    char name[20];

    // Player points
    int points;
} Player;

#endif