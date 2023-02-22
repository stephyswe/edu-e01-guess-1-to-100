#include <stdio.h>

#ifndef FILEDATA_H
#define FILEDATA_H

// Struct: FileData
// Description: file pointer and file name
typedef struct
{
    // File data
    FILE *file_ptr;

    // File name
    char file_name[256];
} FileData;

#endif