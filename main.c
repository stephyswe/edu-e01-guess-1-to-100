#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "safeinput.h" 
#include "date.h" 
#include "file.h"

#include "FileData.h"
#include "Player.h"
#include "score.h"

#define FILENAME_SIZE 1024
#define MAX_LINE 2048
#define BUF_SIZE 65536
#define FILE_SCORE "score.txt"

// Info in README.me

// Function: readFile
// Description: Reads file
// Parameters: None
// Returns: struct FileData
// Side-effects: None
// Error-handling: None
// Status: 'Working'
FileData readFile()
{
    // Read file
    FileData fdata;

    // Open file
    fdata.file_ptr = fopen(FILE_SCORE, "r");

    // Check if file exists
    checkFileExist(fdata.file_ptr);

    // Return file data
    return fdata;
}

// Function: writeFile
// Description: Writes to file
// Parameters: None
// Returns: struct FileData
// Side-effects: None
// Error-handling: None
// Status: 'Working'
FileData writeFile()
{
    // Write to file
    FileData fdata;

    // Open file
    fdata.file_ptr = fopen(FILE_SCORE, "w");

    // Check if file exists
    checkFileExist(fdata.file_ptr);

    // Return file data
    return fdata;
}

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


// struct playerAdd
// Description: Struct for player with date
// Parameters: int numberOfGuesses
// Returns: struct Player
// Side-effects: None
// Error-handling: None
// Status: 'Working'
Player playerAdd(int points)
{
    // Create player struct
    Player player;

    // Temporary name, date & points
    
    // set name by user input
    printf("Ange ditt namn: ");
    scanf("%s", player.name);

    // Get current date
    strcpy(player.date, getCurrentDate());

    // Set points
    player.points = points;

    // Return player
    return player;
};


// Function: scoreAdd
// Description: Adds score
// Parameters: int tries, int row
// Returns: struct Score
// Side-effects: None
// Error-handling: None
// Status: 'Working'
Score scoreAdd(int tries, int row) {

    // Create score struct
    Score score;

    // Set score
    score.isHighScore = true;

    // Set points
    score.points = tries;

    // Set row
    score.row = row;

    // Return score
    return score;
}

// Function: scoreCheck
// Description: Checks if score is highscore
// Parameters: int tries
// Returns: struct Score
// Side-effects: None
// Error-handling: None
// Status: 'Working'
Score scoreCheck(int tries)
{
    // Create score struct
    Score score;

    // Read file
    FileData fdata = readFile();

    // Set score
    score.isHighScore = false; // start as highscore false

    // Set rowline
    int row_line = 1;

    // variables
    int number;
    char line[256];

    // loop through file
    while (fgets(fdata.file_name, sizeof(line), fdata.file_ptr) != NULL)
    {
        // get score from string
        sscanf(fdata.file_name, "%*s %*s %*s %d", &number);

        // if number is higher than tries, highscore found
        if (number > tries)
        {
            // High score found! create a new score.
            score = scoreAdd(tries, row_line);
            break;
        }
        // add to rowline
        row_line++;
    }

    // count lines in file. If less than 6, add to last row
    if (row_line < 6 && score.isHighScore == false)
    {
        // create a new score
        score = scoreAdd(tries, row_line);
    }


    // close file
    fclose(fdata.file_ptr);

    // return score
    return score;
}

// Function: scoreToFile
// Description: Adds score to file
// Parameters: int write_line, struct Player player
// Returns: None
// Side-effects: None
// Error-handling: None
// Status: 'Working'
void scoreToFile(int write_line, Player player)
{
    // file pointers for the original file and temp file
    FILE *file, *temp;

    // store the filename and temp filename
    char filename[FILENAME_SIZE] = FILE_SCORE;
    char temp_filename[FILENAME_SIZE];

    // buffer will store each line from the original file
    char buffer[MAX_LINE];

    // newline will store the new line of text to be written to the file
    char newline[MAX_LINE];

    // cast integer player_value to string newline
    sprintf(newline, "%s %s %d", player.date, player.name, player.points);

    // we'll make a temp file with "temp__filename" format
    strcpy(temp_filename, "temp____");

    // append the original filename to the temp filename
    strcat(temp_filename, filename);

    // flush stdin to get the \n char from the last scanf out, otherwise the
    // below fgets will 'fail' as it will immediately encounter a newline
    fflush(stdin);

    // open the original file for reading, and the temp file for writing
    file = fopen(filename, "r");
    temp = fopen(temp_filename, "w");

    // check if either file failed to open, if either did exit with error status
    // checkFileExist(file);
    checkFileExist(temp);

    // we'll keep reading the file so long as keep_reading is true
    bool keep_reading = true;

    // will keep track of the current line number we are reading from the file
    int current_line = 1;

    do
    {
        // read the next line of the file into the buffer
        fgets(buffer, MAX_LINE, file);
        // if we've reached the end of the file, stop reading
        if (feof(file) || current_line == 5)
        {

            // Scenario: File Empty

            // go to the end of the file
            fseek(file, 0, SEEK_END); // goto end of file

            // if the file is empty, write the new line to the file
            if (ftell(file) == 0)
            {
                fputs(newline, temp);
                fputs("\n", temp);
            }

            // Scenario: Line Empty
            else if (current_line == write_line)
            {
                fputs(newline, temp);
                fputs("\n", temp);
            }

            // Scenario: Line is greater than current line
            else if (write_line > current_line)
            {
                fputs(buffer, temp);
                fputs("\n", temp);
                fputs(newline, temp);
            }

            // stop reading
            keep_reading = false;
        }

        // scenario: write_line is same as current_line
        else if (current_line == write_line)
        {
            fputs(newline, temp);
            fputs("\n", temp);
            fputs(buffer, temp);
        }
        // otherwise write this line to the temp file
        else
            fputs(buffer, temp);

        // increment the current line as we will now be reading the next line
        current_line++;

    } while (keep_reading);

    // close our access to both files as we are done with them
    fclose(file);
    fclose(temp);

    // delete the original file, rename temp file to the original file's name
    remove(filename);
    rename(temp_filename, filename);
}


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
    srand(time(NULL));
    number = rand() % 100 + 1;
    number = 50;

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
        guess = handlePromptDefaultTwo(strGuess, tries);

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
    // strings
    char *strMenu = "\n1. Spela igen \n2. Avsluta \n3. Se lowscore \nVälj: ";
    char *strError = "Fel inmatning. Försök igen.";

    //  endless loop
    while (true)
    {
        // switch case to check answer from user to execute cases accordingly (1, 2 or 3)
        // and error handling if answer is not 1, 2 or 3 (default)
        switch (handlePromptDefaultTwo(strMenu, 0))
        {
        case 1:
            // play game
            playGameScore();

            // break loop
            break;
        case 2:
            // exit game
            exit(EXIT_SUCCESS);
            
            // break loop
            break;
        case 3:
            // view scoreboard
            viewLowScoreboard();

            // break loop
            break;
        default:
            // print error message
            fprintf(stderr, strError);

            // break loop
            break;
        }

        // print new line
        printf("\n");
    }
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
