#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define FILENAME_SIZE 1024
#define MAX_LINE 2048
#define BUF_SIZE 65536
#define FILE_SCORE "score.txt"

extern int errno;

/* Uppgift 1. Gissa talet - Godkänt kritierium

** Innehåller **
- Structs (4)
- Funktioner (3)
- While-loopar (2)
- If-satser (2)
- Slumptal (1)
- Strängar (2)
- Inmatning (2)
- Inmatningskontroll (1)

** Common Functions **
strcpy - The strcpy() function copies the string pointed by source
    (including the null character) to the destination
e.x.    strcpy(player.date, getCurrentDate());
        instead of
        player.date = getCurrentDate();


- https://www.programiz.com/c-programming/library-function/string.h/strcpy

** Chronological Structs/Common (18) **
- char *getCurrentDate - gets the current date
- bool isNumber(char *input, bool has_decimal, bool isInteger) - checks if a string is a number
- bool isDecimal(char *input, bool has_decimal) - checks if a string is a decimal

- void checkFileExist(file_ptr) - checks if a file exists
- typedef struct FileData - struct to store data from a file
- FileData readFile - reads a file and returns the data
- FileData writeFile - writes data to a file
- void viewLowScoreboard - views the low scoreboard

- typedef struct Player - struct to store a player
- Player playerAdd(int tries) - adds a player to player struct

- typedef struct Score - struct to store a score
- Score scoreAdd(int write_line, struct Player player) - adds a score to a score struct
- Score scoreCheck(points) - checks if a score is valid
- void scoreToFile(int write_line, struct Player player) - adds a score to a score struct

- int handlePromptDefault(char* stringMessage, int tries) - handles prompt for default messages

- int playGame - plays a game of 'Guess the number'
- void playGameScore - plays a game and saves the score

- void menu - playGameScore & viewLowScoreboard
- int main - playGameScore & menu

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
- playGame - if statement to check if user input is a number


** Beskrivning **
Programmet ska spela spelet "Gissa talet" med användaren. Spelet går ut på att användaren ska gissa ett tal mellan 1 och 100.
Programmet ska välja ett slumptal och sedan låta användaren gissa vilket tal det är. Efter varje gissning ska programmet ge en ledtråd om talet är större eller mindre.
När användaren gissar rätt ska programmet visa hur många gissningar det tog och fråga om användaren vill spela igen.

** Exempel **
** Instruktioner **
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
- Kommentar: "Vill du spela igen? (Ja/Nej):" visas efter varje spel.


** Kravspecifikation - VG **
• Programmet ska innehålla en ”low score lista”. De (max) fem LÄGSTA resultaten ska lagras i en fil. Och när man spelat en omgång ska man
    (ifall man platsar på highscore) få mata in sitt namn och sen lagrtas man på rätt plats i highscorelistan
- Kommentar: Low score lista lagras i en fil - "score.txt". "score.txt" skapas om den inte finns.
    "score.txt" innehåller de fem lägsta resultaten. "score.txt" uppdateras efter varje spel.

• I menyn ska man kunna välja att se lowscore-listan. Så ska den visas upp på skärmen
- Kommentar: I menyn kan man välja lowscore-listan med val 3. "3. Se lowscore"

• Datum och tid, namn och antal gissningar ska lagras och visas för varje low-score entry
- Kommentar: Datum och tid, namn och antal gissningar visas för varje low-score entry
    enligt format "DD/MM/YYY HH:MM NAMN SCORE" - e.x. "02/02/2023 13:17 TopPlayer 3"

• Så istället för ”Vill du spela igen (Ja/Nej)?” ska du implementera en meny
- Kommentar: "meny" visas efter varje spel med switch case och val 1-3
    "\n1. Spela igen \n2. Avsluta \n3. Se lowscore \n";

• Felhantering – inte krascha vid felaktig inmatning i menyer etc etc och ra felmeddelandn för användaren
- Kommentar: Felmeddelande visas för användaren när användaren skriver fel format (text istället för siffror)
    och/eller decimaltal. Samt med meddelande "Felaktig inmatning" när användaren skriver felaktigt val i menyn.
    Användaren får uppmaningen att försöka igen tills de skriver in ett tal med siffror.
*/

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

bool isNumber(char *input, bool has_decimal, bool isInteger)
{
    // Check if input is integer
    int integer;

    // Error messages
    char *strWrongDecimal = "Fel. Inmatningsvärdet har decimal. Försök igen.\n";
    char *strWrongType = "Fel. Inmatningsvärdet är varken heltal eller float. Försök igen.\n";

    // Check if input is integer and has decimal. Print error message if input is float
    if (sscanf(input, "%d", &integer) == 1 && has_decimal)
        printf(strWrongDecimal);

    // Check if input is integer and doesn't have decimal. Set isInteger to true if input is integer
    else if (sscanf(input, "%d", &integer) == 1 && !has_decimal)
        isInteger = true;

    // Wrong input type. Print error message
    else
        printf(strWrongType);

    // Return isInteger
    return isInteger;
}

// Function: isDemical
// Description: Checks if input is decimal
// Parameters: char *input, bool has_decimal
// Returns: bool has_decimal
// Side-effects: None
// Error-handling: None
// Status: 'Working'
bool isDecimal(char *input, bool has_decimal)
{
    // Loop through input
    for (int i = 0; input[i] != '\0'; i++)
    {
        // Check if input is decimal or dot
        if (input[i] == '.' || input[i] == ',')
        {   // Input is decimal
            has_decimal = true;
            break;
        }
    }

    // Return has_decimal
    return has_decimal;
}

void checkFileExist(FILE *file_ptr)
{
    // Error number
    int errnum;

    // Check if file exists
    char there_was_error = 0;
    char opened_in_read  = 1;

     // strings
    char answer[8];
    char *strIntro = "Vill du skapa en ny fil (score.txt)? (Ja/Nej): ";
    char *strYes = "Ja";
    char *strNo = "Nej";

    // Check if file exists
    if (file_ptr == NULL)
    {
        // Get error number
        errnum = errno;

        // Print error message
        fprintf(stderr, "Value of errno: %d\n", errno);

        // Print error message
        perror("Error printed by perror");

        // Print error message
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));

        // Print error message
        printf("Error opening file %s \n", file_ptr);

        // Ask user if they want to create a new file
        printf("Do you want to create a new file? (Ja/Nej) \n");

        // loop while answer is not "Ja" or "Nej"
        while (scanf(" %s", &answer) == 1 && strcmp(answer, strYes) != 0) {
             if (strcmp(answer, strYes) == 0){

                // create file
                file_ptr = fopen(FILE_SCORE, "r");

                // Check if file exists. if Not set there_was_error to 1
                if (file_ptr == NULL)
                    there_was_error = 1;
            }
            else if (strcmp(answer, strNo) == 0){
                // Exit program
                exit(EXIT_FAILURE);
            }
            else{
                printf("Felaktig inmatning. Försök igen. \n");
        }
        }

        // Check if there was an error
        if (there_was_error)
        {
            // Print error message
            printf("Disc full or no permission\n");

            // Exit program
            exit(EXIT_FAILURE);
        }

        // Check if file was opened in read mode
        else
            // Print success message
            printf("The file %s was created successfully. \n", FILE_SCORE);
    }
}

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

// struct player
// Description: Struct for player with date
// Parameters: none
// Returns: struct Player
// Side-effects: None
// Error-handling: None
// Status: 'Working'
typedef struct
{
    // Player date
    char date[20];

    // Player name
    char name[20];

    // Player points
    int points;
} Player;

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

// Function: Struct Score
// Description: Struct for score
// Parameters: None
// Returns: None
// Side-effects: None
// Error-handling: None
// Status: 'Working'
typedef struct
{
    // Score isHighScore
    bool isHighScore;

    // Score points
    int points;

    // Score row
    int row;
} Score;


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

// Function: scoreAdd
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

// Function handlePromptDefault
// Description: Prompts user for input
// Parameters: char* stringMessage, int tries
// Returns: int number
// Side-effects: None
// Error-handling: None
// Status: 'Working'
int handlePromptDefault(char *stringMessage, int tries)
{
    // Variables
    char input[100];
    bool has_decimal = false;
    bool isInteger = false;

    // While loop to check if input is an integer
    while (!isInteger)
    {
        // reset variables
        has_decimal = false;

        // prompt user for input
        printf(stringMessage, tries);

        // get input from user
        scanf("%s", input);

        // checks if number is an double by decimal point
        has_decimal = isDecimal(input, has_decimal);

        // checks if number is an integer
        isInteger = isNumber(input, has_decimal, isInteger);
    }

    // Converts string to int
    int number = atoi(input);

    // return number
    return number;
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
        guess = handlePromptDefault(strGuess, tries);

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
        switch (handlePromptDefault(strMenu, 0))
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
