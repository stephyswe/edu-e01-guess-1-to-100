Uppgift 1. Gissa talet - Godkänt kritierium - v.1.1


# Innehållsförteckning #
- Beskrivning
- Kravspecifikation
- Programmet
- Filstruktur

## Beskrivning ##
Programmet "Gissa talet" utmanar användaren att gissa ett slumpmässigt valt tal mellan 1 och 100. Efter varje gissning ges en ledtråd om talet är större eller mindre än det gissade talet. När användaren till slut gissar rätt visar programmet antalet gissningar det tog och frågar om användaren vill spela igen. 

### Väl godkänt ####
 - Om användarens resultat är lägre än resultatet i scoreboard-filen, kan de spara datum, namn och poäng i filen.

** Exempel - Godkänt  **
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

** Exempel - Väl Godkänt  **
* Samma som ovan.
* Rätt! Du gissade rätt på 5 försök.
* Ange ditt namn: ___
1. Spela igen
2. Avsluta
3. Se lowscore
* Välj: ___

## Kravspecifikation ##

### Godkänt ###
    Programmet ska använda de texter som finns i exemplet ovan.
    - Texterna sparas som teckensträngar (strings).

    Programmet ska välja olika slumptal varje gång.
    - Slumptalen genereras med rand() och time().

    Slumptalet ska kunna vara alla tal från 1 till och med 100 men inte 0 och inte 101.
    - Slumptalen genereras med rand() % 100 + 1.

    Skriver användaren in något som inte är ett tal ska de få uppmaningen att försöka igen tills de skriver in ett tal med siffror.
    - Användaren uppmanas att försöka igen tills de skriver in ett tal.

    Programmet ska bara räkna gissningar som är heltal. I exemplet ovan skriver användaren ”Fyra” vilket inte är ett heltal och får då försöka igen.
    - Programmet räknar endast gissningar som är heltal.

    Efter varje gissning ska en ledtråd visas om talet är större eller mindre.
    - En ledtråd visas efter varje gissning.

    Gissar man rätt ska man få reda på hur många gissningar det tog och en fråga om man vill spela igen.
    - "Rätt! Du gissade rätt på %d försök.\n" visas efter varje korrekt gissning.
    "Vill du spela igen? (Ja/Nej): " visas efter varje spel.   

    Svara man Ja ska spelet starta om från början med ett helt nytt slumptal. Svara man Nej så avslutas programmet.
    
    Vid alla andra svar ställs frågan om man vill spela om igen.
    - "Vill du spela igen? (Ja/Nej):" visas efter varje spel.

### Väl Godkänt ###
    Programmet ska innehålla en ”low score lista”. De (max) fem LÄGSTA resultaten ska lagras i en fil. Och när man spelat en omgång ska man
    (ifall man platsar på highscore) få mata in sitt namn och sen lagrtas man på rätt plats i highscorelistan
    - Low score listan lagras i filen "scoreboard.txt". Filen skapas om den inte finns, innehåller de fem lägsta resultaten och uppdateras efter varje spel.

    I menyn ska man kunna välja att se lowscore-listan. Så ska den visas upp på skärmen
    - I menyn kan användaren välja lowscore-listan med alternativ 3: "3. Se lowscore".

    Datum och tid, namn och antal gissningar ska lagras och visas för varje low-score entry
    - Datum och tid, namn och antal gissningar ska lagras och visas för varje low-score entry enligt formatet "DD/MM/YYY HH:MM NAMN SCORE", t.ex. "02/02/2023 13:17 TopPlayer 3

    Så istället för ”Vill du spela igen (Ja/Nej)?” ska du implementera en meny
    - Efter varje spel visas en meny med tre alternativ med hjälp av switch case:
    "\n1. Spela igen \n2. Avsluta \n3. Se lowscore \n".

    Felhantering – inte krascha vid felaktig inmatning i menyer etc etc och hantera felmeddelanden för användaren
    - Felmeddelande visas för användaren när användaren skriver felaktigt val i menyn. Användaren får uppmaning att försöka igen tills hen skriver in ett giltigt val.
    Felmeddelande visas också när användaren skriver in fel format (text istället för siffror och/eller decimaltal). Meddelandet "Felaktig inmatning" visas och användaren får uppmaning att försöka igen tills hen skriver in ett giltigt tal.

## Programmet ##
Programmet inleds i main() med två funktioner, där spelet påbörjas genom funktionen 'playScoreGame()', och efter spelet är avslutat visas en meny() med tre alternativ: att spela spelet (1), visa scoreboard (2), eller att avsluta spelet (3). Om användaren väljer att spela spelet igen så startas funktionen 'playScoreGame()' igen. Om användaren väljer att visa scoreboard så visas viewLowScoreboard() och om användaren väljer att avsluta spelet så avslutas programmet.

playScoreGame() omfattar två funktioner: att spela spelet och att spara användarens resultat till en fil. playGame() ansvarar för att lagra användarens gissningsförsök i en variabel 'tries', medan scoreCheck() verifierar om användarens resultat är mindre än det nuvarande resultatet i scoreboard. Om score.isHighScore är sant, så lägger scoreToFile() till användarens resultat på rätt plats i scoreboard-filen.

### playGame() ###
Funktionen playGame genererar ett slumpmässigt nummer med hjälp av getRandomNumber(). handlePrompt() hanterar användarens input och ger ledtrådar om gissningen är för hög eller för låg. Om användaren gissar rätt returneras antalet försök som användes.

getRandomNumber() - genererar ett slumpmässigt heltal mellan 1 och 100.

handlePrompt() - hanterar användarens inmatning. Om användarens inmatning är ett giltigt heltal mellan 1 och 100 returneras det. Om inmatningen inte är ett giltigt heltal mellan 1 och 100 returneras ett felmeddelande.

### scoreCheck() ###
scoreCheck kontrollerar scoreboard-filen genom att läsa in den med hjälp av readFile() och iterera igenom varje rad. scoreAdd() funktionen anropas när användarens resultat uppfyller en av följande kriterier:
(1) Det är mindre än det nuvarande resultatet i scoreboard.
(2) Antalet rader i scoreboard är mindre än 5.

scoreAdd() - skapar och returnerar ett Score-objekt med vald rad och isHighscore inställd på sant.

### scoreToFile() ###

scoreToFile anropar med radnummer (line_to_write) och försök (tries). Först anropas playerAdd(). Datum, namn och poäng sparas i en "newline"-rad med hjälp av snprintf(). En temporär fil skapas via Datum-objekt. Scoreboard-filen läser varje rad med fgets() och ökar current_line med 1. Det finns tre scenarion där det nya resultatet sparas i temporär fil. Efter scenarion stängs scoreboard-filen och temporära filen med fclose(). Slutligen tas den nuvarande scoreboard-filen bort med remove() och ersätts av den temporära filen via funktionen rename().

playerAdd() skapar och returnerar en instans av "Player"-klassen.
 
| Scenario           | Åtgärd |
|--------------------|----------------------------------------------------------------|
| Input === output och input > 5  | Lägg till en ny rad, radbyte & befintlig rad |
| Input !== output och input > 5 | Lägg till befintlig rad om input och output är olika |
| Filen är ny, input === output & input > 5 | Lägg till ny rad och radbyte |

## Filstruktur ##
Det finns totalt 15 filer i projektet. 1 scoreboard fil. main, define, structs, common, file, input och prompt.

### main ###
scoreboard.txt

main.c
- void viewLowScoreboard()
- int playGame()
- void playGameScore()
- void menu()
- void main()

### struct ###
- FileData.h - FILE *file_ptr, char file_row[256]
- Score.h - bool isHighScore, int row
- Player.h - char date[20], char name[20], int points

### common.c ###
- int getRandomNumber()
- char *getCurrentDate()
 
### file.c ###
- void createFileWithEmptyRow(char *filename)
- FileData useFile(char *filename, *mode)
- void scoreToFile(int line_to_write, int tries)

### input.c ###
- Player playerAdd(int tries)
- Score scoreCheck(int tries)

### prompt.c ###
- void validateInput(char *inputBuffer)
- bool checkInteger(char *input)
- bool isWithinRange(int num, int min, int max)
- int usePrompt(char *prompt, int max, int tries)

### Define.h ###
- file
- input
- main
- prompt
