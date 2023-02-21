#include "prompt.h"
#include "date.h"
#include "file.h"
#include "scoreinput.h"
#include "playerinput.h"

#include "FileData.h"
#include "Player.h"
#include "Score.h"

// menu options
#define OPTION_PLAY_AGAIN 1
#define OPTION_EXIT 2
#define OPTION_VIEW_SCOREBOARD 3

// Info in README.me

// Function: viewLowScoreboard
// Description: View lowscoreboard
// Parameters: None
// Returns: None
// Side-effects: None
// Error-handling: None
// Status: 'Working'
void viewLowScoreboard()
{
    // Read file
    FileData fdata = readFile();

    // Loop through file
    while (fgets(fdata.file_name, 60, fdata.file_ptr) != NULL)
    {
        // Print file row
        printf("%s", fdata.file_name);
    }

    // Close file
    fclose(fdata.file_ptr);
};

// Function: playGame
// Description: Plays a game of 'Guess the number'
// Parameters: None
// Returns: None
// Side-effects: None
// Error-handling: None
// Status: 'Working'
int playGame()
{
    // variables
    int number = 0;
    int guess = 0;
    int tries = 1;
    bool win = false;

    // seed random number generator
    number = getRandomNumber();

    // strings
    char *strIntro = "Gissa ett tal mellan 1 och 100. \n";
    char *strHigher = "Talet är högre. \n";
    char *strLower = "Talet är lägre. \n";
    char *strCorrect = "Rätt! Du gissade rätt på %d försök.\n";
    char *strWrong = "Fel inmatning. Gissa ett tal mellan 1 och 100. Försök igen: ";
    char *strGuess = "Gissning %d: ";

    // intro
    printf(strIntro);

    // while loop to check if guess is correct
    while (win == false)
    {
        // checks if guess is between 1 and 100 and if it is an integer
        guess = handlePrompt(strGuess, tries);

        // check if guess is correct
        if (guess == number)
        {
            // print correct message
            printf(strCorrect, tries);

            // set win to true
            win = true;

            // break loop
            break;
        }

        // check if guess is higher than number
        else if (guess > number)
            // print lower message
            printf(strLower);

        // check if guess is lower than number
        else if (guess < number)
            // print higher message
            printf(strHigher);

        // increment tries
        tries++;
    }

    // return tries
    return tries;
}

// Function: playGameScore
// Description: Plays a game of 'Guess the number' and checks if score is highscore
// Parameters: None
// Returns: None
// Side-effects: None
// Error-handling: None
// Status: 'Working'
void playGameScore()
{
    // play Game - return tries
    int tries = playGame();

    // check if player score is less then in scoreboard
    Score score = scoreCheck(tries);

    // if yes, add to scoreboard
    if (score.isHighScore)
    {
        // create player object with name and date
        Player player = playerAdd(score.points);

        // add player score to scoreboard file according to row
        scoreToFile(score.row, player);
    }
}

// Function: menu
// Description: Menu function
// Parameters: None
// Returns: None
// Side-effects: None
// Error-handling: None
// Status: 'Working'
void menu()
{
    // variables
    int userChoice;

    // strings
    char *strMenu = "\n1. Spela igen \n2. Avsluta \n3. Se lowscore \nVälj: ";
    char *strError = "Fel inmatning. Försök igen.";

    do
    {
        // show the menu and get the user's choice
        userChoice = handleMenuPrompt(strMenu);

        // execute the chosen option
        switch (userChoice)
        {
        case OPTION_PLAY_AGAIN:
            // play game
            playGameScore();
            break;
        case OPTION_EXIT:
            // exit game
            exit(EXIT_SUCCESS);
            break;
        case OPTION_VIEW_SCOREBOARD:
            // view scoreboard
            viewLowScoreboard();
            break;
        default:
            // print error message
            fprintf(stderr, strError);
            break;
        }

        // print new line
        printf("\n");

    } while (userChoice != OPTION_EXIT);
}

// Function: main
// Description: Main function
// Parameters: None
// Returns: None
// Side-effects: None
// Error-handling: None
// Status: 'Working
void main()
{
    // play game
    playGameScore();

    // menu with options
    menu();
}
