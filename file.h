#include <stdio.h>
#include <stdlib.h>

// struct files
#include "FileData.h"
#include "Player.h"

// Function: readFile
// Description: Reads the file and returns the data
// Returns: FileData file_data
FileData readFile();

// Function: scoreToFile
// Description: Writes the score to the file
// Parameters: int write_line, Player player
void scoreToFile(int write_line, Player player);