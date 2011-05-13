.SILENT:


TARGET=simula
OBJS=libc.o simula.o nInLineFront.o nInLineBack.o
CC=gcc
COPTS=-g -c
LD=$(CC)
LDOPTS=-o

$(TARGET):	$(OBJS)
	echo Linkeditando $(OBJS) para obtener $(TARGET)... 
	$(LD) $(LDOPTS) $(TARGET) $(OBJS)
	
libc.o:	libc.c
	$(LD) $(COPTS) libc.c

simula.o:	simula.c
	$(LD) $(COPTS) simula.c

nInLineFront.o: nInLineFront.c
		$(LD) $(COPTS) nInLineFront.c
		
nInLineBAck.o: nInLineBack.c
		$(LD) $(COPTS) nInLineBack.c

clear:
	echo Limpiando directorio... 
	echo Eliminando archivos objeto y $(TARGET)
	-rm *.o
	-rm $(TARGET)
	echo Finalizado limpieza
