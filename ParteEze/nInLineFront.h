#include "nInLineBack.h"
#include "defs.h"

/*This is the function that starts the game */
int startNInLine(void);

/* This function reads and returns an int that matches the option
** the user selected */
int mainMenu(void);


/* This function asks human for the values of ninline, rows and cols.
** It also loads all this data on the structure.
** Then fills the turn and creates the board. ply is for num of players.
** Returns 1 if there was no memory or 0 if there was OK */
int setData(int ply, typeconf * data);

/* This function asks for ninline and validates it */
int getLines(void);

/* This function checks if the number that the user just entered is
** between the right values. If it's not prints an error message.*/
void wrongQuant(int n, int max, int min);

/* Prints the board, just that. It recieves board, row and col.*/
void printBoard(matrix board, int row, int colums);

/* This function returns the play. The parameter is in/out
** This also validates acording to the specs of the board. 
** If it reads 'q' or 'Q' returns 1 and returns 0 if it
** reads a valid move. */
int validMove(int * plays, typeconf data);

/* Prints screens with the results of the turn. 
** Values: -1 Full col, 0 nothin', 1 'X' won, 2 DRAW */
void show(int end, int turn, int * quit);


/* Prints the 'about' screen.*/
void printCredits(void);

int start(void);


