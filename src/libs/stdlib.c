#include "stdlib.h"
#include "../../include/kernel.h"

//***** All the following code is just not cool, but it works ¨*****//

char heap_space[1024*1024*8];
size_t offset;

// Roughly allocs some memory
void * malloc(size_t size)
{
     void* ret = 0;
     ret = heap_space + offset;
     offset += size;
     return ret;
}

// Roughly callocs some memory
void * calloc(size_t size, size_t cols)
{
     char* ret = (char*)malloc(size * cols);
     int i = 0;
     for(; i < size; i++)
        ret[i] = 0;
     return ret;
}

// Roughly reallocs some memory
void * realloc(void * ptr, size_t size)
{
     char* ret = (char*)malloc(size);
     int i = 0;
     return ret;
}

// The cake is a lie, but the cake follows the standard implementation.
void free(void* ptr)
{
     return;
}

int time_lies = 0;

int _time = 0;
// Lies
int time(void *ptr)
{
	_time += 10 * _ticks(); // Well, this is kinda random right?
	return  _time;
}
// Lies
int srand(int i)
{
	time_lies = (time_lies + 3) * (time_lies+31);
	return  time_lies;
}

// More lies
int rand()
{
	time_lies = (time_lies + 3) * (time_lies+31);
	return  time_lies;
}
// We needed all this weird code to build something "random".

