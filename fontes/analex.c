/*----------------------------------*/
/* Autor: Elias Jose Moreira Torres */
/* <ejmt_ce@hotmail.com>            */
/* Este software esta disponivel    */
/* via licenca GPL                  */
/*----------------------------------*/

/*------------------------------*/
/* analex.c - analisador lexico */
/*------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "analex.h"

PRIVATE FILE *ArqFonte;   /* fluxo do arquivo fonte */
PRIVATE char *Buffer;     /* buffer para leitura do arquivo fonte */
PRIVATE int   Indice;     /* indice dentro do buffer */
PRIVATE int   Linha;      /* linha atual */
PRIVATE int   ItensLidos; /* numero de caracteres lidos de cada vez */
PRIVATE int   Caract;     /* cada caractere lido do arquivo fonte */
PRIVATE char *PalRes[]    /* lista de palavras reservadas */
                      = {"int",	"char",	"if", "else", "while", "do", "return", "static", "extern", 0};
PRIVATE int   TknRes[]    /* lista dos respectivos tokens reservados */
                      = { INT,	 CHAR,	 IF,   ELSE,   WHILE,	DO,   RETURN,	STATIC,	  EXTERN,  0};
/*---------------------------------------------------*/
/* ler no maximo TAM_BUFFER caracteres para o buffer */
/*---------------------------------------------------*/
PRIVATE int LerBuffer()
{
	return fread(Buffer, 1, TAM_BUFFER, ArqFonte);
}
/*------------------------------------*/
/* obter proximo caractere do arquivo */
/*------------------------------------*/
PRIVATE int ObterCaractere()
{
	if (ItensLidos == TAM_BUFFER) /* se faltam itens */
  	{
    		if (Indice == TAM_BUFFER) /* se fim do buffer */
    		{
      			ItensLidos = LerBuffer();
      			Indice     = 0;
    		}
  	}
  	else                          /* se nao faltam mais itens */
  	{
    		if (Indice == ItensLidos) /* se fim de arquivo */
      			return FIM_ARQ;
  	}
  	if (Buffer[Indice] == FIM_LIN) Linha++;
  	return Buffer[Indice++];
}
/*-----------------------------------*/
/* associar um arquivo com um buffer */
/*-----------------------------------*/
PUBLIC void IniciarAnalisadorLexico(char *NomeFonte)
{
	if ((ArqFonte = fopen(NomeFonte, "r")) == (FILE *)0)
  	{
    		printf("Erro de abertura do arquivo %s\n", NomeFonte);
    		exit(1);
  	}
  	Buffer = malloc(TAM_BUFFER);
  	if (! Buffer)
  	{
    		puts("Sem memoria para alocar buffer...");
    		exit(1);
  	}
  	ItensLidos = LerBuffer();
  	Indice     = 0;
  	Linha      = 1;
  	Caract     = ObterCaractere();
}
/*--------------------------------------------------*/
/* retornar a categoria se for palavra reservada ou */
/* 0 para indicar que o lexema eh um identificador  */
/*--------------------------------------------------*/
PRIVATE int PalavraReservada(char *Lexema)
{
	register int Indice;

  	Indice = 0;
  	while (PalRes[Indice])
  	{
    		if (! strcmp(Lexema, PalRes[Indice])) return TknRes[Indice];
    		Indice++;
  	}
  	return 0;
}
/*--------------------------------------------------------*/
/* retornar a categoria se for simbolo de dois caracteres */
/* ou 0 em caso contrario                                 */
/*--------------------------------------------------------*/
PRIVATE int SimboloDuplo(char *Lexema)
{
	register int   Indice;
  	auto     char *SmbDup[] = {"<=",    "==",    ">=",    "!=",   0};
  	auto     int   TknDup[] = {MENORIG, IGUAL,   MAIORIG, DIFERE, 0};

  	Indice = 0;
  	while (SmbDup[Indice])
  	{
    		if (! strcmp(Lexema, SmbDup[Indice])) return TknDup[Indice];
    		Indice++;
  	}
  	return 0;
}
/*-------------------------------------------*/
/* obter proximo token = (categoria, lexema) */
/*-------------------------------------------*/
PUBLIC int ObterToken(char *Lexema)
{
	int Estado; /* estado do automato finito usado para analise lexica */
  	int IndLex; /* indice do lexema */
  	int IndCad; /* indice da cadeia */
  	int Token;  /* token encontrado */

  	Estado    = 1;
  	IndLex    = 0;
  	IndCad    = 0;
  	Lexema[0] = '\0';

  	while (1)
  	{
    		switch(Estado)
    		{
      			case 1 :	if (Caract == FIM_ARQ) return FIM_ARQ;
               			 	if (isspace(Caract)) Caract = ObterCaractere();
               				else
               				if (Caract == '"')
               				{
                 				Caract = ObterCaractere();
                 				Estado = 5;
               				}			
               				else
               				if (Caract == '/')
               				{
                 				Caract = ObterCaractere();
                 				Estado = 6;
               				}
               				else
					if (Caract == '\'')
					{
						Lexema[IndLex++] = Caract;
						Caract           = ObterCaractere();
						Estado           = 9;
					}
					else
               				if (isalpha(Caract))
               				{
                 				Lexema[IndLex++] = Caract;
                 				Caract           = ObterCaractere();
                 				Estado           = 2;
               				}
               				else
               				if (isdigit(Caract))
               				{
                 				Lexema[IndLex++] = Caract;
                 				Caract           = ObterCaractere();
                 				Estado           = 4;
               				}
               				else
               				{
                 				Lexema[IndLex++] = Caract;
                 				Caract           = ObterCaractere();
                 				Estado           = 3;
               				}
               				break;
			case 2 : 	if (isalnum(Caract)||(Caract == '_'))
               				{
                 				Lexema[IndLex++] = Caract;
                 				Caract           = ObterCaractere();
               				}
               				else
               				{
                 				Lexema[IndLex] = '\0';
                 				Token          = PalavraReservada(Lexema);
                 				if (Token) return Token;
                 				else
                 				{
                   					Lexema[TAM_IDENT] = '\0';
                   					return IDENTIF;
                 				}
               					}
               				break;
      			case 3 : 	Lexema[IndLex++] = Caract;
               				Lexema[2]        = '\0';
               				Token            = SimboloDuplo(Lexema);
               				if (Token)
               				{
                 				Caract = ObterCaractere();
                 				return Token;
               				}
               				Lexema[1] = '\0';
               				return Lexema[0];
      			case 4 : 	if (isdigit(Caract))
               				{
                 				Lexema[IndLex++] = Caract;
                 				Caract           = ObterCaractere();
               				}
               				else
               				{
                 				Lexema[IndLex] = '\0';
                 				if (IndLex <= TAM_NUMERO) return NUMERO;
                 				else                      return ERROLEX;
               				}
               				break;
      			case 5 : 	if (Caract == '"')
               				{
                 				Caract         = ObterCaractere();
                 				Lexema[IndCad] = '\0';
                 				if (IndCad <= TAM_CADEIA) return CADEIA;
                 				else                      return ERROLEX;
               				}
               				else
               				if (Caract == FIM_ARQ) return ERROLEX;
               				else
               				{
                 				Lexema[IndCad++] = Caract;
                 				Caract           = ObterCaractere();
               				}
               				break;
      			case 6 : 	if (Caract == '*')
	       				{
		       				Caract = ObterCaractere();
		       				Estado = 7;
	       				}
               				else 
	       				{
						return '/';
	       				}
               				break;
      			case 7 :	if (Caract == FIM_ARQ) return ERROLEX;
					if (Caract == '*')
					{
						Estado = 8;
					}
					Caract = ObterCaractere();
	       				break;
			case 8 :	if (Caract == '/')
					{
						Caract = ObterCaractere();
						Estado = 1;
					}
					else
					{
						Estado = 7;
					}
					break;
			case 9 :	if (Caract == FIM_ARQ) return ERROLEX;
					else
					{
						Lexema[IndLex++] = Caract;
						Caract           = ObterCaractere();
						Estado           = 10;
					}
					break;
			case 10:	if (Caract == '\'')
					{
						Lexema[IndLex++] = Caract;
						Lexema[IndLex]   = '\0';
						Caract           = ObterCaractere();
						return CARACT;
					}
					else
					{
						return ERROLEX;
					}
					break;
    }
  }
}
/*----------------------*/
/* obter linha corrente */
/*----------------------*/
PUBLIC int ObterLinha()
{
  return Linha;
}
/*-----------------------------------*/
/* desassocia o arquivo com o buffer */
/*-----------------------------------*/
PUBLIC void TerminarAnalisadorLexico()
{
	free(Buffer);
	fclose(ArqFonte);
}
