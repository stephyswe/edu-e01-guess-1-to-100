#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Player.h"
#include "common.h"

// struct playerAdd
// Description: Struct for player with date
// Parameters: int numberOfGuesses
// Returns: struct Player
// Side-effects: None
// Error-handling: None
// Status: 'Working'
Player playerAdd(int points)
{
    // string
    char *strTypeName = "Ange ditt namn: ";
    // Create player struct
    Player player;

    // set name by user input
    printf(strTypeName);
    scanf("%s", player.name);

    // Get current date
    strcpy(player.date, getCurrentDate());

    // Set points
    player.points = points;

    // Return player
    return player;
};