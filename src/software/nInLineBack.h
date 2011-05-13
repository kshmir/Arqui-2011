#include "../../include/defs.h"
#include "../libs/stdlib.h"

/*--------- Matrix Type. --------*/
typedef char ** matrix;

/*--------- Structure Type --------*/
typedef struct typeconf
{
	int ply; 	/* Indicates if the game is HUM vs HUM or HUM vs COM*/
	int turn;	/* Indicates the turn */
	int rows;	/* The quantity of rows in the board */
	int columns;	/* The quantity of cols in the board */
	int nlines;	/* The quantity of bricks in line to win */
	matrix board;	/* board pointer */
	int * index;	/* Index array */
} typeconf;

/* Fills all the information of the match in config. It also creates the board and
** the index array. Returns 0 if it was OK, 1 if it was not. */
int getData(typeconf * data, int ply, int turn, int rows, int columns, int nlines);

/* This function creates a dynamic matrix.
** Returns a pointer to it or NULL if there was an error */
matrix getBoard(int columns, int rows);

/* This function Free the matrix that has quant of rows. */
void freeBoard(matrix board, int quant);

/* Fills the index array with the row in where the next brick goes,
** according in which column will put the brick. */
void fillIndex(typeconf * data);

/* This function has to ckeck who has to play.
** 1 (player1), 2 (player2) or -1 (PC). If the column 
** is full, returns FUL_COL. It the col is not full places the
** brick where it goes and returns if with this movement the player
** won, draw or continue playing (WON, DRAW or 0). */
int play(typeconf * data, int j);

/* This function is the Artificial Inteligence.
** Returns the row where the brick was placed. 
** The are 3 laws: 
** First of all, winning if it's possible. 
** If it's not then try to avoid HUM wins on the next move.
** If everything goes wrong then choose a random move */
int playCOM(typeconf data);

/* Seeks for a column where there is a winner move and places the brick there.
** Returns that col or -1 if there was no col to win. */
int winnerMove(typeconf data, int player);

/* Place the brick of player p in the col j returning the row where that brick is*/
int placeBrick(typeconf * data, int p, int j);

/* Reads the last played row j, and determines if the game is over, 
** returning WON, DRAW or 0 if the game is still on */
int  gameOver(typeconf data, int j);

/* Gived a position (f,j) and a direction array (rpos, cpos), returns 0 or 1
** when it was a line */
int isLine(typeconf data, int f, int j, int rpos, int cpos);

/* Checks if the position (row, colum) is not outside the board */
int position(typeconf data, int row, int column);

/* Undo the last brick puted on the col j, returning the row where it was */
int undoBrick(typeconf * data, int j);

/* Seeks for a random empty col that not desovey the 2 first laws.
** Returns -2 if there was no memory or -1 if every col was full */
int randZero(typeconf data);

/* Returns a random int between left and right */
int randInt(int left, int right);

/* Swap a couple of chars*/
void swapChars(char * i, char * j);
