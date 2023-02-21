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