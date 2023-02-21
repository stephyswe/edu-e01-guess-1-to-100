Uppgift 1. Gissa talet - Godkänt kritierium - v.1.1


# Innehållsförteckning #
- Beskrivning
- Kravspecifikation
- Programmet
- Filstruktur



## Beskrivning ##
Programmet ska spela spelet "Gissa talet" med användaren. Spelet går ut på att användaren ska gissa ett tal mellan 1 och 100.
Programmet ska välja ett slumptal och sedan låta användaren gissa vilket tal det är. Efter varje gissning ska programmet ge en ledtråd om talet är större eller mindre.
När användaren gissar rätt ska programmet visa hur många gissningar det tog och fråga om användaren vill spela igen.

** Exempel  **
* Gissa ett tal mellan 1 och 100.
* Gissning 1: 50
* Talet är lägre.
* Gissning 2: 25
* Talet är högre.
* Gissning 3: 37
* Talet är högre.
* Gissning 4: 43
* Talet är högre.
* Gissning 5: 47
* Rätt! Du gissade rätt på 5 försök.
* Vill du spela igen? (Ja/Nej):

## Kravspecifikation ##

### Godkänt ###

    Programmet ska använda de texter som finns i exemplet ovan.
    - Texter sparas som chars (stringtecken).

    Programmet ska välja olika slumptal varje gång.
    - Slumptal genereras med rand() och time().

    Slumptalet ska kunna vara alla tal från 1 till och med 100 men inte 0 och inte 101.
    - Slumptalet genereras med rand() % 100 + 1.

    Skriver användaren in något som inte är ett tal ska de få uppmaningen att försöka igen tills de skriver in ett tal med siffror.
    - Användaren får uppmaningen att försöka igen tills de skriver in ett tal med siffror.

    Programmet ska bara räkna gissningar som är heltal. I exemplet ovan skriver användaren ”Fyra” vilket inte är ett heltal och får då försöka igen.
    - Programmet räknar bara gissningar som är heltal.

    Efter varje gissning ska en ledtråd visas om talet är större eller mindre.
    - Ledtråd visas efter varje gissning.

    Gissar man rätt ska man få reda på hur många gissningar det tog och en fråga om man vill spela igen.
    - "Rätt! Du gissade rätt på %d försök.\n" visas efter varje rätt gissning.
    "Vill du spela igen? (Ja/Nej): " visas efter varje spel.

    Svara man Ja ska spelet starta om från början med ett helt nytt slumptal. Svara man Nej så avslutas programmet.
    
    Vid alla andra svar ställs frågan om man vill spela om igen.
    - "Vill du spela igen? (Ja/Nej):" visas efter varje spel.


### Väl Godkänt ###
    Programmet ska innehålla en ”low score lista”. De (max) fem LÄGSTA resultaten ska lagras i en fil. Och när man spelat en omgång ska man
    (ifall man platsar på highscore) få mata in sitt namn och sen lagrtas man på rätt plats i highscorelistan
    - Low score lista lagras i en fil - "scoreboard.txt". Filen skapas om den inte finns, innehåller de fem lägsta resultaten och uppdateras efter varje spel.

    I menyn ska man kunna välja att se lowscore-listan. Så ska den visas upp på skärmen
    - I menyn kan man välja lowscore-listan med val 3. "3. Se lowscore"

    Datum och tid, namn och antal gissningar ska lagras och visas för varje low-score entry
    - Datum och tid, namn och antal gissningar visas för varje low-score entry
    enligt format "DD/MM/YYY HH:MM NAMN SCORE" - e.x. "02/02/2023 13:17 TopPlayer 3"

    Så istället för ”Vill du spela igen (Ja/Nej)?” ska du implementera en meny
    - "meny" visas efter varje spel med switch case och val 1-3
    "\n1. Spela igen \n2. Avsluta \n3. Se lowscore \n";

    Felhantering – inte krascha vid felaktig inmatning i menyer etc etc och hantera felmeddelanden för användaren
    - Felmeddelande visas för användaren när användaren skriver fel format (text istället för siffror och/eller decimaltal. 
    
    Samt med meddelande "Felaktig inmatning" när användaren skriver felaktigt val i menyn. Användaren får uppmaning att försöka igen till de skriver in ett tal med siffror.

## Programmet ##

Programmet börjar i main() med två funktioner. Spelet startas med playScoreGame() och efter avslutat spel visas en menu(). Menu() har tre valmöjligheter, att spela spelet(1) eller att se scoreboard(2). Samt att avsluta spelet(3)

playScoreGame() har två funktioner, att spela spelet och att spara användarens resultat till en fil.
- playGame() - sparar användarens resultat i en int tries.
- scoreCheck() - kontrollerar om användarens resultat är mindre än nuvarande scoreboard.

- ### om score.isHighScore är sant 
- - sparar användarens resultat i ett Player objekt via playerAdd(). 
- - scoreToFile() - sparas användarens resultat till en fil. På rätt plats i scoreboard.

### playGame() ###
playGame skapar ett slumpmässigt nummer via getRandomNumber(). handlePrompt() är en funktion som hanterar användarens input. Funktionen ger därefter en ledtråd om användarens gissning är för hög eller för låg. Om användarens gissning är rätt så returneras antalet försök som användaren gjorde. **

getRandomNumber() - skapar ett slumpmässigt nummer mellan 1 och 100.

handlePrompt() - hanterar användarens input. Om användarens input är ett nummer mellan 1 och 100 så returneras det. Om användarens input inte är ett nummer mellan 1 och 100 eller ogiltligt returneras ett felmeddelande.


### scoreCheck() ###
scoreCheck läser av scoreboard filen via readFile() och loopar igenom alla rader. scoreAdd() anropas om användarens resultatet är:
- (1) mindre än nuvarande scoreboard. 
- (2) antalet rader i scoreboard är mindre än 5  **

scoreAdd() - skapar ett Score objekt och returnerar det med valt rad samt isHighscore satt till sant. **

### playerAdd() ###

playerAdd skapar ett Player objekt och returnerar det. **

### scoreToFile() ###

scoreToFile anropas med en giltlig rad (write_line) och spelarens resultat. Först sparas datum, användarens namn och poäng i en "newline" rad. Scoreboard filen läser varje rad med fgets() och incrementerar current_line med 1.

om Scoreboard filen är tom eller har 5 rader:
- (1) är scoreboard filen tom "ftell(file) == 0" - lägg till "newline" raden i scoreboard filen.
- (2) är om raden är tom ... TODO


## Filstruktur ##
Det finns totalt 15 filer i projektet. 1 scoreboard fil. 3 structs, 2 common, 2 file, 1 main, 4 inputs och 2 prompt.

### main ###
scoreboard.txt

main.c
- void viewLowScoreboard()
- int playGame()
- void playGameScore()
- void menu()
- void main()

### struct ###
- FileData.h <> FILE *file_ptr, char file_name[60]
- Score.h <> bool isHighScore, int row
- Player.h <> char date[20], char name[20], int points

### common.c ###
- int getRandomNumber()
- char *getCurrentDate()
 
### file.c ###
- void checkFileExist(FILE *file_ptr)
- FileData readFile()
- void scoreToFile(int write_line, Player player)

### inputs ###
playerinput.c
- Player playerAdd(int points)

scoreinput.c
- Score scoreAdd(int row)
- Score scoreCheck(int tries)

### prompt.c ###
- void validateInput(char *inputBuffer)
- bool checkInteger(char *input)
- bool isWithinRange(int num, int min, int max)
- int handlePrompt(const char *prompt, int tries)
- int handleMenuPrompt(const char *prompt)
