

/********************************** 
 *
 *  Kernel
 *
 ***********************************/

#ifndef _kernel_
#define _kernel_

#define OS_PID	0

// TODO: Add description for this.
int (*player)(void);
int _ticks();

void setCursor(int b);

/** Useful typedefs */
typedef int size_t;
typedef short int ssize_t;
typedef enum eINT_80 {
	_WRITE = 0, _READ //TODO: Fix calls to make it compile
} tINT_80;
typedef enum eUSER {
	U_KERNEL = 0, U_NORMAL
} tUSERS;

/* __write
 * Recibe como parametros:
 * - File Descriptor
 * - Buffer del source
 * - Cantidad
 **/
size_t __write(int fd, const void* buffer, size_t count);

/* __read
 * Recibe como parametros:
 * - File Descriptor
 * - Buffer a donde escribir
 * - Cantidad
 **/
size_t __read(int fd, void* buffer, size_t count);

#endif
