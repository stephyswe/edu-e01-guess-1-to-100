#include <stdio.h>
#include <stdlib.h>

#include "FileData.h"
#include "Player.h"

void checkFileExist(FILE *file_ptr);
FileData readFile();
void scoreToFile(int write_line, Player player);