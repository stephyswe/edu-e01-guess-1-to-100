#include <stdio.h>
#include <stdlib.h>

// struct files
#include "FileData.h"
#include "Player.h"

#ifndef FILE_H
#define FILE_H

#define FILE_SCORE "scoreboard.txt"

#endif /* FILE_H */

// Function: useFile
// Description: use the file and returns the data
// Parameters: char filename, char mode
// Returns: FileData file_data
FileData useFile(char *filename, char *mode);

// Function: scoreToFile
// Description: Writes the score to the file
// Parameters: int write_line, Player player
void scoreToFile(int write_line, Player player);