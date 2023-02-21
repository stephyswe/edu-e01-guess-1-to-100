#include <stdio.h>

#ifndef FILEDATA_H
#define FILEDATA_H

// Function: Struct FileData
// Description: Struct for file data
// Parameters: None
// Returns: None
// Side-effects: None
// Error-handling: None
// Status: 'Working'
typedef struct
{
    // File data
    FILE *file_ptr;

    // File name
    char file_name[60];
} FileData;

#endif