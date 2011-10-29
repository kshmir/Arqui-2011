#ifndef _START_H_

#define _START_H_

void setup_IDT_entry(DESCR_INT*item, byte selector, dword offset, byte access, byte cero);

#endif
