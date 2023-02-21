#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Function handlePromptDefaultTwo
// Description: Prompts user for input
// Parameters: char* stringMessage, int tries
// Returns: int number
// Side-effects: None
// Error-handling: None
// Status: 'Working'
int handlePromptDefaultTwo(char *stringMessage, int tries)
{
   int number;
    char input[100];
    while (1) {
        printf(stringMessage, tries);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input\n");
            exit(1);
        }
        
        int length = strlen(input);
        int i, is_integer = 1;
        for (i = 0; i < length; i++) {
            if (!isdigit(input[i])) {
                if (input[i] == '\n' || input[i] == '\0') {
                    break;
                }
                is_integer = 0;
                break;
            }
        }
        if (is_integer) {
            number = atoi(input);
            break;
        }
        printf("Invalid input, try again\n");
    }
    return number;
}