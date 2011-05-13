
/*This is the function that starts the game */
int startNInLine(void);

/* This function reads and returns an int that matches the option
** the user selected */
int mainMenu(void);

/* Loads all information of the match. First of all
** verifies if the file exists, then loads the game.
** If file doesn't exist, this function returns to main menu. 
** Returns 0 if everything was OK, 1 if there was an error
** loading or 2 if the file doesn't exist. */
int loadMatch(typeconf * data);

/* Fills all the fields of the struct.
** Returns 0 if it was OK, 1 if it was not. */
int loadData(FILE * fil, typeconf * data);

/* Loads the position of the bricks in the board,
** from the file (fil).
** Returns 0 if it was OK, 1 if it was not. */
int loadBoard(typeconf * data, FILE * fil);

/*Prints loading messages. Returns 0 if it was OK, 1 if it was not.*/
int printLoad(int load);

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

/* Asks a human if he wanna save match.*/
int printSave(typeconf data);

/* Saves all information of the match. First of all
** verifies if the file exists, then asks the human if he wanna
** overwrite it. If file doesn't exist, this function saves the match. 
** Returns 0 if everything was OK, 1 if there was an error
** saving or 2 if the couldn't be written. */
int saveMatch(typeconf data);

/* Prints in standard output a menu when human intends 
** to save with a filename that already exists.
** Returns 1 if it has to overwrite, 2 if it has to reenter name
** 3 if it has to quit without saving. */
int loopMenu(void);

/* Saves data information on a file.
** Returns 0 if it was OK, 1 if it was not. */
int saveData(typeconf data, FILE * fil);

/* Save the position of the bricks in the board on the 
** file. Returns 0 if it was OK, 1 if it was not.*/
int saveBoard(FILE * fil, typeconf data);

/*Free All ;)*/
void freeAll(typeconf data);

/* Prints the 'about' screen.*/
void printCredits(void);

int start(void);
