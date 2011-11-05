#include <stdlib.h>
#include "heap.h"


int main(void){
	
	
	
	return 0;

}

/* Contructor de heap */
memStruct* newMemStruct(int memcap, byte base){

	memStruct* ret = NULL;
	
	if(base != NULL){
		ret = malloc(sizeof(memStruct));
		ret -> status = FREE;
		ret -> memCap = memcap;
		ret -> memDisp = memcap;
		ret -> left_child = NULL;
		ret -> right_child = NULL;
		ret -> base_m = base;
	}
	return ret;
	
}

byte myMalloc(memStruct *mem_struct, int cap){
	
	byte ret = NULL;
	
	if(mem_struct != NULL){
	if( mem_struct -> status == FULL || cap > mem_struct->memDisp ){
		ret = NULL;
	}else{
		if( mem_struct -> status == FREE){
			/* Creacion del hijo izquierdo */
			mem_struct -> left_child = newMemStruct(cap, mem_struct -> base_m);
			(mem_struct -> left_child) -> status = FULL;
			(mem_struct -> left_child) -> memDisp = 0;
			
			/* Creacion del hijo derecho */
			mem_struct -> right_child = newMemStruct((mem_struct -> memCap)-cap, (mem_struct -> base_m) + cap);
			(mem_struct -> right_child) -> status = FREE;
			
			/* Modificacion del heap */
			mem_struct -> status = USED;
			mem_struct -> memDisp = (mem_struct -> memCap)-cap;
		
		}else if(mem_struct -> status == USED){
			if((mem_struct -> left_child) -> status == FULL){
					ret = myMalloc(mem_struct -> right_child, cap);
			}else if((mem_struct -> right_child) -> status == FULL){
					ret = myMalloc(mem_struct -> left_child, cap);
			}else{
					if((mem_struct -> left_child) == FREE){
						if((ret = myMalloc(mem_struct -> left_child,cap)) == NULL){	
							ret = myMalloc(mem_struct -> right_child,cap);
						}
					}else{
						if((ret = myMalloc(mem_struct -> right_child,cap)) == NULL){	
							ret = myMalloc(mem_struct -> left_child,cap);
						}	
					}
				}		
			}
		}
	}
	return ret;
}

byte myCalloc(memStruct* mem_struct, int cap){
	
	byte pmem;
	byte aux;
	int i;
	pmem = myMalloc(mem_struct, cap);
	aux = pmem;
	
	if(pmem != NULL){
		for (i = 0; i < cap; i++){
			aux[i] = 0;
		}
	}
	return pmem;
}



/* Cambia una hoja de FULL a FREE */
void myFree(byte p, memStruct* mem_struct){
	
	if(mem_struct != NULL){
		if(mem_struct -> base_m == p && mem_struct -> status == FULL){
			mem_struct -> status = FREE;
			mem_struct -> memDisp =	mem_struct -> memCap;		
		}else{
			if(mem_struct -> status == USED){
				if(((mem_struct -> left_child) -> base_m) <= p && p < ((mem_struct -> left_child) -> base_m) + ((mem_struct -> left_child) -> memCap)){
					myFree(p,mem_struct -> left_child);
					
				}else{
					myFree(p,mem_struct -> right_child);		
				}	
			}
		}
	}	
	return;
}

void refactor(byte p, memStruct* mem_struct){
	
	if(mem_struct != NULL && mem_struct -> status == USED){
	
		if(((mem_struct -> left_child) -> status == FREE) && (mem_struct -> right_child) -> status == FREE){
				myFree(mem_struct -> left_child);
				myFree(mem_struct -> right_child);
				mem_struct -> left_child = NULL;
				mem_struct -> right_child = NULL;
				mem_struct -> status = FREE;
				mem_struct -> memDisp = mem_struct -> memCap;
		}
		else if()
	}
		
	return;
}
void free (void* pmem)
{
	

}



memStruct* getLastLeft(memStruct* mem_struct){
	
	memStruct* ret = NULL;
	
	if(mem_struct != NULL){	
		ret = mem_struct -> left_child;
	
		if(ret != NULL){
			while(ret -> left_child != NULL){
				ret = ret ->left_child;		
			}
		}
		else{
			ret = mem_struct;
		}
	}	
	return ret;	
}

memStruct* getLastRight(memStruct* mem_struct){
	
	memStruct* ret = NULL;
	
	if(mem_struct != NULL){	
		ret = mem_struct -> right_child;
	
		if(ret != NULL){
			while(ret -> right_child != NULL){
				ret = ret ->right_child;		
			}
		}
		else{
			ret = mem_struct;
		}
	}	
	return ret;	
}



