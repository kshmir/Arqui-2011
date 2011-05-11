#include "../src/libc.h"
/***************************************************************
 *k_clear_screen
 *
 * Borra la pantalla en modo texto color.
 ****************************************************************/

void k_clear_screen() {
	int i = 0;
	moveCursorToStart();
	while (i++ < (MAX_COLS * (MAX_ROWS + 1))) {
		putC(' ');
	}
	moveCursorToStart();
}

void k_maxi_screen() {
	char *vidmem = (char *) 0xb8000;
	unsigned int i = 0, j = 0;
	char a = 'a';
	while (j < 80) {
		while (i < 25 * 2) {
			vidmem[i * j] = a;
			i++;
			vidmem[i++] = WHITE_TXT;
		}
		j++;
		a++;
	}
}

/***************************************************************
 *setup_IDT_entry
 * Inicializa un descriptor de la IDT
 *
 *Recibe: Puntero a elemento de la IDT
 *	 Selector a cargar en el descriptor de interrupcion
 *	 Puntero a rutina de atencion de interrupcion
 *	 Derechos de acceso del segmento
 *	 Cero
 ****************************************************************/

void setup_IDT_entry(DESCR_INT *item, byte selector, dword offset, byte access,
		byte cero) {
	item->selector = selector;
	item->offset_l = offset & 0xFFFF;
	item->offset_h = offset >> 16;
	item->access = access;
	item->cero = cero;
}

