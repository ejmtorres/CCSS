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
PRIVATE void Relacao(char *Op)
{
	Token=ObterToken(Lexema);
}
/*-------------------------------------------------*/
/* ListaDeExpressoes = Expressao { ',' Expressao } */
/*-------------------------------------------------*/
PRIVATE void ListaDeExpressoes(int *NA, int *NB)
{
    int T; // tipo da expressao
    
    Expressao(&T);
    EmpilharExpressao();
    *NA = *NA + 1;
    switch(T)
    {
        case INT:  *NB = *NB + NB_INTEIRO;  break;
    //    case PONTEIRO: *NB = *NB + NB_PONTEIRO; break;
    //    case CADEIA:   *NB = *NB + NB_PONTEIRO; break;
    }

  	while (Token == ',')
  	{
    		Token=ObterToken(Lexema);
    		Expressao(&T);
        EmpilharExpressao();
        *NA = *NA + 1;
        switch(T)
        {
            case INT:  *NB = *NB + NB_INTEIRO;  break;
            //case PONTEIRO: *NB = *NB + NB_PONTEIRO; break;
            //case CADEIA:   *NB = *NB + NB_PONTEIRO; break;
        }

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
PRIVATE void Fator(int *R, int *T)
{
    auto     int TR;      /* topo dos registradores */
    register int Cat;     /* categoria */
    auto     int NA;      /* numero de argumentos ou indices */
    auto     int NB;      /* numero de bytes empilhados */
    auto     int TA;      /* topo auxilar dos registradores */
    auto     int P;       /* entrada para tipo estruturado */
    char Alvo[TAM_NOME];  /* nome da funcao ou vetor */

  switch(Token)
  {
    case IDENTIF : //Cat = ObterCategoria(Lexema);
                   /* funcao declarada ou externa */
                   //if ((Cat == CFUNC)||(Cat == NADA))
                   //{
                   //  strcpy(Alvo, Lexema);
                   //  Token = ObterToken(Lexema);
                   //  IniciarFuncao(&NA, &NB, &TA);
                   //  if (Token == '(')
                   //  {
                   //     Token = ObterToken(Lexema);
                   //     if (Token == ')') Token = ObterToken(Lexema);
                   //     else
                   //     {
                   //       ListaDeExpressoes(&NA, &NB);
                   //       if (Token == ')') Token = ObterToken(Lexema);
                   //       else Abortar(2);
                   //     }
                   //  }
                   //  TerminarFuncao(R, T, NA, NB, TA, Alvo);
                   //}
                   //else
                   /* variavel vetor */
                   //if (Cat == CVET)
                   //{
                   //  strcpy(Alvo, Lexema);
                   //  Token = ObterToken(Lexema);
                   //  IniciarFatorVetor(&NA, &TA, R, T, &P, Alvo);
                   //  if (Token == '[')
                   //  {
                   //    Token = ObterToken(Lexema);
                   //    ListaDeIndices(&NA, P);
                   //    if (Token == ']') Token = ObterToken(Lexema);
                   //    else Abortar(21);
                   //  }
                   //  else  Abortar(20);
                   //  TerminarFatorVetor(NA, TA, *R, Alvo);
                   //}
                   /* variavel simples */
                   //else
                   {
                     GerarFator(R, T, Token, Lexema);
                     Token = ObterToken(Lexema);
                   }
                   break;
    case NUMERO  : GerarFator(R, T, Token, Lexema);
                   Token = ObterToken(Lexema);
                   break;
    //case VALOR   : Token = ObterToken(Lexema);
    //               if (Token == '(') Token = ObterToken(Lexema);
    //               else Abortar(18);
    //               if (Token == IDENTIF)
    //               {
    //                 GerarFatorValor(R, T, Lexema);
    //                 Token = ObterToken(Lexema);
    //               }
    //               else Abortar(1);
    //               if (Token == ')') Token = ObterToken(Lexema);
    //               else Abortar(2);
    //               break;
    case '('     : SalvarRegistradores(&TR);
                   Token = ObterToken(Lexema);
                   Expressao(T);
                   if (Token == ')') Token = ObterToken(Lexema);
                   else Abortar(2);
                   RecuperarRegistradores(R, TR);
                   break;
    default      : Abortar(10);
  }
	
/*    switch(Token)
	{
        case NUMERO  :  GerarFator(R, T, Token, Lexema);
		                Token=ObterToken(Lexema);
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
*/
}
/*---------------------------------------*/
/* Termo = Fator { ( '*' | '/' ) Fator } */
/*---------------------------------------*/
PRIVATE void Termo(int *R, int *T)
{
/*
	Fator();
  	while ((Token == '*') || (Token == '/'))
  	{
    		Token=ObterToken(Lexema);
    		Fator();
  	}
*/
  int R1, R2; /* registradores para os fatores */
  int T1, T2; /* tipos dos fatores */
  int Operador;

  Fator(&R1, &T1);
  while ((Token == '*')||(Token == '/'))
  {
    Operador = Token;
    Token    = ObterToken(Lexema);
    Fator(&R2, &T2);
    Operar(Operador, R1, R2, T1, T2);
  }
  *R = R1;
  *T = T1;

}
/*----------------------------------------------------------*/
/* ExpressaoSimples = [ '-' ] Termo { ( '+' | '-' ) Termo } */
/*----------------------------------------------------------*/
PRIVATE void ExpressaoSimples(int *R, int *T)
{
/*
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
*/
  int R1, R2; /* registradores de cada termo */
  int T1, T2; /* tipos de cada termo */
  int Operador;
  int Menos; /* setado se tem menos unario */

  Menos = 0;
  if (Token == '-')
  {
    Menos = 1;
    Token = ObterToken(Lexema);
  }
  Termo(&R1, &T1);
  GerarMenos(Menos, R1);
  while ((Token == '+')||(Token == '-'))
  {
    Operador = Token;
    Token    = ObterToken(Lexema);
    Termo(&R2, &T2);
    Operar(Operador, R1, R2, T1, T2);
  }
  *R = R1;
  *T = T1;

}
/*-----------------------------------------------------------*/
/* Expressao = ExpressaoSimples [ Relacao ExpressaoSimples ] */
/*-----------------------------------------------------------*/
PRIVATE void Expressao(int *T)
{
/*
	ExpressaoSimples();
	if ((Token=='<')     || (Token=='>')     ||
	    (Token==MENORIG) || (Token==MAIORIG) ||
	    (Token==IGUAL)   || (Token==DIFERE))
	{
		Relacao();
		ExpressaoSimples();
	}
*/
  int R1, R2; /* registradores das expressoes simples */
  int T1, T2; /* tipos das expressoes simples */
  char Op[3]; /* operador das expressoes simples */

  //if (Token == STRING)
  //{
  //  GerarCadeia(Lexema, T);
  //  Token = ObterToken(Lexema);
  //}
  //else
  //if (Token == ENDER)
  //{
  //  Token = ObterToken(Lexema);
  //  if (Token == '(') Token = ObterToken(Lexema);
  //  else Abortar(18);
  //  if (Token == IDENTIF)
  //  {
  //    GerarEndereco(Lexema, T);
  //    Token = ObterToken(Lexema);
  //  }
  //  else Abortar(1);
  //  if (Token == ')') Token = ObterToken(Lexema);
  //  else Abortar(2);
  //}
  //else
  {
    ExpressaoSimples(&R1, &T1);
    //if (Relacao(Lexema))
    //{
    //  strcpy(Op, Lexema);
    //  Token = ObterToken(Lexema);
    //  ExpressaoSimples(&R2, &T2);
    //  OperarRelacao(Op, R1, R2, T1, T2);
    //}
    *T = T1;
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
PRIVATE void ComandoDeAtribuicao(char *Alvo)
{
/*
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
*/
  auto     int T;       /* tipo base do alvo */
  auto     int P;       /* tipo estruturado do alvo */
  register int Cat;     /* categoria do alvo */
  auto     int NI;      /* numero de indices */

  Cat   = ObterCategoria(Alvo);
  //Token = ObterToken(Lexema);
  //if (Cat == CVET) /* variavel vetor */
  //{
  //  IniciarAtribuicaoVetor(&NI, &T, &P, Alvo);
  //  if (Token == '[')
  //  {
  //    Token = ObterToken(Lexema);
  //    ListaDeIndices(&NI, P);
  //    if (Token == ']') Token = ObterToken(Lexema);
  //    else Abortar(21);
  //  }
  //  else  Abortar(20);
  //  TerminarAtribuicaoVetor(NI, Alvo);
  //  if (Token == '=') Token = ObterToken(Lexema);
  //  else Abortar(9);
  //  Expressao(&T);
  //  GerarAtribuicaoVetor(Alvo, T);
  //}
  //else             /* variavel simples */
  {
    if (Token == '=') Token = ObterToken(Lexema);
    else Abortar(9);
    Expressao(&T);
    GerarAtribuicao(Alvo, T);
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
	char Id[TAM_LEXEMA + 1];

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
		case IDENTIF	:	strcpy(Id, Lexema);
					Token=ObterToken(Lexema);
			  		switch(Token)
			  		{
						case '='	:
						case '[' 	:	ComandoDeAtribuicao(Id);
									break;
						//case '(' 	: 	ComandoDeChamada(Id);
						//			break;
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
PRIVATE void DeclaracaoLocal()
{
	VariavelLocal();
	while (Token==',')
	{
		Token=ObterToken(Lexema);
		VariavelLocal();
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
		DeclaracaoLocal();
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
PRIVATE void Parametro(int Tipo, int NP)
{
	if (Token=='*')
	{
		Token=ObterToken(Lexema);
	}
	if (Token==IDENTIF)
	{
		DefinirParametro(Lexema, Tipo, NP);
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
PRIVATE void DeclaracaoDeParametro(int NP)
{
	int T;

	Tipo(&T);
	Parametro(T, NP);
}
/*-------------------------------------------------------------------------------*/
/* DeclaracoesDeParametros = DeclaracaoDeParametro { ',' DeclaracaoDeParametro } */
/*-------------------------------------------------------------------------------*/
PRIVATE void DeclaracoesDeParametros(int *NP)
{
	*NP = 0;
	if (Token==')')
	{
		/* sem parametros */
	}
	else
	{
		*NP = *NP + 1;
		DeclaracaoDeParametro(*NP);
		while (Token==',')
		{
			Token=ObterToken(Lexema);
			*NP = *NP + 1;
			DeclaracaoDeParametro(*NP);
		}
	}
}
/*-------------------------------------------------------------*/
/* VariavelGlobal = [ '*' ] Identificador [ ListaDeDimensões ] */
/*-------------------------------------------------------------*/
PRIVATE void VariavelGlobal(char *Id)
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
	char Id[TAM_LEXEMA + 1];
	int  T; 
	int  NP; // N. de parametros (se função)

	Tipo(&T);
  	VariavelGlobal(Id);
	switch(Token)
	{
		case ';': 	IniciarSegmentoDeDados();
				DefinirVariavelGlobal(Id, T);
				Token=ObterToken(Lexema); 
				break;
		case ',': 	IniciarSegmentoDeDados();
				DefinirVariavelGlobal(Id, T);
				while (Token==',') 
    			   	{
      					Token=ObterToken(Lexema);
      					VariavelGlobal(Id);
					DefinirVariavelGlobal(Id, T);
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
				DefinirNomeDaSubRotina(Id);
				IniciarSubRotina(Id);
				Token=ObterToken(Lexema);
    				DeclaracoesDeParametros(&NP);
				DefinirSubRotina(ObterNomeDaSubRotina(), T, NP);
    				if (Token==')')
    				{
      					Token=ObterToken(Lexema);
      					Bloco();
					TerminarSubRotina(Id);
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
	//Listar();
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
		TerminarMontagem("main");
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
