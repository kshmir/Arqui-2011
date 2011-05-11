#ifndef BUFFER_SIZE

#define BUFFER_SIZE 200
#define MAX_ROWS 24
#define MAX_COLS 80
#define VIDEO 0xb8000

void incrementCursor();

void decrementCursor();
void enter();
int capsOn();
int isShift();
int isCapital();
void escRelease();
void removeLastC();
void controlKey(char scancode);
void putC(char c);
void pushC(char c);
char getC();
int getCursorX();
int getCursorY();
void setCursorX(int x);
void setCursorY(int y);
void moveCursorToStart();
#endif
