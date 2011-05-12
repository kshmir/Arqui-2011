#include "stdlib.h"

char heap_space[1024*1024*4];
size_t offset;

void * malloc(void* ptr, size_t size)
{
     void* ret = 0;
     ret = heap_space + offset;
     offset += size;
     return ret;
}

void * calloc(void * ptr, size_t size)
{
     char* ret = (char*)malloc(ptr,size);
     int i = 0;
     for(; i < size; i++)
        ret[i] = 0;
     return ret;
}

void * realloc(void * ptr, size_t size)
{
     char* ret = (char*)malloc(ptr,size);
     int i = 0;
     for(; i < size; i++)
        ret[i] = 0;
     return ret;
}

void free(void* ptr)
{
     return;
}
