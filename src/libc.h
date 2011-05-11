#ifndef LIBC_H
#define LIBC_H 1
#include "../include/kc.h"
#include "../src/IO.h"
#include "../src/shell.h"

void k_clear_screen();
void k_maxi_screen();

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
		byte cero);
#endif

