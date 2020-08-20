#COMP=gcc
COMP=clang
#OPC=-W -O2 -c
OPC=-Wdeprecated -O2 -c

ccss: 	     ccss.o anasem.o anasin.o analex.o
	     $(COMP) -o ccss ccss.o anasem.o anasin.o analex.o
	     rm *.o
ccss.o:      ccss.c
	     $(COMP) $(OPC) ccss.c
anasem.o:    anasem.c anasem.h
	     $(COMP) $(OPC) anasem.c
anasin.o:    anasin.c anasin.h
	     $(COMP) $(OPC) anasin.c
analex.o:    analex.c analex.h
	     $(COMP) $(OPC) analex.c
