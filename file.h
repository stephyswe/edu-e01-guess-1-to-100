#include <stdio.h>
#include <stdlib.h>

// struct files
#include "FileData.h"
#include "Player.h"

// Function: checkFileExist
// Description: Checks if the file exists
// Parameters: FILE *file_ptr
void checkFileExist(FILE *file_ptr);

// Function: readFile
// Description: Reads the file and returns the data
// Returns: FileData file_data
FileData readFile();

// Function: scoreToFile
// Description: Writes the score to the file
// Parameters: int write_line, Player player
void scoreToFile(int write_line, Player player);