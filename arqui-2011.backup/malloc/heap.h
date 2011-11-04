#define byte unsigned char*
#define FREE 0
#define USED 1
#define FULL 2
#define MAXSIZE 4000

typedef struct memStruct{
	
	int status;
	int memCap;
	int memDisp;
	byte base_m;
	struct memStruct *left_child;
	struct memStruct *right_child;
	
}memStruct;

typedef struct memNode{

	memStruct *asoc_struct;
	struct memNode *next_node;
}memNode;

memStruct* newMemStruct(int memcap, byte base);
byte myMalloc(memStruct *mem_struct, int cap);
byte myCalloc(memStruct *mem_struct, int cap);
void myFree(byte p, memStruct* mem_struct);
void refactor(memStruct* mem_struct);
memStruct* getLastLeft(memStruct* mem_struct);
memStruct* getLastRight(memStruct* mem_struct);
