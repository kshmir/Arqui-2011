#include "libmem.h"
#include "stdio.h"



page_array pages_struct;
char* paginas[MAX_PAGES]; //vector de segmentos

void* myMalloc(int size){
		
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
						
						if(k!=-1){
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
						else
							actual->header[j]= bloques*-1;
					}
					/* ans = EL SECTOR DE MEMORIA ES [i][j] */
					flag = FOUND;
					//corregirlo contando cuantos bloques recorrio
					for(k=0, ans=paginas[i];k<j;k++)
						ans += abs(actual->header[k])*PADDING;
				}
			}
			
		}
		//CALCULAR BLOQUES DISPONIBLES
		actual->blocks_cont=cantMaxBlocks(actual->header);
		return ans;
}
/* Segun un size, la cantidad minima de bloques necesitada */
int getBlocks(int size){
	int aux = 0;
	if (size >=0)
	 aux=size/PADDING + (size % PADDING == 0 ? 0 : 1);
	return aux; 
}
	

int getUsed(mem_header* page_header){
		
	int sum = 0;
	int i;
	if (page_header!=NULL){
		for (i = 0; i < MAX_HEADER_SIZE && page_header -> header[i] != 0; i++){
			sum += ((page_header -> header)[i] > 0 ? 0 : (int)((page_header -> header)[i]));
		}
	}
	return sum * PADDING * (-1);
}

int getFreeSpace(mem_header* header){
	
	return MAX_PAGE_SIZE - getUsed(header);
}

void* myCalloc(int size){
	
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
	i =getPageIndex(p);
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
		//aca busco si mi antecesor es un espacio libre
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
			if (dif-k>1)
				actual->header[k]= actual->header[dif-1];
		}
		
	}
		for (j=MAX_HEADER_SIZE-1; j>=0 && actual->header[j]>0; j--)
				actual->header[j]=0;
	
	actual->blocks_cont=cantMaxBlocks(actual->header);
	}
	return;
}
int abs(int num){
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


void printPages(){
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

char* indent(char* pchar, int size){
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

void* myRealloc(void* p, int new_size){
	int index;
	void* aux;
	int actual_size;
	//pruebo si se hay espacio disponible en la misma pagina u otra para mover todo el paquete
	if((aux=myMalloc(new_size))!=NULL)
	{
	
	//pages_struct
		//copio todos los valores antes de liberar la memoria
		actual_size = PADDING*-1*pages_struct.pages[getPageIndex (p)].header[getHeaderIndex(p)];
		//mymemcpy(p, -1*pages_struct.pages[getPageIndex (p)].header[getHeaderIndex(p)], aux);
		
		myFree(p);
		p=aux;
	}
	else{
		//me fijo si me puedo expander (aca se trabaja sobre header)
		
		if((index=getHeaderIndex(p))!=-1){
			//me fijo si tengo ANTECESOR, si esta libre y entre el y yo sumamos espacio suficiente
			
			
			if(index>0 && pages_struct.pages[getPageIndex (p)].header[index-1]>0 && 
				(pages_struct.pages[getPageIndex (p)].header[index-1] + (pages_struct.pages[getPageIndex (p)].header[index]*-1))*PADDING>=new_size){
				//en caso de que se cumplan las condiciones pedidas copio y luego hago el malloc y free
				//el vector origen va a ser p y el vector destino va a ser p- (lo que ocupa mi antecesor)
				
				mymemcpy(p, PADDING*-1*pages_struct.pages[getPageIndex (p)].header[index],p-(pages_struct.pages[getPageIndex (p)].header[index-1]*PADDING));
				myFree(p);
				p=myMalloc(new_size);
			}
			//me fijo si tengo SUCESOR, si esta libre y si el y yo sumados sumamos espacio suficiente
			else if(index<MAX_HEADER_SIZE-1 && pages_struct.pages[getPageIndex (p)].header[index+1]>0 && 
					(pages_struct.pages[getPageIndex (p)].header[index+1] + 
					(pages_struct.pages[getPageIndex (p)].header[index]*-1))*PADDING>=new_size){
					//en caso de que se cumplan las condiciones pedidas hago el malloc y free y deberia autoexpandirse solo
					//debido a que primero trata de ubicarlo siempre en un segmetno ya existente por lo que si ingrresa por aca
					//significa que no hay espacios mayores
					myFree(p);
					p=myMalloc(new_size);
					
			}
			//me fijo si tengo sucesor y antecesor y juntos logramos ocupar el espacio pedido.
			else if(index<MAX_HEADER_SIZE-1 && index>0 && pages_struct.pages[getPageIndex (p)].header[index+1]>0 && 
					pages_struct.pages[getPageIndex (p)].header[index-1]>0 && 
					(pages_struct.pages[getPageIndex (p)].header[index-1] + pages_struct.pages[getPageIndex (p)].header[index+1] + (pages_struct.pages[getPageIndex (p)].header[index]*-1))*PADDING>=new_size){
					//en caso de que se cumplan las condiciones pedidas copio y luego hago el malloc y free
					//el vector origen va a ser p y el vector destino va a ser p- (lo que ocupa mi antecesor)
					mymemcpy(p, PADDING*-1*pages_struct.pages[getPageIndex (p)].header[index],p-(pages_struct.pages[getPageIndex (p)].header[index-1]*PADDING));
					myFree(p);
					p=myMalloc(new_size);
					}
			else
				p = NULL;
		}
		else //si no hay indice de header retorna null y no migra nada
			p = NULL;
	}
	
	printf("-------%c\n",p==NULL?'s':'n');
	return p;
}

int getHeaderIndex (void* p){
	int page_index, index = -1, bloques, aux;
	
	//obtengo el indice de pagina y calculo los bloques que se desplazo p
	if((page_index=getPageIndex(p))!=-1){
		bloques = ((int)((char*)p - (char*)paginas[page_index]))/PADDING;
		aux= bloques;
		//itero buscando el indice sobre el header
		for (index = 0; index<MAX_HEADER_SIZE && aux>0;index++){
				aux -= abs(pages_struct.pages[page_index].header[index]); 
		
		}
		index=(aux==0? index:-1);
	}
	return index;
}

void mymemcpy(void* origen, int size, void* destino){
	int i;
	char* o;
	char* d;
	
	o = (char*)origen;
	d = (char*)destino;
	for(i=0; i<(size/sizeof(char));i++){
		//printf("%d-",i);
		d[i]=o[i];
	}

}

void printBlock(void* p){
	
	int header = getHeaderIndex(p);
	int page = getPageIndex(p);
	int i;
	int counter = 0;
	int aux = 0;
	char* pointer;
	printf("header: %d   page: %d \n",header,page);
	
	if(header != -1 && page != -1){
		int bytes = abs(pages_struct.pages[page].header[header] * PADDING);
		for( i = 0; i < header; i++){
			aux += pages_struct.pages[page].header[header];
		}
		aux *= PADDING;
		pointer = (char*)(paginas[page]) + aux;
		printf("| ");
		for(i = 0; i < bytes; i++){
			if(counter < 15){
				printf("%c | ",pointer[i]);
				counter++;
				i++;
			}else{
				printf("\n| ");
				counter = 0;
			}
		}
		printf("\n");
	}
	else{
		printf("Invalid pointer\n");
	}
}	

/* Tiene que ingresar la dirección en formato de 6 dígitos, ej 20C2F4 */
int toInt(int size, char** p){

	int ret;
	int i;
	int dim = myStrlen(p[0]);
	toUpperString(p[0]);
	
	
	if(isValidPointer(p[0]) && dim == 6){
		if(dim == 6){
			for( i = 0, ret = 0; i < dim; i++){
				if( p[0][i] >= '0' && p[0][i] <= '9'){
					ret += (p[0][i] - '0') * myPow(16,dim - i);
				}else if(p[0][i] >= 'A' && p[0][i] <= 'F'){
					ret += (p[0][i] - 'A' + 10) * myPow(16,dim -1- i);
					
				}	
			}
		
		}else{
			ret = -1;
		}
	}else{
		printf("Null pointer exception\n");
	}
	
	return ret;
}

int myStrlen(char* s){
	
	int i = 0;
	while(s[i] != '\0'){
		i++;
	}	
	
	return i;
}

int myPow(int base, int exp){
	
	int ret = base;
	int i;
	
	if(exp == 0){
		ret = 1;
	}else{
		if( exp == 1){
			ret = base;
		}else{
			for( i = 1; i < exp; i++){
				ret *= base;
			}
		}
	}
	return ret;
}

void toUpperString(char* s){
	
	int i;
	int dim = myStrlen(s);
	for( i = 0; i < dim; i++){
		if(s[i] >= 'a' && s[i] <= 'z'){
			s[i] = s[i] - 'a' + 'A';
		}
	}
	
}

int isValidPointer(char* s){
	int valid = 1;
	int dim = myStrlen(s);
	int i;
	for(i = 0; i < dim && valid; i++){
		if(!((s[i] >= 0 && s[i] <= 9) || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F')))
			valid = 0;
	}
	
	return valid;
}
