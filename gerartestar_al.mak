COMP=gcc
OPC=-W -O2 -c

testar_al:   testar_al.o analex.o
	     $(COMP) -o testar_al testar_al.o analex.o
testar_al.o: testar_al.c 
	     $(COMP) $(OPC) testar_al.c
analex.o:    analex.c analex.h
	     $(COMP) $(OPC) analex.c
