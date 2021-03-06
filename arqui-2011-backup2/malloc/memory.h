#include "../src/libs/stdio.h"
#include "../src/libs/stdlib.h"

#define MAX_HEADER_SIZE 128 /* Tamaño del header */
#define MAX_PAGE_SIZE 4096 /* 4K */
#define MAX_PAGES 256 /* Cantidad de paginas */
#define PADDING 32 /* Tamaño minimo que se puede allocar */
#define NOT_FOUND 0
#define FOUND 1


typedef struct mem_header{
	
	char header[MAX_HEADER_SIZE];
	unsigned char blocks_cont; /*= MAX_HEADER_SIZE; /* cantidad minima contigua de bloques, al principio 128 */
	
}mem_header;

typedef struct page_array{
	
	struct mem_header pages[MAX_PAGES];
	
}page_array;



void * myMalloc(size_t size); //TESTED
void * myCalloc(size_t size);
int getBlocks(size_t size); //TESTED
size_t getUsed(mem_header* page_header); //TESTED
size_t getFreeSpace(mem_header* header); //TESTED
void myFree(void* p);
int abs(int num); //TESTED
void initHeader(mem_header* h1);
void gen_pages_index();
void gen_pages_index2();
void printPages();
void printPage(void* p);
int getPageIndex (void* p);

char* indent(char* pchar, int size);

void printMap(void* p);
char* toHexa(char* hexa, char* p);
int cantMaxBlocks(char* header);

int getHeaderIndex (void* p);
void* myRealloc(void* p, size_t new_size);
void mymemcpy(void* origen, size_t size, void* destino);
void printBlock(void* p);
int toInt(int size, char** p);
int myStrlen(char* s);
int myPow(int base, int exp);
void toUpperString(char* s);
