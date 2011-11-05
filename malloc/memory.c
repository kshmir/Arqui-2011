#include "memory.h"
#define NOT_FOUND 0
#define FOUND 1
#define FIRST_PAGE 0x00200000

page_array pages_struct;
char* paginas[MAX_PAGES]; //vector de segmentos

int main(void){
	int i;
	char * p;
	float prueba;
	page_array headers; //struct de vectores de headers
	
	initHeader(&pages_struct.pages[0])	;
	
	//muestro lo que hay en el header
	for(i=0;i<MAX_HEADER_SIZE;i++)
			printf("%d ",pages_struct.pages[0].header[i]);
	printf("\n");
	printf("cantidad de bloques contiguos libres %d\n",pages_struct.pages[0].blocks_cont);
	gen_pages_index();
	printf("Mi nueva funcion para imprimir bloques\n");
	printPage(paginas[0]);
	
	// imprimo el espacio libre y en uso
	printf("libre: %d\nuso: %d \n", getFreeSpace(&pages_struct.pages[0]), getUsed(&pages_struct.pages[0]));
	
	// ahora voy a reserbar algunos sectores y liberar otros
	pages_struct.pages[0].header[0]=-2;
	pages_struct.pages[0].blocks_cont-=2; // xq arriba reserve 2 bloques 
	pages_struct.pages[0].header[1]=4;
	pages_struct.pages[0].header[2]=-8;
	pages_struct.pages[0].blocks_cont-=8; // xq arriba reserve 8 bloques
	pages_struct.pages[0].header[3]=-3;
	pages_struct.pages[0].blocks_cont-=3; // xq arriba reserve 3 bloques
	pages_struct.pages[0].header[4]=5;
	

	printf("libre: %d\nuso: %d \n", getFreeSpace(&pages_struct.pages[0]), getUsed(&pages_struct.pages[0]));
	for(i=0;i<MAX_HEADER_SIZE;i++)
			printf("%d ",pages_struct.pages[0].header[i]);
	printf("\n");
	printf("cantidad de bloques contiguos libres %d\n",pages_struct.pages[0].blocks_cont);
	printf("Mi nueva funcion para imprimir bloques\n");
	printPage(paginas[0]);
	//testeo de la funcion abs
	printf("abs(%d)=%d\nabs(%d)=%d\nabs(%d)=%d\n",-1,abs(-1),0,abs(0),2,abs(2));
	
	//testeo de la funcion getblocks
	printf("getBlocks(%d)=%d\n",31,getBlocks(31));
	printf("getBlocks(%d)=%d\n",32,getBlocks(32));
	printf("getBlocks(%d)=%d\n",33,getBlocks(33));
	printf("getBlocks(%d)=%d\n",0,getBlocks(0));
	
	//testeo de la funcion malloc
	
	for(i=0;i<MAX_HEADER_SIZE;i++)
			printf("%d ",pages_struct.pages[0].header[i]);
	printf("\n");
	printf("libre: %d uso: %d \n", getFreeSpace(&pages_struct.pages[0]), getUsed(&pages_struct.pages[0]));
	
	myMalloc(32);
	printf("myMalloc(32)\n");
	for(i=0;i<MAX_HEADER_SIZE;i++)
			printf("%d ",pages_struct.pages[0].header[i]);
	printf("\n");
	printf("libre: %d uso: %d \n", getFreeSpace(&pages_struct.pages[0]), getUsed(&pages_struct.pages[0]));
	
	myMalloc(3*32);
	printf("myMalloc(96)\n");
	for(i=0;i<MAX_HEADER_SIZE;i++)
			printf("%d ",pages_struct.pages[0].header[i]);
	printf("\n");
	printf("libre: %d uso: %d \n", getFreeSpace(&pages_struct.pages[0]), getUsed(&pages_struct.pages[0]));
	
	myMalloc(31);
	printf("myMalloc(31)\n");
	for(i=0;i<MAX_HEADER_SIZE;i++)
			printf("%d ",pages_struct.pages[0].header[i]);
	printf("\n");
	printf("libre: %d uso: %d \n", getFreeSpace(&pages_struct.pages[0]), getUsed(&pages_struct.pages[0]));
	
	myMalloc(33);
	printf("myMalloc(33)\n");
	for(i=0;i<MAX_HEADER_SIZE;i++)
			printf("%d ",pages_struct.pages[0].header[i]);
	printf("\n");
	printf("libre: %d uso: %d \n", getFreeSpace(&pages_struct.pages[0]), getUsed(&pages_struct.pages[0]));
	printf("myMalloc(20)\n");
	p = myMalloc(20);
	printf("El puntero p: %p \n",p);
	printf("pagina 0: %p \n",paginas[0]);
	printf("Espacio usado: %d \n", getUsed(&pages_struct.pages[0]));
	printf("desplazo %d\n",(p-paginas[0])/32);
	
	for(i=0;i<MAX_HEADER_SIZE;i++)
			printf("%d ",pages_struct.pages[0].header[i]);
	printf("\n");
	printf("libre: %d uso: %d \n", getFreeSpace(&pages_struct.pages[0]), getUsed(&pages_struct.pages[0]));
	
	printf("myFree(p)\n");
	myFree(p);
	for(i=0;i<MAX_HEADER_SIZE;i++)
			printf("%d ",pages_struct.pages[0].header[i]);
	printf("\n");
	printf("libre: %d uso: %d \n", getFreeSpace(&pages_struct.pages[0]), getUsed(&pages_struct.pages[0]));
	
	//ahora voy a realizar un free de una posicion de memoria ya liberada
	printf("myFree(p)\n");
	myFree(p);
	for(i=0;i<MAX_HEADER_SIZE;i++)
			printf("%d ",pages_struct.pages[0].header[i]);
	printf("\n");
	printf("libre: %d uso: %d \n", getFreeSpace(&pages_struct.pages[0]), getUsed(&pages_struct.pages[0]));
	
	//ahora voy a realizar un free de una posicion de memoria inexistente
	printf("myFree(p+320)\n");
	myFree(p+320);
	for(i=0;i<MAX_HEADER_SIZE;i++)
			printf("%d ",pages_struct.pages[0].header[i]);
	printf("\n");
	printf("libre: %d uso: %d \n", getFreeSpace(&pages_struct.pages[0]), getUsed(&pages_struct.pages[0]));
	

	//printPages();
	printMap(paginas[0]);
	printf("%d\n",cantMaxBlocks(pages_struct.pages[0].header));
	printPage(paginas[0]);
	printf("funciono \n");


	
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
		mem_header* actual;
		int bloques = getBlocks(size);
		
		if( size > 0 && size < MAX_PAGE_SIZE){
			/* Itero sobre el pages para ver si cuento con un segmento de memorio del tamaño solicitado */
			for (i = 0; i < MAX_PAGES && flag == NOT_FOUND; i++){
				if((pages_struct.pages[i].blocks_cont) >= bloques){
					actual = &pages_struct.pages[i]; /* Header */
					for(j = 0, k = -1; j < MAX_HEADER_SIZE && actual->header[j] != bloques && actual->header[j] != 0; j++){
						/* Busca el menor bloque en el que yo entre */
						if( actual->header[j] >= bloques){
							if( k == -1 ){
								k = j;
							}else{	
								k = (actual->header[j] < actual->header[k] ? j : k);
							}	
						}
						
					}
					//te olvidaste cuando sale xq entra justo
					if (actual->header[j] == bloques){
						actual->header[j] *= -1;
					}
					// te estabas olvidando de fijarte si salio por un cero
					else if( j >= MAX_HEADER_SIZE ||  actual->header[j] == 0){
						aux = actual->header[k] - bloques;
						//te habias olvidado de multiplicar los bloques por -1 para que figuren como usados
						actual->header[k] = bloques*-1;
						
						j = k++;
						while(actual->header[k] != 0 && k < MAX_HEADER_SIZE){
							aux2 = actual->header[k];
							actual->header[k] = aux;
							aux = aux2;
							k++;
						}if(actual->header[k] == 0){
							actual->header[k] = aux;
						}
					}
					/* ans = EL SECTOR DE MEMORIA ES [i][j] */
					flag = FOUND;
					//corregirlo contando cuantos bloques recorrio
					for(k=0, ans=paginas[i];k<j;k++)
						ans += abs(actual->header[k])*PADDING;
				}
			}
			
		}
		return ans;
}
/* Segun un size, la cantidad minima de bloques necesitada */
int getBlocks(size_t size){
	int aux = 0;
	if (size >=0)
	 aux=size/PADDING + (size % PADDING == 0 ? 0 : 1);
	return aux; 
}
	

size_t getUsed(mem_header* page_header){
		
	size_t sum = 0;
	int i;
	if (page_header!=NULL){
		for (i = 0; i < MAX_HEADER_SIZE && page_header -> header[i] != 0; i++){
			sum += ((page_header -> header)[i] > 0 ? 0 : (size_t)((page_header -> header)[i]));
		}
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
	mem_header* actual;
	/* Calculo a que pagina debo momverme*/
	i = (int)(p - (void*)paginas[0])/ MAX_PAGE_SIZE;
	actual = &pages_struct.pages[i];
	//original vicky
	//aux = (int)p - (i * MAX_PAGE_SIZE);
	
	// modificacion de eze
	aux = p - (void*)paginas[i];
	
	if( aux % PADDING == 0){
	aux /= PADDING;
	for(j = 0, k = 0; j < MAX_HEADER_SIZE && aux > 0; j++){
		
		aux = aux - abs(actual->header[j]);
		//te olvidabas de incrementar k cuando aux era 0
		if(aux >=0){
			k++;
		}
	}
	if(aux == 0 && actual->header[k] < 0){
	
		actual->header[k] = actual->header[k] * -1;
		if (k>0 && actual->header[k-1]>0)
			k--;
		
		dif=k;
		while(k< MAX_HEADER_SIZE && actual->header[k]!=0  && dif<MAX_HEADER_SIZE)
		{
			
			if(actual->header[k]>0 && (dif+1<MAX_HEADER_SIZE) && actual->header[dif+1]>0)
			{
				dif++;
				actual->header[k]+=actual->header[dif];
				if (dif+1<MAX_HEADER_SIZE && actual->header[dif+1]>0)
						actual->header[k]+=actual->header[dif++];
				
			}
			k++;
			dif++;
			if (dif<MAX_HEADER_SIZE)
				actual->header[k]= actual->header[dif];
		}
	}
		for (j=MAX_HEADER_SIZE-1; j>=0 && actual->header[j]>0; j--)
				actual->header[j]=0;
	}
	
	return;
}
int abs(int num)
{
	return (num>=0?num:num*-1);
}

void initHeader(mem_header* h1){
	int i;
	if (h1!=NULL && h1->header!=NULL){
		for (i=0; i<MAX_HEADER_SIZE;i++)
			h1->header[i]=0;
	h1->blocks_cont = MAX_HEADER_SIZE;
	}
	
}
 void gen_pages_index(){
	 
		int i;
		void* p=(void*)FIRST_PAGE;
		for (i=0;i<MAX_PAGES;i++){
				paginas[i]=p+(i*MAX_PAGE_SIZE);
			
			}
	 
}

void printPages()
{
	int i, count;
	char pointer[9];
	
	printf("BASE ADDRESS   |  USED\n");
	printf("----------------------\n");
	for(i = 0, count=0; i < MAX_PAGES;){
		while(count<20 && i<MAX_PAGES){
			printf("%s       |  %d\n",toHexa(pointer,paginas[i]),getUsed(&pages_struct.pages[i]));
			i++;
			count++;
			}
		if (i!=MAX_PAGES){
			printf("Please enter any key for more results\n");
			getchar();
			count = 0;
			printf("BASE ADDRESS   |  USED\n");
			printf("----------------------\n");
			}
		}
}

void printPage(void* p){
	char end = 0;
	int i;
	int count;
	char indentation[4];
	int free = MAX_PAGE_SIZE;
	char* puntero_ppio_header;
	int page_index = getPageIndex(p);
	puntero_ppio_header = pages_struct.pages[page_index].header;
	
	if( page_index != -1){
		printf("U: Used - F: Free\n|");
		for(i = 0, count = 0; i < MAX_HEADER_SIZE && !end; ){
		if(count < 6){
			free = free - abs(puntero_ppio_header[i] * PADDING);
			count++;
			if(puntero_ppio_header[i] < 0){
				printf(" U: %s%d |", indent(indentation,puntero_ppio_header[i]*(-PADDING)),puntero_ppio_header[i]*(-PADDING));
			}
			else{
				if(puntero_ppio_header[i] > 0){
					printf(" F: %s%d |", indent(indentation,puntero_ppio_header[i]*(PADDING)), puntero_ppio_header[i]*(PADDING));
				}else{
					printf(" F: %s%d |\n", indent(indentation,free), free);
					end = 1;
				}	
			}
			i++;
		}else{
			printf("\n|");
			count = 0;
		}	
	}}
	else{
		printf("Invalid Pointer \n");
	}
}
int getPageIndex (void* p){
	int i;
	int found = 0;
	
	for (i = 0; i < MAX_PAGES && !found; i++){
		found = ((p >= (void*)paginas[i]) && (p < (void*)paginas[i] + MAX_PAGE_SIZE) ? 1 : 0);
	}
	return (found ? (i - 1) : -1);
}

char* indent(char* pchar, int size)
{
   int count = 0;
   int i;
    if (pchar !=NULL){ 

		if(size<1000 && size>99){
            count = 1;
		}
		else if(size<100 && size>9){
            count = 2;
		}
		else if(size<10 && size>=0){
            count = 3;
		}
		for(i=0;i<count;i++){
			pchar[i]=' ';
		}
		pchar[i]='\0';
	}
	return pchar;
}

void printMap(void* p){
	
	char pointer[9];
	char end = 0;
	int i;
	int count;
	
	char* puntero_ppio_header;
	int page_index = getPageIndex(p);
	puntero_ppio_header = pages_struct.pages[page_index].header;
	
	if( page_index != -1){
		printf("POINTER        |  USED\n");
		printf("----------------------\n");
		count++;
		for(i = 0, count = 0; i < MAX_HEADER_SIZE;){
			if(count < 10){
				if(puntero_ppio_header[i] < 0){
					printf("%s       |  %d\n",toHexa(pointer,paginas[i]),puntero_ppio_header[i] * (-PADDING));
				count++;
				}
				i++;	
			}else{
				printf("Please enter any key for more results\n");
				getchar();
				count = 0;
				printf("POINTER        |  USED\n");
				printf("----------------------\n");		
			}
		}
	
	}else{
		printf("Invalid Pointer \n");
	}
}

char* toHexa(char* hexa, char* p){
	
	int r;
	int i;
	int num = (int)p;
	
	
	hexa[0] = '0';
	hexa[1] = 'x';
	
	for(i = 7; i > 1; i--){
		r = num %16;
		if( r < 10){
			hexa[i] = r +'0';
		}else{
			hexa[i] = r - 10 + 'a';
		}
	num /= 16;
	}
	hexa[8] = '\0';
	
	return hexa;
}

int cantMaxBlocks(char* header){
	int i;
	int ret = 0;
	int aux = MAX_HEADER_SIZE;
	
	for(i = 0; header[i] != 0; i++){
		aux = aux - abs(header[i]);		
		if( header[i] > 0 && ret < header[i]){
			ret = header[i];
		}
	}
	
	if(ret < aux){
		ret = aux;
	}	
	
	return ret;
}

void printBlock(void* p){
	
	int bytes;
	int header ;
	
	
	
}
