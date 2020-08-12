/*----------------------------------*/
/* Autor: Elias Jose Moreira Torres */
/* <ejmt_ce@hotmail.com>            */
/* Este software esta disponivel    */
/* via licenca GPL                  */
/*----------------------------------*/

/*---------------------------------*/
/* anasin.c - analisador sintatico */
/*---------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analex.h"
#include "anasin.h"
#include "anasem.h"

PRIVATE int  Token;
PRIVATE char Lexema[TAM_LEXEMA+1];
PRIVATE void Expressao();
PRIVATE void Comandos();

/*----------------------------------*/
/* mostrar erro sintatico e abortar */
/*----------------------------------*/
PRIVATE void Abortar(int N)
{
	char Mensagem[TAM_MENSAGEM];

  	switch(N)
  	{
		case  0 : strcpy(Mensagem, "fim de arquivo"); 		break;
    		case  1 : strcpy(Mensagem, "identificador");        	break;
    		case  2 : strcpy(Mensagem, "tipo");          		break;
    		case  3 : strcpy(Mensagem, "';'");         		break;
    		case  4 : strcpy(Mensagem, "')'");         		break;
    		case  5 : strcpy(Mensagem, "'{'");         		break;
    		case  6 : strcpy(Mensagem, "'}'");         		break;
		case  7 : strcpy(Mensagem, "'=' ou '(' ou '['");	break;
		case  8 : strcpy(Mensagem, "expressao");		break;
		case  9 : strcpy(Mensagem, "'=' ou '['");		break;
		case 10 : strcpy(Mensagem, "']'"); 			break;
		case 11 : strcpy(Mensagem, "'='"); 			break;
		case 12 : strcpy(Mensagem, "numero"); 			break;
  	}
  printf("Linha %d ==> %s esperado(a)!\n", ObterLinha(), Mensagem);
  exit(N);
}
/*-------------------------------------------*/
/* Relacao: '<', "<=", '>', ">=", "==", "!=" */
/*-------------------------------------------*/
PRIVATE void Relacao()
{
	Token=ObterToken(Lexema);
}
/*-------------------------------------------------*/
/* ListaDeExpressoes = Expressao { ',' Expressao } */
/*-------------------------------------------------*/
PRIVATE void ListaDeExpressoes()
{
	Expressao();
  	while (Token == ',')
  	{
    		Token=ObterToken(Lexema);
    		Expressao();
  	}
}
/*----------------------------------------------------------*/
/* ListaDeIndices = '[' Expressao ']' { '[' Expressao ']' } */
/*----------------------------------------------------------*/
PRIVATE void ListaDeIndices()
{
	Expressao();
	if (Token==']')
	{
		Token=ObterToken(Lexema);
		while (Token=='[')
		{
			Token=ObterToken(Lexema);
			Expressao();
			if (Token==']')
			{
				Token=ObterToken(Lexema);
			}
			else
			{
				Abortar(10);
			}
		}
	}
	else
	{
		Abortar(10);
	}
}
/*--------------------------------------------------------------------------------------------*/
/* Fator = NUMERO | [ ( '*' | '&' ) ] IDENTIFICADOR [ ListaDeExpressoes ] | '(' Expressao ')' */
/*--------------------------------------------------------------------------------------------*/
PRIVATE void Fator()
{
	switch(Token)
	{
		case NUMERO	:	Token=ObterToken(Lexema);
					break;
		case '*'	:
		case '&'	:	Token=ObterToken(Lexema);	
					if (Token==IDENTIF)
					{
						Token=ObterToken(Lexema);
						if (Token=='[')
						{
							Token=ObterToken(Lexema);
							ListaDeIndices();
						}
					}
					else
					{
						Abortar(1);
					}
					break;
		case IDENTIF	: 	Token=ObterToken(Lexema);
					if (Token=='[')
					{
						Token=ObterToken(Lexema);
						ListaDeIndices();
					}
					break;
		case '('	:	Token=ObterToken(Lexema);
					Expressao();
					if (Token==')')
					{
						Token=ObterToken(Lexema);
					}
					else
					{
						Abortar(4);
					}
					break;
	}
}
/*---------------------------------------*/
/* Termo = Fator { ( '*' | '/' ) Fator } */
/*---------------------------------------*/
PRIVATE void Termo()
{
	Fator();
  	while ((Token == '*') || (Token == '/'))
  	{
    		Token=ObterToken(Lexema);
    		Fator();
  	}
}
/*----------------------------------------------------------*/
/* ExpressaoSimples = [ '-' ] Termo { ( '+' | '-' ) Termo } */
/*----------------------------------------------------------*/
PRIVATE void ExpressaoSimples()
{
	if (Token == '-')
  	{
    		Token=ObterToken(Lexema);
  	}
  	Termo();
  	while ((Token == '+') || (Token == '-'))
  	{
    		Token=ObterToken(Lexema);
    		Termo();
  	}
}
/*-----------------------------------------------------------*/
/* Expressao = ExpressaoSimples [ Relacao ExpressaoSimples ] */
/*-----------------------------------------------------------*/
PRIVATE void Expressao()
{
	ExpressaoSimples();
	if ((Token=='<')     || (Token=='>')     ||
	    (Token==MENORIG) || (Token==MAIORIG) ||
	    (Token==IGUAL)   || (Token==DIFERE))
	{
		Relacao();
		ExpressaoSimples();
	}
}
/*-----------------------------------*/
/* Tipo = INT [ '*' ] | CHAR [ '*' ] */
/*-----------------------------------*/
PRIVATE void Tipo(int *T)
{
	switch(Token)
  	{
		case INT	:	*T=INT;
					Token=ObterToken(Lexema); 
					break;
    		case CHAR 	: 	*T=CHAR;
					Token=ObterToken(Lexema);
					break;
    		default   	: 	Abortar(2);
  	}
}
/*----------------------------------------------------------------------*/
/* ComandoDeAtribuicao = IDENTIFICADOR [ ListaDeIndices ] '=' Expressao */
/*----------------------------------------------------------------------*/
PRIVATE void ComandoDeAtribuicao()
{
	if (Token == '[')
    	{
      		Token=ObterToken(Lexema);
      		ListaDeIndices();
      		if (Token == ']') 
		{
			Token=ObterToken(Lexema);
    			if (Token == '=') 
    			{
				Token=ObterToken(Lexema);
				Expressao();
    			}
    			else 
    			{
				Abortar(11);
    			}
		}
      		else Abortar(10);
    	}
    	else
    	if (Token == '=') 
    	{
		Token=ObterToken(Lexema);
		Expressao();
    	}
    	else 
    	{
		Abortar(9);
    	}
}
/*------------------------------------------------------------*/
/* ComandoDeChamada = IDENTIFICADOR '(' ListaDeExpressoes ')' */
/*------------------------------------------------------------*/
PRIVATE void ComandoDeChamada()
{
}
/*----------------------------------*/
/* ComandoRETURN = RETURN Expressao */
/*----------------------------------*/
PRIVATE void ComandoRETURN()
{
}
/*----------------------------------------------*/
/* ComandoDO = DO Corpo WHILE '(' Expressao ')' */
/*----------------------------------------------*/
PRIVATE void ComandoDO()
{
}
/*----------------------------------------------*/
/* ComandoWHILE = WHILE '(' Expressao ')' Corpo */
/*----------------------------------------------*/
PRIVATE void ComandoWHILE()
{
}
/*-------------------------------------------------------*/
/* ComandoIF = IF '(' Expressao ')' Corpo [ ELSE Corpo ] */ 
/*-------------------------------------------------------*/
PRIVATE void ComandoIF()
{
}
/*--------------------------------------------------*/
/* Comando vai direcionar para o comando apropriado */
/*--------------------------------------------------*/
PRIVATE void Comando()
{
	switch(Token)
  	{
		case IF		: 	ComandoIF(); 
					break;
		case WHILE	: 	ComandoWHILE();	
					break;
		case DO		: 	ComandoDO();
					break;
		case RETURN	: 	ComandoRETURN();
					break;
		case IDENTIF	:	Token=ObterToken(Lexema);
			  		switch(Token)
			  		{
						case '='	:
						case '[' 	:	ComandoDeAtribuicao();
									break;
						case '(' 	: 	ComandoDeChamada();
									break;
						default  	: 	Abortar(7);
			  		}
					break;
  	}
}
/*----------------------------*/
/* Comandos = { Comando ';' } */
/*----------------------------*/
PRIVATE void Comandos()
{
	while ((Token==IF) || (Token==WHILE) || (Token==DO) || (Token==RETURN) || (Token==IDENTIF))
	{
		Comando();
		if (Token==';')
		{
			Token=ObterToken(Lexema);
		}
		else
		{
			Abortar(3);
		}
	}
}
/*----------------------------------------*/
/* Corpo = Comando ';' | '{' Comandos '}' */
/*----------------------------------------*/
PRIVATE void Corpo()
{
	if (Token=='{')
	{
		Comandos();
		if (Token=='}')
		{
			Token=ObterToken(Lexema);
		}
		else
		{
			Abortar(6);
		}
	}
	else
	{
		Comando();
		if (Token==';')
		{
			Token=ObterToken(Lexema);
		}
		else
		{
			Abortar(3);
		}
	}
}
/*------------------------------------------------------*/
/* ListaDeDimensoes = '[' NUMERO ']' { '[' NUMERO ']' } */
/*------------------------------------------------------*/
PRIVATE void ListaDeDimensoes()
{
	Token=ObterToken(Lexema);
	if (Token==NUMERO)
	{
		Token=ObterToken(Lexema);
		if (Token==']')
		{	
			Token=ObterToken(Lexema);
			while (Token=='[')
			{
				Token=ObterToken(Lexema);
				if (Token==NUMERO)
				{
					Token=ObterToken(Lexema);
					if (Token==']')
					{
						Token=ObterToken(Lexema);
					}
					else
					{
						Abortar(10);
					}
				}
				else
				{
					Abortar(12);
				}
			}
		}
		else
		{
			Abortar(10);
		}
	}
	else
	{
		Abortar(12);
	}
}
/*------------------------------------------------------------*/
/* VariavelLocal = [ '*' ] IDENTIFICADOR [ ListaDeDimensoes ] */
/*------------------------------------------------------------*/
PRIVATE void VariavelLocal()
{
	if (Token=='*')
	{
		Token=ObterToken(Lexema);
	}
	if (Token==IDENTIF)
  	{
    		Token=ObterToken(Lexema);
		if (Token=='[')
		{
			ListaDeDimensoes();
		}
		else
		{
			// nao eh vetor
		}
  	}
  	else
  	{
    		Abortar(1);
  	}
}
/*-------------------------------------------------------*/
/* DeclaracaoLocal = VariavelLocal { ',' VariavelLocal } */
/*-------------------------------------------------------*/
PRIVATE void DeclaracaoLocal(int T)
{
	VariavelLocal(T);
	while (Token==',')
	{
		Token=ObterToken(Lexema);
		VariavelLocal(T);
	}
	if (Token==';')
	{
		Token=ObterToken(Lexema);
	}
	else
	{
		Abortar(3);
	}
}
/*----------------------------------------------*/
/* DeclaracoesLocais = { Tipo DeclaracaoLocal } */
/*----------------------------------------------*/
PRIVATE void DeclaracoesLocais()
{
	int T;

	while ((Token==INT) || (Token==CHAR))
	{
		Tipo(&T);
		DeclaracaoLocal(T);
	}
}
/*----------------------------------------------------*/
/* Bloco = '{' [ DeclaracoesLocais ] [ Comandos ] '}' */
/*----------------------------------------------------*/
PRIVATE void Bloco()
{
  	if (Token=='{')
  	{
    		Token=ObterToken(Lexema);
    		DeclaracoesLocais();
    		Comandos();
    		if (Token=='}')
    		{
      			Token=ObterToken(Lexema);
    		}
    		else
    		{
      			Abortar(6);
    		}
  	}
  	else
  	{
    		Abortar(5);
  	} 
}
/*-----------------------------------*/
/* Parametro = [ '*' ] IDENTIFICADOR */
/*-----------------------------------*/
PRIVATE void Parametro()
{
	if (Token=='*')
	{
		Token=ObterToken(Lexema);
	}
	if (Token==IDENTIF)
	{
		Token=ObterToken(Lexema);
	}
	else
	{
		Abortar(1);
	}
}
/*----------------------------------------*/
/* DeclaracaoDeParametro = Tipo Parametro */
/*----------------------------------------*/
PRIVATE void DeclaracaoDeParametro()
{
	int T;

	Tipo(&T);
	Parametro();
}
/*-------------------------------------------------------------------------------*/
/* DeclaracoesDeParametros = DeclaracaoDeParametro { ',' DeclaracaoDeParametro } */
/*-------------------------------------------------------------------------------*/
PRIVATE void DeclaracoesDeParametros()
{
	if (Token==')')
	{
		/* sem parametros */
	}
	else
	{
		DeclaracaoDeParametro();
		while (Token==',')
		{
			Token=ObterToken(Lexema);
			DeclaracaoDeParametro();
		}
	}
}
/*-------------------------------------------------------------*/
/* VariavelGlobal = [ '*' ] Identificador [ ListaDeDimensões ] */
/*-------------------------------------------------------------*/
<<<<<<< HEAD
PRIVATE void VariavelGlobal(char *Id)
=======
PRIVATE void VariavelGlobal(char *Identificador)
>>>>>>> dcc950ab22e2879c3a4b7c27be50d6816311fc9c
{
	if (Token=='*')
	{
		Token=ObterToken(Lexema);
	}
	if (Token==IDENTIF)
  	{
		strcpy(Id, Lexema);
    		Token=ObterToken(Lexema);
		if (Token=='[')
		{
			ListaDeDimensoes();
		}
<<<<<<< HEAD
=======
		else
		{
		}
>>>>>>> dcc950ab22e2879c3a4b7c27be50d6816311fc9c
  	}
  	else
  	{
    		Abortar(1);
  	}
}
/*-------------------------------------------------------------------------------------------------------------------*/
/* DeclaracaoGlobal = Tipo VariavelGlobal ( { ',' VariavelGlobal } ';' | '(' [ DeclaracoesDeParametros ] ')' Bloco ) */
/*-------------------------------------------------------------------------------------------------------------------*/
PRIVATE void DeclaracaoGlobal()
{
<<<<<<< HEAD
	int  T; 
	char Id[TAM_CADEIA + 1];

	Tipo(&T);
  	VariavelGlobal(Id);
	switch(Token)
	{
		case ';': 	IniciarSegmentoDeDados();
				DefinirVariavelGlobal(Id, T);
				Token=ObterToken(Lexema); 
				break;
		case ',': 	DefinirVariavelGlobal(Id, T);
				while (Token==',') 
    			   	{
					Token=ObterToken(Lexema);
      					VariavelGlobal(Id);
					DefinirVariavelGlobal(Id, T);
=======
	int  T;
        char Identificador[TAM_CADEIA + 1];	

	Tipo(&T);
  	VariavelGlobal(Identificador);
	switch(Token)
	{
		case ';': 	IniciarSegmentoDeDados();
				DefinirVariavelGlobal(Identificador, T);
				Token=ObterToken(Lexema); 
				break;
		case ',': 	IniciarSegmentoDeDados();
				DefinirVariavelGlobal(Identificador, T);
				while (Token==',') 
    			   	{
      					Token=ObterToken(Lexema);
      					VariavelGlobal(Identificador);
					DefinirVariavelGlobal(Identificador, T);
>>>>>>> dcc950ab22e2879c3a4b7c27be50d6816311fc9c
    				}
    				if (Token==';')
    				{
      					Token=ObterToken(Lexema);
    				}
				else
				{
		  			Abortar(3);
				}
				break;
		case '(': 	IniciarSegmentoDeCodigo();
				IniciarSubRotina(Identificador);
				Token=ObterToken(Lexema);
    				DeclaracoesDeParametros();
    				if (Token==')')
    				{
      					Token=ObterToken(Lexema);
      					Bloco();
					TerminarSubRotina(Identificador);
    				}
				else
				{
					Abortar(4);
				}
				break;
		default :	Abortar(3);
	}
}
/*------------------------------------------------------------*/
/* DeclaracoesGlobais = DeclaracaoGlobal { DeclaracaoGlobal } */
/*------------------------------------------------------------*/
PRIVATE void DeclaracoesGlobais()
{
  	DeclaracaoGlobal();
  	while ((Token==INT) || (Token==CHAR))
  	{
    		DeclaracaoGlobal();
  	} 

}
/*-------------------------------------------*/
/* Modulo = [ Inclusoes ] DeclaracoesGlobais */
/*-------------------------------------------*/
PRIVATE void Modulo()
{
  	/* Inclusoes(); */
  	DeclaracoesGlobais();
}
/*-------------------------------------------------*/
/* Associar um analisador sintatico com um arquivo */
/* fonte e com um arquivo objeto (em assembly)     */
/*-------------------------------------------------*/
PUBLIC void IniciarAnalisadorSintatico(char *NomeFonte, char *NomeMonta)
{
  	IniciarAnalisadorLexico(NomeFonte);
  	IniciarAnalisadorSemantico(NomeMonta);

  	Token=ObterToken(Lexema);
  	Modulo();
	if (Token==FIM_ARQ)
	{
	}	
	else Abortar(0);
}
/*------------------------------------*/
/* Desassociar o analisador sintatico */
/*------------------------------------*/
PUBLIC void TerminarAnalisadorSintatico()
{
	TerminarAnalisadorSemantico();
  	TerminarAnalisadorLexico();
}
