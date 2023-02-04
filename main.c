#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Uppgift 1. Gissa talet - Godkänt kritierium
** Innehåller **
- Funktioner (3)
- While-loopar (2)
- If-satser (2)
- Slumptal (1)
- Strängar (2)
- Inmatning (2)
- Inmatningskontroll (1)
** Funktioner (3) **

- main - main function
- playGame - plays a game of 'Guess the number'
- handlePrompt - handles the prompt for the user

** While-loopar (2) **
- main - while loop to check value of playAgain
- playGame - while loop to check if user input is correct

** If-satser (2) **
- main - if statement to check if user input is "Ja"
- main - if statement to check if user input is "Nej"

** Slumptal (1) **
- playGame - generates a random number

** Strängar (2) **
- main - string to ask user if they wanna play again or not
- main - string to check if user input is "Ja"
- main - string to check if user input is "Nej"

** Inmatning (2) **
- main - scanf to get user input
- playGame - scanf to get user input

** Inmatningskontroll (1) **
- playGame - while loop to check if user input is correct

** Beskrivning **
Programmet ska spela spelet "Gissa talet" med användaren. Spelet går ut på att användaren ska gissa ett tal mellan 1 och 100.
Programmet ska välja ett slumptal och sedan låta användaren gissa vilket tal det är. Efter varje gissning ska programmet ge en ledtråd om talet är större eller mindre.
När användaren gissar rätt ska programmet visa hur många gissningar det tog och fråga om användaren vill spela igen.

** Exempel Instruktioner **
Gissa ett tal mellan 1 och 100.
Gissning 1: 50
Talet är lägre.
Gissning 2: 25
Talet är högre.
Gissning 3: 37
Talet är högre.
Gissning 4: 43
Talet är högre.
Gissning 5: 47
Rätt! Du gissade rätt på 5 försök.
Vill du spela igen? (Ja/Nej):

** Kravspecifikation **

• Programmet ska använda de texter som finns i exemplet ovan.
- Kommentar: Texter sparas som chars (stringtecken). 

• Programmet ska välja olika slumptal varje gång.
- Kommentar: Slumptal genereras med rand() och time().

• Slumptalet ska kunna vara alla tal från 1 till och med 100 men inte 0 och inte 101.
- Kommentar: Slumptalet genereras med rand() % 100 + 1.

• Skriver användaren in något som inte är ett tal ska de få uppmaningen att försöka igen tills de skriver in ett tal med siffror.
- Kommentar: Användaren får uppmaningen att försöka igen tills de skriver in ett tal med siffror.

• Programmet ska bara räkna gissningar som är heltal. I exemplet ovan skriver användaren ”Fyra” vilket inte är ett heltal och får då försöka igen.
- Kommentar: Programmet räknar bara gissningar som är heltal.

• Efter varje gissning ska en ledtråd visas om talet är större eller mindre.
- Kommentar: Ledtråd visas efter varje gissning.

• Gissar man rätt ska man få reda på hur många gissningar det tog och en fråga om man vill spela igen.
- Kommentar: "Rätt! Du gissade rätt på %d försök.\n" visas efter varje rätt gissning. 
    "Vill du spela igen? (Ja/Nej): " visas efter varje spel.

• Svara man Ja ska spelet starta om från början med ett helt nytt slumptal. Svara man Nej så avslutas programmet. 
    Vid alla andra svar ställs frågan om man vill spela om igen. 
- Kommentar: "Vill du spela igen? (Ja/Nej):" visas efter varje spel. Svarar användaren någonting annat än "Ja" eller "Nej" så ställs frågan igen.
*/

// Function: handlePrompt
// Description: Handles the prompt for the user
// Parameters: int tries
// Returns: int guess
// Side-effects: None
// Error-handling: None
// Status: 'Working'
int handlePrompt(int tries) {
    // Variables
    char *strGuess = "Gissning %d: ";
    char *strWrongDecimal = "Fel. Inmatningsvärdet har decimal. Försök igen.\n";
    char *strWrongType = "Fel. Inmatningsvärdet är varken heltal eller float. Försök igen.\n";
    char input[100];
    int guess = 0;
    int integer;
    bool has_decimal = false;
    bool isInteger = false;

    // loops until user input is correct
    while(!isInteger) {

        // resets variables
        has_decimal = false;

        // gets user input
        printf(strGuess, tries + 1);
        scanf("%s", input);

        // checks if number is an double by decimal point
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '.') {
            // printf("Decimal point found at position %d of the string
            has_decimal = true;
            break;
            }
        }

        // checks if number is an integer
        if (sscanf(input, "%d", &integer) == 1 && has_decimal) {

            // prints error message
            printf(strWrongDecimal);

        // checks if number is a float
        } else if (sscanf(input, "%d", &integer) == 1 && !has_decimal) {

            // sets isInteger to true
            isInteger = true;
        
        // prints error message
        } else {

            // prints error message
            printf(strWrongType);
        } 
    }

    // Converts string to int
    int x = atoi(input);

    // returns guess
    return x;
}

// Function: playGame
// Description: Plays a game of 'Guess the number'
// Parameters: None
// Returns: None
// Side-effects: None
// Error-handling: None
// Status: 'Working'
void playGame() {

    // Variables
    int number = 0;
    int guess = 0;
    int tries = 0;
    bool win = false;

    // seed random number generator
    srand(time(NULL));
    number = rand() % 100 + 1;

    // strings
    char *strIntro = "Gissa ett tal mellan 1 och 100. \n";
    char *strHigher = "Talet är högre. \n";
    char *strLower = "Talet är lägre. \n";
    char *strCorrect = "Rätt! Du gissade rätt på %d försök.\n";
    char *strWrong = "Fel inmatning. Gissa ett tal mellan 1 och 100. Försök igen: ";


    // prints intro
    printf(strIntro);

    // loops until user wins
    while(win == false){
        // guess a number between 1 and 100 tell if number is higher or lower

        // checks if guess is between 1 and 100 and if it is an integer
        guess = handlePrompt(tries);

        // increment tries
        tries++;

        // check if guess is correct
        if(guess == number){
            // prints correct message
            printf(strCorrect, tries);

            // sets win to true
            win = true;

        // check if guess is higher or lower than number
        }else if(guess > number){

            // prints lower message
            printf(strLower);

        // check if guess is higher or lower than number
        }else if(guess < number){

            // prints lower message
            printf(strHigher);
        }
    }
}

// Function: main
// Description: Main function
// Parameters: None
// Returns: None
// Side-effects: None
// Error-handling: None
// Status: 'Working
void main(){

    // Variables    
    bool playAgain = true;
    char answer[8];

    // strings
    char *strIntro = "Vill du spela igen? (Ja/Nej): ";
    char *strYes = "Ja";
    char *strNo = "Nej";

    // while loop to check value of playAgain
    while(playAgain){  
        // play game with random number
        playGame();

        // ask user if they wanna play again or not
        printf(strIntro);

        // while loop to check if user input is correct
        while (scanf(" %s", &answer) == 1 && strcmp(answer, strYes) != 0) {

            // check if user input is "Ja"
            if(strcmp(answer, strYes) == 0){

                // sets playAgain to true
                playAgain = true;
            }

            // check if user input is "Nej"
            else if (strcmp(answer, strNo) == 0){

                // sets playAgain to false
                playAgain = false;
                break;

            // if user input is not "Ja" or "Nej"
            } else {

                // prints intro message
                printf(strIntro);
            }
        }

        // prints new line
        printf("\n\n");
    }
}
