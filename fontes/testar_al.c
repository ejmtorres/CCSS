	/*----------------------------------*/
/* Autor: Elias Jose Moreira Torres */
/* <ejmt_ce@yahoo.com.br>           */
/* Este software esta disponivel    */
/* via licenca GPL                  */
/*----------------------------------*/

/*----------------------------------*/
/* teste_al.cpp                     */
/*----------------------------------*/
#include <stdio.h>
#include <string.h>
#include "analex.h"

#define TAM_NOME_ARQ 80

char NomeFonte[TAM_NOME_ARQ];     /* nome do arquivo fonte */
char NomeObjeto[TAM_NOME_ARQ];    /* nome do arquivo objeto */
int Token;
char Lexema[200];
/*--------------------------------------------------------*/
/* obtem o nome do arquivo objeto atraves de acrescimo da */
/* extensao asm ou troca da extensao original por asm     */
/*--------------------------------------------------------*/
void ObterNomeObjeto(char *NomeArquivo)
{
  char *Ptr = NomeArquivo;
  int   TemPonto;  /* indica se tem ponto no nome do arquivo */

  TemPonto = 0;
  while (*Ptr) /* pesquisa todo o nome do arquivo */
    if (*Ptr++ == '.') /* se tiver ponto sai do laco */
    {
      TemPonto = 1;
      break;
    }
  if (! TemPonto) /* se nao tinha ponto*/
    *Ptr++ = '.'; /* acrescenta o ponto */
  *Ptr++ = 'a';   /* coloca a extensao */
  *Ptr++ = 's';
  *Ptr++ = 'm';
  *Ptr++ = '\0';
}
/*--------------------*/
/* programa principal */
/*--------------------*/
int main(int NumArg, char *Arg[])
{
  /* se foi fornecido o nome do arquivo, use-o */
  if (NumArg == 2) strcpy(NomeFonte, Arg[1]);
  /*ou peca um ao usuario */
  else
  {
    printf("Entre com o nome do arquivo ==> ");
    gets(NomeFonte);
  }
  strcpy(NomeObjeto, NomeFonte);
  ObterNomeObjeto(NomeObjeto);
  IniciarAnalisadorLexico(NomeFonte);
  while ((Token = ObterToken(Lexema)) != FIM_ARQ)
  {
    printf("Lexema => <%s>, Token = <%d>\n", Lexema, Token);
    getchar();
  }
  TerminarAnalisadorLexico();
}

