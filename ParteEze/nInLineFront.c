#include <stdarg.h>
#include "nInLineFront.h"

/*---------- Costants of menu options ----------*/
#define QUIT 3
#define CREDITS  2


/*---------- Constants of game type ---------*/
#define VS_GAME 0
#define COM_GAME 1

/*--------- Constant of COM move --------*/
#define COM_MOVE -1

/*---------- Constants of dimensions and limits ----------*/
#define MAX_ROW 40
#define MAX_COL 19
#define MIN_N 3
#define MAX_N 19

/*--------- Macro for print a divisor line  --------*/
#define NICE_ROW(col) {int t=6*(col); while(t--) putchar('-');}

/*-------- Macro for empty the buffer. --------*/
#define CHAR_PACMAN while (getchar() != '\n')

/*--------- Constant of full column ----------*/
#define FULL_COL -1

/*---------- Constant of Game Over ----------*/
#define WON 1
#define DRAW 2

int
start(void)
{
	int quit;
	
	quit = startNInLine();	/*Start N In Line.*/
	return quit;
}

int
startNInLine(void)
{
	int option;
	int quit;
	int plays;
	int end;
	typeconf data;
	
	srand((unsigned int) time((time_t*)NULL));  
	
	/*Execute and make the relations of all the functions.*/
	do
	{
		option = mainMenu();
		quit=0;
		
		
		if(option != QUIT && option != CREDITS)		
		{

				if(setData(option, &data))
				{
					printf("\nNot Enough Memory!!\n");
					return 1;
				}
			
			/*-----Start to play.-----*/
			if(!quit)	/*If the file is well loaded or start a new game, it begins to play.*/
				printBoard(data.board, data.rows, data.columns);
			
			while(!quit)
			{
				if(data.turn == 1 || (data.turn == 2 && data.ply == VS_GAME))
					quit = validMove(&plays, data);	/*Check if can play.*/
				else
					plays = COM_MOVE;
				
				if(!quit)
				{
					end = play(&data, plays-1);
					show(end, data.turn, &quit);
					if (!end)
						data.turn = 3 - data.turn; 
					if(end > 0 || (end == 0 && (plays == COM_MOVE || data.ply == VS_GAME)))
						printBoard(data.board, data.rows, data.columns);
				}
			}


		}
		if (option == CREDITS) /*Credits Option */
			printCredits();   
		
	} while(option != QUIT);
	
	return 0;
}

int
mainMenu(void)
{
	int option;
	
	/*Print the main Menu*/
	printf("\n\t*******************************\n");
	printf("\t*                             *\n");
	printf("    _______   .__        .__  .__               \n");
	printf("   \\      \\   |__| ____  |  | |__| ____   ____  \n");
	printf("   /   |   \\  |  |/   \\  |  | |  |/    \\_/ _  \\ \n");
	printf("  /    |    \\ |  |   | \\ |  |_|  |   |  \\  ___/ \n");
	printf("  \\____|__  / |__|___| / |____/__|___| /\\____ .\n");
	printf("          \\/         \\/              \\/    \\/ \n");
	printf("\t*                             *\n");
	printf("\t*\t1. HUM Vs. HUM        *\n");
	printf("\t*                             *\n");
	printf("\t*\t2. HUM Vs. COM        *\n");
	printf("\t*                             *\n");
	printf("\t*\t3. Credits            *\n");
	printf("\t*                             *\n");
    printf("\t*\t4. Exit               *\n");
	printf("\t*                             *\n");
	printf("\t*******************************\n");

	do
	{
		option = getint("\nPlease enter your choice: ");
		
		if(option < 1 || option > 4)
			printf("\nWrong Choice!\n");
	} while (option < 1 || option > 4);
	
	return option-1; /*Returns the player choice.*/
}

int
loadMatch(typeconf * data)
{
	char name[25];
	FILE * fil;
	int aux;
	
	aux=0;
	printf("\nPlease enter the file name (maximum %d chracters): ", 20);
	scanf("%20s", name); 
	CHAR_PACMAN;
	
	/*Load the file if it exists in the directory.*/
	if((fil = fopen(strcat(name, ".sav"), "rb")) != NULL) 
	{
		aux=loadData(fil, data);
		fclose(fil);
	}
	else
		aux=2;
	
	return aux;
}

int
loadData(FILE * fil, typeconf * data)
{
	int ply;
	int row;
	int columns;
	int nlines;
	int aux;
	
	aux=1;
	
	/*Load all the game data.*/
	if(	fread(&(ply), sizeof(ply), 1, fil) &&
		fread(&(data->turn), sizeof(data->turn), 1, fil) &&
		fread(&(row), sizeof(row), 1, fil) &&
		fread(&(columns), sizeof(columns), 1, fil) &&
		fread(&(nlines), sizeof(nlines), 1, fil) &&
		!getData(data, ply, data->turn, row, columns, nlines))
	{
			if(loadBoard(data, fil))
			{	
				freeBoard(data->board, data->rows);
				free(data->index);
			}
			else
			{
				fillIndex(data);
				aux=0;
			}
	}
	
	return aux;
}

int
loadBoard(typeconf * data, FILE * fil)
{
	int i; 
	int aux;
	
	aux=0;
	
	/*Load the board.*/
	for(i=0; i<data->rows && (aux==0); i++)
		aux=(data->columns-fread(data->board[i], sizeof(char), data->columns, fil));
	
	/*Return 0 if it's all ok.*/
	return aux;
}

int
printLoad(int load)
{
	int quit;
	
	quit=0;
	
	/*Print load messages.*/
	switch(load)
	{
		case 0: printf("\nLoading in progress...\n");
		break;
					
		case 1: printf("\nCorrupt File!\n"); quit = 1;
		break;
					
		case 2: printf("\nIt does not exist!\n"); quit = 1;
		break;
	}
	
	/*If is an error returns 1.*/
	return quit;
}

int
setData(int ply, typeconf * data)
{
	int nlines;
	int n; 
	int row;
	int columns;
	
	nlines = getLines();
	
	/*Ask the player for data and fill the struct.*/
	do
	{
		n = getint("\nNumber of Rows (between %d and %d): ", nlines, MAX_ROW);
		wrongQuant(n, MAX_ROW, nlines);
	}while(n > MAX_ROW || n < nlines);

	row = n;
	
	do
	{
		n = getint("\nNumber of Columns (between %d and %d): ", nlines, MAX_COL);
		wrongQuant(n, MAX_COL, nlines);
	}while(n > MAX_COL || n < nlines);
	
	columns = n;
	
	/*Return the struct with the data.*/
	return getData(data, ply, 1, row, columns, nlines); 
}

int
getLines(void)
{
	int n;
	
	/*Ask for the min number of bricks to win.*/
	do
	{
		n = getint("\nNumber of Bricks in a row to win (between %d and %d): ", MIN_N, MAX_N);
		wrongQuant(n, MAX_N, MIN_N);
	}while(n > MAX_N || n < MIN_N);
	
	return n;
}

void
wrongQuant(int n, int max, int min)
{	
	if(n > max || n < min)
			printf("\nWrong quantity!\n");
	
	return;
}

void
printBoard(matrix board, int row, int columns)
{
  	int i; 
	int j;
	
	putchar('\n');
	
	/*Print the board.*/
	for(i=0; i<row; i++)
	{
		NICE_ROW(columns)
	
		printf("\n|");					
		if (i>8)
			printf("<%d>|", i+1);
		else
			printf("<0%d>|", i+1);			
			
		for(j = 0; j < columns; j++)
			printf(" %s  |", (board[i][j] == 0)?" ": 
			((board[i][j] == 1)? "X": "O"));
			
		putchar('\n');
	}
	
	NICE_ROW(columns)
	printf("\n     |");

	for(j = 0; j < columns; j++){
		if (j>8)
			printf("<%d>|", j+1);
		else
			printf("<0%d>|", j+1);
	}
	putchar('\n');
	return;
}

int
validMove(int * plays, typeconf data)
{
	char ch;
	int continues;
	
	continues=1;
	printf("\nPLAYER %d '%c'\n", data.turn, data.turn == 1? 'X':'O');
	
	/*Returns 0 if it's a valid move or 1 if it's quit.*/
	do
	{
		printf("\n Enter move or 'Q' to quit: ");
		
		if(scanf("%d", plays) != 1)
		{
			scanf("%c", &ch);	
			
			if(toupper(ch) == 'Q')
			{
				continues = 0;	
				*plays = 0;		
			}
			else
			{	/*If is not a valid command print a message.*/
				printf("\nInvalid Char!\n");
				CHAR_PACMAN; /*Empty the buffer.*/
			}
		}
		else
		{
			if(*plays < 1 || *plays > data.columns)
			{
				printf("\nInvalid Move!\n");
				CHAR_PACMAN;
			}
			else
			{
				continues = 0;
				ch = 0;
			}
		}
	} while(continues);
	
	CHAR_PACMAN;
	return (int)ch > *plays; 
}

void
show(int end, int turn, int * quit)
{	
	/*Print messages of consequence of a move.*/
	switch(end)
	{
        	case FULL_COL: printf("\nThat column is Full...\n"); break;
		
		case WON: printf("\n##### CONGRATULATIONS PLAYER %d ! YOU WON! #####\n", turn);
		*quit = 1; break;	
		
		case DRAW: printf("\nDRAW :(\n");
		*quit = 1; break; 
		
		case -2: printf("\nNot enough memory! System32 Error. Shutting down..\n");
		*quit = 1; break;
	}
	
	return;
}



int
loopMenu(void)
{
	int c;
	
	printf("\nThis file already exists!\n"
	"\n\t1. OverWrite?\n"
	"\n\t2. Enter new file name\n"
	"\n\t3. Quit without Saving\n");
	
	/*Ask for what to do when a file name already exists.*/
	do
	{
		printf("\nEnter your choice: ");
		scanf("%d",&c);
		CHAR_PACMAN;
		
		if(c < 1 || c > 3)
			printf("\nInvalid Choice!\n");
	} while(c < 1 || c > 3);
	
	return c;
}


void
printCredits(void)
{	
	/*Print the credits of the game.*/
	printf("_________           __________________         \n");
	printf("__  ____/_________________  /__(_)_  /________ \n");
	printf("_  /    __  ___/  _ \\  __  /__  /_  __/_  ___/ \n");
	printf("/ /___  _  /   /  __/ /_/ / _  / / /_ _(__  )  \n");
	printf("\\____/  /_/    \\___/\\__,_/  /_/  \\__/ /____/   \n");
	printf("\n \t Muricelag O.S\n\nN In Line - VER 1.00 @2007 All Rights Reserved.\n\n");
	return;
}
