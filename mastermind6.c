#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

// global constants
#define COLORS 8
#define THREE 3
#define FOUR 4
#define TEN 10
#define NINE 9
#define TRUE 1
#define FALSE 0
#define ZERO 0
#define INVALID -1

// function prototypes
void welcomeScreen();
void clearScreen();
void displayBoard();
int getColor();
void convertColor(int color);
void populateColorArray(char colors[COLORS]);
void setCode(int codeArray[FOUR]);
void initializeArray(int array[TEN][FOUR]);
void getGuess(int guesses[TEN][FOUR], char colors[COLORS]);
int isValid(char colors[COLORS], char color);
void displayBoard(int guesses[TEN][FOUR], int clues[TEN][FOUR]);

//FUNCTION DECLARATIONS
void getClues(int guesses[TEN][FOUR], int clues[TEN][FOUR], int secretCode[FOUR], char colors[COLORS]);
void evaluatePegs(int red, int white, int clues[TEN][FOUR]);
int searchArray(int guesses[TEN][FOUR], char color, int row);
int checkWin(int clues[TEN][FOUR]);
int isDuplicate(char guess[TEN]);


// enumeration
enum color
{
    BLACK,
    GREEN,
    NAVY,
    ORANGE,
    PINK,
    RED,
    VIOLET,
    WHITE
};

// main function
int main()
{
    //STORE IF THE PLAYER HAS WON OR NOT
    int win;

    // array of valid colors as characters
    char colors[COLORS];

    // array for the secret code
    int secretCode[FOUR];

    // array for the player guesses
    int guesses[TEN][FOUR];

    // array for the code maker clues
    int clues[TEN][FOUR];

    // seed the random
    srand(time(NULL));

    // display welcome screen
    welcomeScreen();

    // clear the screen
    clearScreen();

    // set secret code
    setCode(secretCode);

    // clear the screen
    clearScreen();

    // populate the color array with the single character color
    populateColorArray(colors);

    // initialize the guesses array
    initializeArray(guesses);

    // initialize the clues array
    initializeArray(clues);

    // display the initial board
    displayBoard(guesses, clues);

    // get player guess
    // this only performs one turn of the game
    for(int turn = 0; turn < TEN; turn++)
    {
        getGuess(guesses, colors);
        //CALL FUNCTION GET CLUES
        getClues(guesses, clues, secretCode, colors);
        displayBoard(guesses, clues);
        //Set win equal to function checkWin, passing clues
        win = checkWin(clues);
        //Evaluate for win condition
        if (win == TRUE)
        {
            printf("You guessed the secret code!");
        }
        if (win == FALSE && turn == 10)
        {
            printf("You FAILED to guess the secret code!");
        }
    }

    return 0;
}

// welcome screen
void welcomeScreen()
{
    printf("\t\t##########################################################\n");
    printf("\t\t##########################################################\n");
    printf("\t\t############                                  ############\n");
    printf("\t\t############            Mastermind            ############\n");
    printf("\t\t############                                  ############\n");
    printf("\t\t##########################################################\n");
    printf("\t\t##########################################################\n");

    printf("Rules:\n");
    printf("1. The Codemaker sets a secret code\n");
    printf("2. The Codebreaker tries to match the code using logic and deduction\n");
    printf("3. After each move, the Codemaker gives clues to the Codebreaker\n");
    printf("4. The Codebreaker has 10 attempts to guess the secret code\n");

}

// clear the screen
void clearScreen()
{
    char enter;

    printf("\n\t\t\t\t <Hit Enter to continue>\n\n");

    scanf("%c", &enter);

    // windows
    system("cls");

    // linux and mac
//    system("clear");
}

// Mastermind board
void displayBoard(int guesses[TEN][FOUR], int clues[TEN][FOUR])
{

    printf("+----------------------------------------+ \n");
    printf("|            SECRET CODE                 | \n");
    printf("+----------------------------------------+ \n");
    printf("|          ?    ?    ?    ?              | \n");
    printf("+----------------------------------------+ \n");
    printf("|     PLAYER GUESS        |    CLUES     | \n");
    printf("+----------------------------------------+ \n");

    for(int row = NINE; row >= ZERO; row--)
    {
        printf("|   ");
        for(int col = 0; col < FOUR; col++)
            if(guesses[row][col] == INVALID)
                printf("?    ");
            else
                printf("%c    ", guesses[row][col]);

        printf("  |  ");

        for(int col = 0; col < FOUR; col++)
            if(clues[row][col] == INVALID)
                printf("?  ");
            else
                printf("%c  ", clues[row][col]);

        printf("| \n");
        printf("+----------------------------------------+ \n");
    }
}

// Code Maker creates the secret code
void setCode(int codeArray[FOUR])
{
    int code = 0;
    int isUsed[COLORS];
    const int USED = 1;


    //Initialize isUSed elements to -1
    for (code=0; code < FOUR; code++)
    {
        codeArray[code] = INVALID;
    }
    for (code = 0; code < COLORS; code++)
    {
        isUsed[code] = INVALID;
    }

//Set the secret code no duplicates
    for(code = 0; code < FOUR; code++)
    {
        int color = getColor();
        codeArray[code] = color;
        if (isUsed[color] == INVALID)
        {
            for (color = 0; color < COLORS; color++)
            {
                isUsed[color] = USED;
                codeArray[code] = color;
                code++;
            }

        }
    }
}


/*
   printf("Integer Secret Code\n");

    for(code = 0; code < FOUR; code++)
    {
        printf("%d ", codeArray[code]);
    }

    printf("\n");

    printf("\nColor Secret Code\n");

    for(code = 0; code < FOUR; code++)
    {
        convertColor(codeArray[code]);
    }
}*/

// randomly select a member of enum color
int getColor()
{
    // returns a random color from enum
    int color = rand() % COLORS;
    return color;
}

// convert the integer color to a string
void convertColor(int color)
{
    switch(color)
    {
        case BLACK:
            printf("Black ");
            break;
        case GREEN:
            printf("Green ");
            break;
        case NAVY:
            printf("Navy ");
            break;
        case ORANGE:
            printf("Orange ");
            break;
        case PINK:
            printf("Pink ");
            break;
        case RED:
            printf("Red ");
            break;
        case VIOLET:
            printf("Violet ");
            break;
        case WHITE:
            printf("White ");
            break;
    }
}

// populate the character array with single letters for the player to enter
void populateColorArray(char colors[COLORS])
{
    int color;

    for(color = BLACK; color <= WHITE; color++)
    {
        switch(color)
        {
            case BLACK:
                colors[color] = 'B';
                break;
            case GREEN:
                colors[color] = 'G';
                break;
            case NAVY:
                colors[color] = 'N';
                break;
            case ORANGE:
                colors[color] = 'O';
                break;
            case PINK:
                colors[color] = 'P';
                break;
            case RED:
                colors[color] = 'R';
                break;
            case VIOLET:
                colors[color] = 'V';
                break;
            case WHITE:
                colors[color] = 'W';
                break;
        }
    }
}

// initialize the array to be all -1
void initializeArray(int arrays[TEN][FOUR])
{
    int row;
    int col;

    // this is a nested loop to traverse a 2-d array
    for(row = 0; row < TEN; row++)
        for(col = 0; col < FOUR; col++)
            arrays[row][col] = -1;
}

// prompt the Code Breaker for their guess
void getGuess(int guesses[TEN][FOUR], char colors[COLORS])
{
    // use static variable to keep track of the turn number
    // turn number is the row index for the array
    static int row = 0;
    int col;
    char guess[TEN];
    int valid = FALSE;

    printf("\nCharacter colors are \n");

    for(col = 0; col < COLORS; col++)
    {
        printf("%c ", colors[col]);
    }

    while(!valid)
    {
        //Update prompt
        printf("Enter your guess of four colors (no spaces, no duplicates)\n");

        scanf("%s", guess);
        printf("You entered %s\n", guess);

        if(strlen(guess) == FOUR)
        {
            for(col = 0; col < FOUR; col++)
            {
                guess[col] = toupper(guess[col]);

                if(isalpha(guess[col]))
                {
                    //Require is valid and isDuplicate
                    if(isValid(colors, guess[col]) && !isDuplicate(guess))
                    {
                        guesses[row][col] = guess[col];

                        if(col == THREE)
                            valid = TRUE;
                    }
                    else
                    {
                        printf("getGuess: Invalid value entered %c, try again\n", guess[col]);
                        valid = FALSE;
                        break;
                    }
                }
                else
                {
                    printf("getGuess: Invalid value entered %c, try again\n", guess[col]);
                    valid = FALSE;
                    break;
                }
            }
        }
        else
        {
            printf("getGuess: Incorrect number of letters entered\n");
            valid = FALSE;
        }
    }

    row++;
}

// check if the Code Breaker's guess is valid
int isValid(char colors[COLORS], char color)
{
    int c;
    // initialize valid to false, 0
    int valid = FALSE;

    for(c = 0; c < COLORS; c++)
    {
        if(color == colors[c])
        {
            return TRUE;
        }
    }

    return FALSE;
}

//Check if guess has a duplicate
int isDuplicate(char guess[TEN])
{
    int i;
    int j;
    for(i=0; i<TEN; i++)
     {
      for(j=i+1; j<TEN; j++)
       {
          if(guess[i] == guess[j])
          {
             return TRUE;
          }
          else
          {
              return FALSE;
          }

        }
     }
}


void getClues(int guesses[TEN][FOUR], int clues[TEN][FOUR], int secretCode[FOUR], char colors[COLORS])
{
    static int row = 0;
    int redPegs = 0;
    int whitePegs = 0;
    int idx;

    //Loop through the secret code
    for (int col = 0; col < FOUR; col++)
    {
        idx = INVALID;
        idx = searchArray(guesses, colors[COLORS], row);
        //Increment red pegs if user guesses correct color and position
        if (idx == secretCode[col])
            {
                redPegs++;
            }
            //Increment white pegs if user guesses correct color wrong position
            else if (idx != INVALID && idx!= secretCode[col])
            {
                whitePegs++;
            }

        }

    evaluatePegs(redPegs, whitePegs, clues);
    row++;
}

int searchArray(int guesses[TEN][FOUR], char color, int row)
{
    int idx;
    int col;

    for (col = 0; col < FOUR; col++)
    {
        if (guesses[row][col] == (int) color)
        {
            idx = col;
        }
    }


    return idx;
}

void evaluatePegs(int red, int white, int clues[TEN][FOUR])
{
    static int row = 0;
    int col;

    if (red > 0)
    {

        for(int i =0; i < red; i++)
        {

                clues[row][col] = 'R';
            }
    }


    if (white > 0)
    {
            for (col = 0; col < white; col++)
            {
            clues[row][col] = 'W';
            }
    }
    row++;
}

int checkWin(int clues[TEN][FOUR])
{
    static int row = 0;
    int count;
    int col;

    for (row = 0; row < TEN; row++)
    {
        for (col = 0; col < FOUR; col++)
        {
            if (clues[row][col] == 'R')
            {
                count++;
            }
        }
    }
    row++;
    if (count == FOUR)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


