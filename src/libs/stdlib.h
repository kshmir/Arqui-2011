/*
 * stdlib.h
 *
 *  Created on: May 11, 2011
 *      Author: cristian
 */

#ifndef _STDLIB_H_

#include "../../include/kernel.h"

#define _STDLIB_H_

void * malloc(void* ptr, size_t size);
void * calloc(void* ptr, size_t size);
void * realloc(void* ptr, size_t size);
void free(void* ptr);

#endif /* STDLIB_H_ */