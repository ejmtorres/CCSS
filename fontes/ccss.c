/*----------------------------------*/
/* Autor: Elias Jose Moreira Torres */
/* <ejmt_ce@hotmail.com>            */
/* Este software esta disponivel    */
/* via licenca GPL                  */
/*----------------------------------*/

/*----------------------------*/
/* ccs.c - programa principal */
/*----------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "anasin.h"
#include "ccss.h"

#define TAM_NOME_ARQ 80

PRIVATE char NomeFonte[TAM_NOME_ARQ];   /* nome do arquivo fonte */
PRIVATE char NomeMonta[TAM_NOME_ARQ];   /* nome do arquivo .asm */

/*----------------------------------*/
/* mostrar sintaxe de uso e abortar */
/*----------------------------------*/
void Abortar()
{
	puts("Sintaxe de uso:\n");
	puts("  ./ccss 'prog.c'");
	puts("  onde 'prog.c' eh o programa em C a ser compilado.\n");
	exit(1);
}

/*------------------------------------------------*/
/* obter nome do arquivo com a extensao fornecida */
/*------------------------------------------------*/
PRIVATE void ObterNome(char *NomeArq, char *Extensao)
{
  char *PtrArq = NomeArq;
  char *PtrExt = Extensao;
  int   TemPonto;  /* indica se tem ponto no nome do arquivo */

  TemPonto = 0;
  while (*PtrArq) /* pesquisa todo o nome do arquivo */
    if (*PtrArq++ == '.') /* se tiver ponto sai do laco */
    {
      TemPonto = 1;
      break;
    }
  if (! TemPonto) /* se nao tinha ponto*/
    *PtrArq++ = '.'; /* acrescenta o ponto */
  *PtrArq++ = *PtrExt++;
  *PtrArq++ = *PtrExt++;
  *PtrArq   = *PtrExt;
}

/*--------------------*/
/* programa principal */
/*--------------------*/
PUBLIC int main(int NumArg, char *Arg[])
{
  puts("*************************************");
  puts("* CCSS - Compilador C Super Simples *");
  puts("*************************************");
  puts("* Implementado em C para SO Linux.  *");
  puts("* Código de montagem de 32 bits.    *");
  puts("* Roda em 32/64 bits.               *");
  puts("* Autor: Elias Jose Moreira Torres  *");
  puts("* <ejmt_ce@hotmail.com>             *");
  puts("*************************************");
  puts("\n");
  switch(NumArg)
  {
    case  1 : Abortar();
              break;
    case  2 : strcpy(NomeFonte, Arg[1]);
              break;
  }
  strcpy(NomeMonta, NomeFonte);
  ObterNome(NomeMonta, "s");
  printf("Gerando %s ...\n", NomeMonta);
  IniciarAnalisadorSintatico(NomeFonte, NomeMonta);
  TerminarAnalisadorSintatico();
  return 0;
}
