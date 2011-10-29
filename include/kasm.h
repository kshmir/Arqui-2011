/*********************************************
 kasm.h
 ************************************************/

#include "defs.h"

// TODO: Describe this
unsigned int _read_msw();

// TODO: Describe this
void _lidt(IDTR *idtr);

void _restart();
void _setCursor(int a);

/* Writes PIC1's mask */
void _mascaraPIC1(byte mascara);
/* Writes PIC2's mask */
void _mascaraPIC2(byte mascara);

/* Disables interrupts */
void _Cli(void);
/* Enables interrutps  */
void _Sti(void);

/* Timer tick */
void _int_08_hand();
/* Keyboard */
void _int_09_hand();
/* Handler INT 80h */
void _int_80_hand(int systemCall, int fd, char *buffer, int count);

int _rdtsc();

void _doManyCicles();
void _doManyCicles2();
/* System call write */
void _write ( int fd, char *buffer, int count );

/* System call read */
//void _read ( int fd, void *buffer, size_t count );

/* Assembly's out */
int _out(unsigned int port, int value);

/* Assembly's in */
int _in(unsigned int port);

/* Call for debug */
void _debug(void);



/* Get Hour from system */
int _getHour();

/* Get Minutes from system */
int _getMinutes(void);

/* Get Seconds from system */
int _getSeconds(void);


