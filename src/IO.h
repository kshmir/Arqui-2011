#ifndef BUFFER_SIZE

#define BUFFER_SIZE 200
#define MAX_ROWS 25
#define MAX_COLS 80
#define VIDEO 0xb8000

/** Increment's the video card's cursor position */
void incrementCursor();
/** Decrements's the video card's cursor position */
void decrementCursor();
void enter();
/** Gets whether caps is on or not */
int capsOn();
/** Tells wether a shift's on */
int isShifted();
/** Checks shifts and caps to check whether font should
 * be CAPITALIZED or not
 */
int isCapital();
/**	Calld everytime esc's released */
void escRelease();
/**	Removes last character and decreases cursor */
void removeLastC();
/** Receives the scancodes which aren't from a key.
 * And changes the shift state, control, alt, etc.
 */
void controlKey(char scancode);
/**
 * Calls INT80 and prompts a write of c with it's style value
 * Then it increment's the cursor
 */
void putC(char c);
/** Stores all the characters it receives on a buffer */
void pushC(char c);
/** Get's the last char on the KB buffer */
char getC();
int getCursorX();
int getCursorY();
/* Sets X cursor by setting the logic cursor and then
 * ask's kernel to update the effective pointer.
 */
void setCursorX(int x);
/* Sets Y cursor by setting the logic cursor and then
 * ask's kernel to update the effective pointer.
 */
void setCursorY(int y);
void moveCursorToStart();
#endif
