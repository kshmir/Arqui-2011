#include "stdlib.h"

char heap_space[1024*1024*4];
size_t offset;

void * malloc(size_t size)
{
     void* ret = 0;
     ret = heap_space + offset;
     offset += size;
     return ret;
}

void * calloc(size_t size, size_t cols)
{
     char* ret = (char*)malloc(size * cols);
     int i = 0;
     for(; i < size; i++)
        ret[i] = 0;
     return ret;
}

void * realloc(void * ptr, size_t size)
{
     char* ret = (char*)malloc(size);
     int i = 0;
     for(; i < size; i++)
        ret[i] = 0;
     return ret;
}

void free(void* ptr)
{
     return;
}

int time_lies = 0;

int _time = 0;
int time(void *ptr)
{
	_time += 10;
	return  _time;
}
int srand(int i)
{
	time_lies = (time_lies + 3) * (time_lies+31);
	return  time_lies;
}

int rand()
{
	time_lies = (time_lies + 3) * (time_lies+31);
	return  time_lies;
}


