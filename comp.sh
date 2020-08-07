if ( ./ccss $1.c )
then if ( as --32 -o $1.o $1.s )
     then if ( ld -m elf_i386 -o $1 $1.o lib_es.o lib_cad.o )
          then echo "$1 gerado com sucesso!"
	  else echo "Erro na ligacao de $1.o!"
          fi
     else echo "Erro na montagem de $1.s!."	  
     fi
else echo "Erro na compilacao de $1.xod!"     
fi
