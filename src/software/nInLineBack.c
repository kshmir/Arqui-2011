#include "nInLineBack.h"

#include "../libs/stdio.h"
#include "../libs/stdlib.h"
#include "../libs/string.h"

/*-------- Constant of Full Column  ----------*/
#define FULL_COL -1

/*--------- Constants of Game Over. --------*/
#define WON 1
#define DRAW 2
#define RAND_MAX ((65535*255))

int
getData(typeconf * data, int ply, int turn, int rows, int columns, int nlines)
{
	/*Fill the structure fields*/
	data->ply = ply;
	data->turn = turn;
	data->rows = rows;
	data->columns = columns;
	data->nlines = nlines;
	
	/*Create the board, if an error happens returns null*/
	if((data->board = getBoard(columns, rows)) == NULL)
		return 1;
	
	/*Create the index array.*/
	if ((data->index = malloc(columns * sizeof(int))) == NULL)
	{
		freeBoard(data->board, data->rows);
		return 1;
	}
	
	/*Fill The Index array.*/	
	fillIndex(data);
	
	return 0;
}

matrix
getBoard(int columns, int rows)
{
	matrix board;
	int i;
	
	/*Crate the matrix with 0 in all positions.*/
	if ( (board = calloc(rows, sizeof(char*))) != NULL )
		for(i=0; i<rows; i++)
			if ( ( board[i] = calloc(columns, sizeof(char))) == NULL ) 
			{
				freeBoard(board, i); /*If can't create it, return null*/
				return NULL;
			}
	
	return board;		
}

void
freeBoard(matrix board, int quant)
{
	while(quant--)
		free(board[quant]); /*Free the rows.*/
		
	free(board); /*Free The Board.*/
	return;
}

void
fillIndex(typeconf * data)
{
	int j;
	int i;
	int flag;
	
	/*Complete the array of indexes with the number of row*
	of the brick, for example if the brick will be in the row 2*
	and col 1, put 2 in the pos 1 of the array.*/ 
	for(j=0; j<data->columns; j++)
	{	
		i=data->rows-1;
		flag=1;
		
		while(i>=0 && flag)
		{
			if (data->board[i][j]==0)
			{
				data->index[j]=i;
				flag=0; 
			}
			
			i--;
		}
		
		if(flag)
			data->index[j]=i;
	}
	
	return;
}

int
play(typeconf * data, int j)
{
	/*Return WON if the player wins, DRAW if it's a draw*
	*or 0 if noone wins.*/
	if (j<0)
	{
		if((j=playCOM(*data)) == -2)
			return -2;
	}
	else if(placeBrick(data, data->turn, j)<0)
		return FULL_COL;
	
	return gameOver(*data,j);
}

int
playCOM(typeconf data)
{
	int column;	
	
	if((column=winnerMove(data, 2))<0)
	{
		/*Return the number of col where the brick was placed.*/
		if((column=winnerMove(data, 1))<0)
			column=randZero(data);
		else
		{
			undoBrick(&data, column);
			placeBrick(&data, 2, column);
		}
	}
	
	return column;
}

int
winnerMove(typeconf data, int player)
{
	int j;
	
	j=0;
	
	/*Search for a pos where the player can win*
	return the number of col or -1 instead.*/
	while(j<data.columns)
	{
		if(placeBrick(&data, player, j)>=0)
		{
			if(gameOver(data, j) != 0)
				return j;
			else
				undoBrick(&data, j);
		}
		
		j++;
	}
	
	return -1;
}

int
placeBrick(typeconf * data, int p, int j)
{	
	/*Return the row of the brick or -1.*/
	if(data->index[j] >= 0)
	{
		data->board[data->index[j]][j]=p;
		return data->index[j]--;
	}
	
	return -1;
}

int 
gameOver(typeconf data, int j)
{
	int i;
	int vec[]={-1,-1,-1,0,-1,1,0,-1};
	
	i=0;
	/*If the last brick makes player win return WON.*/
	while(i<8)
	{
		if(isLine(data, data.index[j]+1, j, vec[i], vec[i+1]))
			return WON;
		
		i+=2;
	}
	
	i=0;
	
/*If the row 0 has empty positions is a draw.*/
	while(i<data.rows) 
	{	
		if (data.board[0][i]==0)
			return 0;
		
		i++;
	}
	
	return DRAW;
}

int 
isLine(typeconf data, int f, int j, int rpos, int cpos)
{
	int i;
	int abricks; 	/* amount of Bricks. */
	int flagpos;	/* flag position */
	int flagapos;  	/*  flag antiposition. */

	i=1;
	abricks=1; 
	flagpos=1;
	flagapos=1; 
	
	/*If is a line of data.nlines or more bricks in the (f,j)*
	*pos return 1 instead return 0.*/	
	while(i<=data.nlines && abricks < data.nlines)
	{
		if (flagpos && (flagpos=position(data,f+rpos*i,j+cpos*i)))
		{
			if(data.board[f][j]==data.board[f+rpos*i][j+cpos*i])
				abricks++;
			else
				flagpos=0;
		}
		if (flagapos && (flagapos=position(data,f+rpos*(-i),j+cpos*(-i))))
		{
			if(flagapos && data.board[f][j]==data.board[f+rpos*(-i)][j+cpos*(-i)])
				abricks++;
			else
				flagapos=0;
		}
		
		i++;
	}
	
	if (abricks>=data.nlines)
		return 1;
	else
		return 0;
}

int
position(typeconf data, int row, int column)
{	
	/*If the pos is inside the matrix return 1.*/
	if (row<data.rows && row>=0)
		if (column<data.columns && column>=0)
			return 1;

	return 0;
}

int
undoBrick(typeconf * data, int j)
{	
	/*Erase the last brick in the col j and*
	*returns the number of row.*/
	if(data->index[j] < data->rows - 1)
		data->board[++data->index[j]][j]=0;
	
	return data->index[j];
}

int
randZero(typeconf data)
{
	int i, j, top=data.columns-1, aux=-1;
	char * m;
	
	/*Search for a not full col where the player can't win, or*
	*a random col, and return the col. Return -1 if all cols are full or*
	*-2 if is not enough memory.*/
	if((m=malloc(data.columns * sizeof(char))) == NULL)
		return -2;
	
	for(i=0; i<data.columns; i++)
		m[i]=i;
	
	for(i=0; i<=top; )
	{
		j=randInt(i, top);
		
		if(placeBrick(&data, 2, m[j])>=0)
			if(placeBrick(&data, 1, m[j])>=0)
				if(gameOver(data, m[j])==1)
				{
					undoBrick(&data, m[j]);
					undoBrick(&data, m[j]);
					swapChars(m+i, m+j);
					i++;
				}
				else
				{
					undoBrick(&data, m[j]);
					aux=m[j];
					free(m);
					return aux;
				}
			else
			{
				aux=m[j];
				free(m);
				return aux;
			}
		else
		{
			swapChars(m+top, m+j);
			top--;
		}
		
	}
	
	if(placeBrick(&data, 2, m[0])>=0)
		aux=m[0];
	
	free(m);
	
	return aux;
}

int
randInt(int left, int right)
{
	/*Return a random int.*/
	return ((int) ((rand() / ((double) RAND_MAX + 1)) * (right - left + 1) + left));
}

void
swapChars(char * i, char * j)
{
	char aux;
	
	/*j takes the value of i and i takes the value of j.*/
	aux=*i;
	*i=*j;
	*j=aux;
	
	return;
}
