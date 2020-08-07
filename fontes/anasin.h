/*----------------------------------*/
/* Autor: Elias Jose Moreira Torres */
/* <ejmt_ce@yahoo.com.br>           */
/* Este software esta disponivel    */
/* via licenca GPL                  */
/*----------------------------------*/

/*---------------------------------*/
/* anasin.h - analisador sintatico */
/*---------------------------------*/
#include "ccss.h"
#define TAM_MENSAGEM 30

/*-------------------------------------------------*/
/* associar um analisador sintatico com um arquivo */
/* fonte e um arquivo objeto                       */
/*-------------------------------------------------*/
PUBLIC void IniciarAnalisadorSintatico(char *NomeFonte, char *NomeMonta);
/*------------------------------------*/
/* desassociar o analisador sintatico */
/*------------------------------------*/
PUBLIC void TerminarAnalisadorSintatico();
