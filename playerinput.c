#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// struct files
#include "Player.h"

// header files
#include "common.h"

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