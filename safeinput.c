#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


bool checkInteger(char *input) {
    // variables
    int length = strlen(input);
    int i;
    bool is_integer = true;

    // loop through input
    for (i = 0; i < length; i++) {

        // check if input is integer
        if (!isdigit(input[i])) {

            // check if input is newline or null
            if (input[i] == '\n' || input[i] == '\0') {
                break;
            }

            // input is not integer
            is_integer = false;
            break;
        }
    }
    return is_integer;
}

// Function: isWithinRange
// Description: Checks if number is within range
// Parameters: int num
// Returns: bool
// Side-effects: None
// Error-handling: None
// Status: 'Working'
bool isWithinRange(int num) {
    if (num >= 1 && num <= 100)
        return true;
    else
        return false; 
}

// Function handlePrompt
// Description: Prompts user for input
// Parameters: char* prompt, int tries
// Returns: int number
// Side-effects: None
// Error-handling: None
// Status: 'Working'
int handlePrompt(char *prompt, int tries)
{
    // variables
    int number;
    char inputBuffer[100];

    // error messages
    char *strErrorDefaultMsg = "Ogiltig inmatning, försök igen\n";
    char *strErrorNumberMsg = "Ogiltigt nummer, måste vara 1 - 100, försök igen\n";

    while (true) {
        printf(prompt, tries);
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
            printf("Error reading input\n");
            exit(1);
        }

        int inputValue = atoi(inputBuffer);
        bool isValidInput = checkInteger(inputBuffer) && isWithinRange(inputValue);

        if (isValidInput) {
            number = inputValue;
            break;
        } else if (isWithinRange(inputValue)) {
            printf(strErrorDefaultMsg);
        } else {
            printf(strErrorNumberMsg);
        }
    }
    return number;
}