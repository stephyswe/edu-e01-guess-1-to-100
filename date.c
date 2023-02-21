#include <stdio.h>
#include <string.h>
#include <time.h>

// Function: getCurrentDate
// Description: Returns the current date and time as a string
// Parameters: None
// Returns: char *date
// Side-effects: None
// Error-handling: None
// Status: 'Working'
char *getCurrentDate()
{
    // Get current date and time
    time_t current_time = time(NULL);

    // Convert to local time format and print to stdout
    struct tm *local_time = localtime(&current_time);

    // Format date and time
    char buffer[100];

    // Date
    static char date[11];

    // Format date and time
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", local_time);

    // Copy buffer to date
    strcpy(date, buffer);

    // Return date
    return date;
}