tudo:
	as --32 -o lib_es.o lib_es.s
	as --32 -o lib_cad.o lib_cad.s

finalizar :
	rm *.o
