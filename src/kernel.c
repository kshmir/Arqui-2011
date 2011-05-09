#include "../include/kasm.h"
#include "../include/defs.h"
#include "../src/keyboard.h"
#include "../src/IO.h"
#include "../src/shell.h"


DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

int tickpos=640;

void int_08() {

	//k_maxi_screen();
    //char *video = (char *   ) 0xb8000;
    //video[tickpos+=2]='a';
}

void int_09(char scancode) {
	//putC('o');
	//gk_maxi_screen();
	//word *c = 0x0041a;
	//*c=0;
	//char res = 'o';
    //char *video = (char *) 0xb8000;
    //video[tickpos+=2]=scanCodeToChar(scancode);
    int flag=scancode >=0x02 && scancode <=0x0d;
    flag=flag || (scancode >=0x10 && scancode <=0x1b);
    flag=flag || (scancode >=0x1E && scancode <=0x29);
    flag=flag || (scancode >=0x2b && scancode <=0x35);
    if(flag) {
		pushC(scanCodeToChar(scancode)); //guarda un char en el stack
		shellKBInterrupt();
		//putC(getC());
	}else
		controlKey(scancode);

}

/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/

kmain() 
{

        int i,num;

/* Borra la pantalla. */ 

	k_clear_screen();
	
	shellStart();

/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

		
		setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
        
/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ1    */

        setup_IDT_entry (&idt[0x09], 0x09, (dword)&_int_09_hand, ACS_INT, 0);
	
/* Carga de IDTR    */

	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

	_Cli();
/* Habilito interrupcion de timer tick*/

        _mascaraPIC1(0xFC);
        _mascaraPIC2(0xFF);
        
	_Sti();

        while(1)
        {
        }
	
}

