#include "../../include/kasm.h"
#include "../../include/defs.h"
#include "../drivers/keyboard.h"
#include "../drivers/video.h"
#include "../shell.h"

DESCR_INT idt[0x81]; /* IDT de 10 entradas*/
IDTR idtr; /* IDTR */

int tickpos = 640;
int videoPos = 320;
char *vidmem = (char *) 0xb8000;

void setVideoPos(int a) {
	videoPos = a;
}

void int_08() {

}
/* Handler del teclado */
void int_09(char scancode) {
	// TODO: DEFINES HERE!
	int flag = scancode >= 0x02 && scancode <= 0x0d;
	flag = flag || (scancode >= 0x10 && scancode <= 0x1b);
	flag = flag || (scancode >= 0x1E && scancode <= 0x29);
	flag = flag || (scancode >= 0x2b && scancode <= 0x35);
	if (flag) {
		pushC(scanCodeToChar(scancode)); //guarda un char en el stack
		shellKBInterrupt();
	} else
		controlKey(scancode);

}

/* Escribe en la posicion de memoria s el
 * caracter c, n veces */
void setBytes(void *s, char* c, int n) {
	unsigned char *p = s;
	int i;

	for (i = 0; i < n; i++)
		p[i] = (char) c[i];
}

/* Handler de INT 80h */
void int_80(int systemCall, int fd, char *buffer, int count) {
	int i, j;

	if (systemCall == WRITE) //write
	{
		if (fd == STDOUT) //PANTALL
		{
			setBytes(vidmem + videoPos, buffer, 2);

		}

	} else if (systemCall == READ) //read
	{
		//#TODO: no andan los in y out.
		if (fd == STDOUT) {

		}
	}
}

/**********************************************
 kmain()
 Punto de entrada de c�digo C.
 *************************************************/

kmain() {

	int i, num;

	/* Borra la pantalla. */

	k_clear_screen();

	shellStart();

	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

	setup_IDT_entry(&idt[0x08], 0x08, (dword) &_int_08_hand, ACS_INT, 0);

	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ1    */

	setup_IDT_entry(&idt[0x09], 0x09, (dword) &_int_09_hand, ACS_INT, 0);

	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE int80h    */

	setup_IDT_entry(&idt[0x80], 0x80, (dword) &_int_80_hand, ACS_INT, 0);

	/* Carga de IDTR */

	idtr.base = 0;
	idtr.base += (dword) &idt;
	idtr.limit = sizeof(idt) - 1;

	_lidt(&idtr);

	_Cli();

	/* Habilito interrupcion de timer tick*/
	_mascaraPIC1(0xFC);
	_mascaraPIC2(0xFF);
	_Sti();

	/* KeepAlive loop */
	while (1) {
	}

}

