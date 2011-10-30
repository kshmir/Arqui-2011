#ifndef _KEYBOARD_H_

#define _KEYBOARD_H_
#define BUFFER_SIZE 200
#define EN 0
#define ES 1
char scanCodeToChar(char scanCode);

void startKeyboard();
/** Stores all the characters it receives on a buffer */
void pushC(char c);

/** Receives the scancodes which aren't from a key.
 * And changes the shift state, control, alt, etc.
 */
int controlKey(int scancode);

/** Gets whether caps is on or not */
int capsOn();
/** Tells wether a shift's on */
int isShifted();
/** Checks shifts and caps to check whether font should
 * be CAPITALIZED or not
 */
int isCapital();

/** Get's the last char on the KB buffer */
char getC();

int directionKey();

void printkeym();

void setKeyboard();

void setCurrentKeyboard(int ck);

#endif /* STDLIB_H_ */

