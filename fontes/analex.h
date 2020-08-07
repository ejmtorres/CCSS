/*----------------------------------*/
/* Autor: Elias Jose Moreira Torres */
/* <ejmt_ce@hotmail.com>            */
/* Este software esta disponivel    */
/* via licenca GPL                  */
/*----------------------------------*/
#include "ccss.h"

/*------------------------------*/
/* analex.h - analisador lexico */
/*------------------------------*/
/* constantes para ... */
#define TAM_BUFFER 2048 /* tamanho do buffer */
#define TAM_IDENT  30   /* tamanho maximo do identificador */
#define TAM_NUMERO 10   /* numero de digitos em numero */
#define TAM_CADEIA 128  /* tamanho maximo de uma cadeia */
#define TAM_LEXEMA 128  /* tamanho maximo de um item lexico */
#define TAM_LINHA  128  /* tamanho da linha do arquivo fonte .c */
#define FIM_LIN    10   /* caractere de fim de linha */
#define FIM_CAD    '\0' /* delimitador de final de cadeia */
/* categorias para ... */
#define FIM_ARQ 300     /* fim de arquivo */
#define IDENTIF 310     /* identificador */
#define NUMERO  320     /* numero */
#define CARACT  330     /* caracteres */
#define CADEIA  340     /* cadeia (de caracteres) */
#define ERROLEX 350     /* indica uma mal formacao de token */
/* categoria para simbolos de dois caracteres */
#define MAIORIG 400     /* maior ou igual (>=) */
#define MENORIG 401     /* menor ou igual (<=) */
#define DIFERE  403     /* diferente      (!=) */
#define IGUAL   404     /* igual          (==) */
/* categorias de palavras reseraaaavadas */
#define INT    500
#define CHAR   INT + 1
#define IF     CHAR + 1
#define ELSE   IF + 1
#define WHILE  ELSE  + 1
#define DO     WHILE + 1
#define RETURN DO + 1
#define STATIC RETURN + 1
#define EXTERN STATIC + 1

/*-----------------------------------*/
/* associar um arquivo com um buffer */
/*-----------------------------------*/
PUBLIC void IniciarAnalisadorLexico(char *NomeFonte);
/*-------------------------------------------*/
/* obter proximo token = (categoria, lexema) */
/*-------------------------------------------*/
PUBLIC int ObterToken(char *Lexema);
/*----------------------*/
/* obter linha corrente */
/*----------------------*/
PUBLIC int ObterLinha();
/*-----------------------------------*/
/* desassocia o arquivo com o buffer */
/*-----------------------------------*/
PUBLIC void TerminarAnalisadorLexico();
