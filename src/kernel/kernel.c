#include "../../include/kernel.h"
#include "../../include/kasm.h"
#include "../../include/defs.h"

#include "../startup/start.h"
#include "../drivers/keyboard.h"
#include "../drivers/video.h"
#include "../shell.h"

DESCR_INT idt[0x81]; /* IDT de 10 entradas*/
IDTR idtr; /* IDTR */

int must_update = 0;
double ticks = 0;
int videoPos = 0;
int cursorEnabled = 1;
char *vidmem = (char *) 0xb8000;
double res;

void setCursor(int b)
{
	cursorEnabled = b;
}

void setVideoPos(int a) {
	videoPos = a;
	if (cursorEnabled) _setCursor(a/2);
}

double* getFrequency(){
	ticks=1;
	int a=0;
	//_doManyCicles();
	a=_rdtsc();
	int i;
	for (i=0;i<100000000;i++);
	a=_rdtsc()-a;
	if(a<0)
		a*=-1;
	if(ticks!=1)
	res=a/((ticks-1)*0.055); //multiplico por 48 xq reduje en 48 la cantidad de ciclos en _doManyCicles
	return &res;
	}

void int_08() {
	ticks++;
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
		must_update++;
	} else
		must_update += controlKey(scancode);


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
			setBytes(vidmem + videoPos, buffer, count);
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
 Punto de entrada de c—digo C.
 *************************************************/

kmain() {

	int i, num;

	/* Borra la pantalla. */



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

	initVideo();
	internalShellStart();
	shellStart();

	/* KeepAlive loop */
	while (1) {
		init();
		//internalShellStart();
		must_update--;
	}

}
