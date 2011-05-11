#include "../src/shell.h"

char lines[MAX_COLS][MAX_ROWS];
int x=0,y=0;
void shellStart(){
	int i,j;
	for(i=0;i<MAX_COLS;i++)
		for(j=0;j<MAX_ROWS;j++)
			lines[i][j]=0;
	k_clear_screen();
	drawComandLine();
}

void drawComandLine(){
	lines[x++][y]=' ';
	lines[x++][y]='$';
	lines[x++][y]=':';
	lines[x++][y]=' ';
	putC(' ');
	putC('$');
	putC(':');
	putC(' ');
	}

void nextRow(){
		setCursorX(0);
		x=0;
		//int aux=getCursorY();
	if(y<MAX_ROWS-1){
		setCursorY(++y);
		drawComandLine();
	}else {
		int i,j;
		for(i=0;i<MAX_COLS;i++){
			for(j=0;j<MAX_ROWS-1;j++)
				lines[i][j]=lines[i][j+1];
		}
				for(i=0;i<MAX_COLS;i++)
					lines[i][MAX_ROWS-1]=0;
		reDrawLines();
		x=0;
		y=MAX_ROWS-1;
		setCursorX(x);
		setCursorY(y);
		drawComandLine();
	
	}
		//int y=MAX_;
		//setCursorY(0);
}
void reDrawLines(){
	int i,j;
	k_clear_screen();
	y=0;
		for(j=0;j<MAX_ROWS;j++){
			x=0;
			setCursorX(0);
			setCursorY(y++);
			for(i=0;i<MAX_COLS;i++){
				if(lines[i][j]==0x0f){
					putTab();
				}else if(lines[i][j]==0){
					i=MAX_COLS;
				}else{
					putC(lines[i][j]);
					x++;
				}
			}
			
		}
		//x=0;
		//setCursorX(0);
	}

void putSpace(){
	putC(getC());
	lines[x++][y]=' ';
	}

void putTab(){
		putC(' ');
		putC(' ');
		putC(' ');
		putC(' ');
	}
	
void backSpace(){
	if(x){
		char c=lines[--x][y];
		lines[x][y]=0;
		if(c==0x0f)
			removeTab();
			else{
		removeLastC();
		//setCursorX(getCursorX()-1);
		}
	}
}
	
void removeTab(){
		removeLastC();
		removeLastC();
		removeLastC();
		removeLastC();
	}
	
void putChar(char c){
	lines[x++][y]=c;
	putC(lines[x-1][y]);
	}
	

void shellKBInterrupt(){
	char c=getC();
	//int x=getCursorX()-CLSIZE;
	//int y=getCursorY();
	if(x<MAX_COLS){
		if(c==0x0f){
			if(getCursorX()<=MAX_COLS-4){
				putTab();
				lines[x++][y]=c;
			}
		}else if(c == 0x39)
			putSpace();
		else{
			putChar(c);		
		}
	}
	
}
