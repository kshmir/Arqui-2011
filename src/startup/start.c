#include "../../include/defs.h"
#include "start.h"

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

void setup_IDT_entry(DESCR_INT *item, byte selector, dword offset, byte access, byte cero) {
	item->selector = selector;
	item->offset_l = offset & 0xFFFF;
	item->offset_h = offset >> 16;
	item->access = access;
	item->cero = cero;
}

void setup_DESCR_PAGE(DESCR_PAGE * item,dword address) {
	item->direction_h = direction_h ;
	item->direction_low = direction_low &0xF0;
	item->atts = 0x03;
} 

