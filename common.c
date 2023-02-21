#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int getRandomNumber()
{
    // variables
    int number;

    // Seed random number generator
    srand(time(NULL));

    // Get random number
    number = rand() % 100 + 1;

    // return number
    return number;
}

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