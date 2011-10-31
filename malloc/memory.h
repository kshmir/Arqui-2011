#define MAX_HEADER_SIZE 128 /* Tamaño del header */
#define MAX_PAGE_SIZE 4096 /* 4K */
#define MAX_PAGES 1 /* Cantidad de paginas */
#define PADDING 32 /* Tamaño minimo que se puede allocar */

typedef struct mem_header{
	
	char header[MAX_HEADER_SIZE];
	unsigned char blocks_cont; /*= MAX_HEADER_SIZE; /* cantidad minima contigua de bloques, al principio 128 */
	
}mem_header;

typedef struct page_array{
	
	struct mem_header pages[MAX_PAGES];
	
}page_array;
