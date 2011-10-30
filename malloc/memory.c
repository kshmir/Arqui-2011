#include "memory.h"
#include <stdlib.h>
#define NOT_FOUND 0
#define FOUND 1

page_array pages_struct;

int main(void){
	int i;
	char** paginas;
	for (i=0; i<MAX_PAGES;i++){
		
		if ((paginas=malloc(MAX_PAGE_SIZE))==NULL){
			printf("no hay espacio suficiente\n");
			return 1;
		}
	}
	
	return 0;
}

void* myMalloc(size_t size){
		
		/* Necesito el puntero a la base de la pagina */
		void *ans = NULL;
		int i=0;
		int j=0;
		int k=0; /* Indice de la menor posicion posible */
		int cant_bloques=0;
		int aux;
		int aux2;
		int flag = NOT_FOUND;
		mem_header actual;
		int bloques = getBlocks(size);
		
		
		if( size > 0 && size < MAX_PAGE_SIZE){
			/* Itero sobre el pages para ver si cuento con un segmento de memorio del tamaño solicitado */
			for (i = 0; i < MAX_PAGES && flag == NOT_FOUND; i++){
				if((pages_struct.pages[i].blocks_cont) >= bloques){
					actual = pages_struct.pages[i]; /* Header */
					for(j = 0, k = -1; j < MAX_HEADER_SIZE && actual.header[j] != bloques && actual.header[j] != 0; j++){
						/* Busca el menor bloque en el que yo entre */
						if( actual.header[j] >= bloques){
							if( k == -1 ){
								k = j;
							}else{	
								k = (actual.header[j] < actual.header[k] ? j : k);
							}	
						}
						
					}
					if( j >= MAX_HEADER_SIZE){
						aux = actual.header[k] - bloques;
						actual.header[k] = bloques;
						j = k++;
						while(actual.header[k] == 0 && k < MAX_HEADER_SIZE){
							aux2 = actual.header[k];
							actual.header[k] = aux;
							aux = aux2;
							k++;
						}if(actual.header[k] == 0){
							actual.header[k] = aux;
						}
					}
					/* ans = EL SECTOR DE MEMORIA ES [i][j] */
					flag = FOUND;
				}
			}
			
		}
			
		return ans;
}
/* Segun un size, la cantidad minima de bloques necesitada */
int getBlocks(size_t size){
	
	return size/PADDING + (size % PADDING == 0 ? 0 : 1);
}
	

size_t getUsed(mem_header* page_header){
		
	size_t sum = 0;
	int i;
	for (i = 0; i < MAX_HEADER_SIZE && page_header -> header[i] != 0; i++){
		sum += ((page_header -> header)[i] > 0 ? 0 : (size_t)((page_header -> header)[i]));
	}
	return sum * PADDING * (-1);
}

size_t getFreeSpace(mem_header* header){
	
	return MAX_PAGE_SIZE - getUsed(header);
}

void* myCalloc(size_t size){
	
	int i;
	char* p = (char*) myMalloc(size);
	int bloques = getBlocks(size);
	
	if(p != NULL){
		for (i = 0; i < bloques * PADDING; i++){
			p[i] = 0;
		}
	}
	return p;
	
}

void myFree(void* p){
	
	int i;
	int j;
	int k;
	int dif;
	int value;
	int aux;
	mem_header actual;
	i = (int)p / MAX_PAGE_SIZE;
	actual = pages_struct.pages[i]; 
	aux = (int)p - (i * MAX_PAGE_SIZE);
	
	if( aux % PADDING == 0){
	aux /= PADDING;
	for(j = 0, k = 0; j < MAX_HEADER_SIZE && aux > 0; j++){
		
		aux = aux - abs(actual.header[j]);
		if(aux > 0){
			k++;
		}
	
	}
	if(aux == 0 && actual.header[k] < 0){
	
		actual.header[k] = actual.header[k] * -1;
		if (k>0 && actual.header[k-1]>0)
			k--;
		
		dif=k;
		while(k< MAX_HEADER_SIZE && actual.header[k]!=0  && dif<MAX_HEADER_SIZE)
		{
			
			if(actual.header[k]>0 && (dif+1<MAX_HEADER_SIZE) && actual.header[dif+1]>0)
			{
				dif++;
				actual.header[k]+=actual.header[dif];
				if (dif+1<MAX_HEADER_SIZE && actual.header[dif+1]>0)
						actual.header[k]+=actual.header[dif++];
				
			}
			k++;
			dif++;
			if (dif<MAX_HEADER_SIZE)
				actual.header[k]= actual.header[dif];
		}
	}
		for (j=MAX_HEADER_SIZE-1; j>=0 && actual.header[j]>0; j--)
				actual.header[j]=0;
	}
	
	return;
}
int abs(int num)
{
	return (num>=0?num:num*-1);
}
