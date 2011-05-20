/***************************************************
 Defs.h
 Loads the definitions of each constant in the code.
 ****************************************************/

#ifndef _defs_
#define _defs_

#define BORRA_BUFFER while (getC() != 0)
#define EOI 0x20
#define NULL 0
#define WRITE 0
#define READ 1
#define KEYBOARD 0
#define STDOUT 1
#define PIC1 2
#define PIC2 3
#define ASCIICERO 0x30
#define TRUE 1
#define FALSE 0

#define CICLOSFIJOS 2952790087

#define time_t long
#define byte unsigned char
#define word short int
#define dword int

/* Flags para derechos de acceso de los segmentos */

/* Segment present in memory */
#define ACS_PRESENT     0x80
/* Code segment */
#define ACS_CSEG        0x18
/* Data segment */
#define ACS_DSEG        0x10
/* Read segment */
#define ACS_READ        0x02
/* Write segment */
#define ACS_WRITE       0x02
#define ACS_IDT         ACS_DSEG
/* Interrupt GATE 32 bits */
#define ACS_INT_386 	0x0E
#define ACS_INT         ( ACS_PRESENT | ACS_INT_386 )

#define ACS_CODE        (ACS_PRESENT | ACS_CSEG | ACS_READ)
#define ACS_DATA        (ACS_PRESENT | ACS_DSEG | ACS_WRITE)
#define ACS_STACK       (ACS_PRESENT | ACS_DSEG | ACS_WRITE)

/* Aligns the following strucs to 1 byte */
#pragma pack (1)

/* Segment descriptor */
typedef struct {
	word limit, base_l;byte base_m, access, attribs, base_h;
} DESCR_SEG;

typedef struct {
	char** jumpmap;
	char** screen;
	char** style;
} SHELL_INFO;

typedef struct {
	int height, width;
	int curX, curY;
	int cursorEnabled, textMode;
	SHELL_INFO* shell;
} VIDEO_MODE_INFO;



/* Interrupt descriptor */
typedef struct {
	word offset_l, selector;byte cero, access;word offset_h;
} DESCR_INT;

/* IDTR declaration  */
typedef struct {
	word limit;dword base;
} IDTR;

#endif

