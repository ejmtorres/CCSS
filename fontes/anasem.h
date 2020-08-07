/*----------------------------------*/
/* Autor: Elias Jose Moreira Torres */
/* <ejmt_ce@yahoo.com.br>           */
/* Este software esta disponivel    */
/* via licenca GPL                  */
/*----------------------------------*/
#include "ccss.h"

/*---------------------------------*/
/* anasem.h - analisador semantico */
/*---------------------------------*/
/* definicoes gerais */
#define TAM_TABELA 50 /* tamanho da tabela de simbolos */
#define TAM_NOME 30   /* tamanho maximo de um identificador */
#define NUM_REG 4     /* numero maximo de registradores alocados */
#define NADA -1       /* entrada nula da tabela de simbolos */
#define BRANCO " "    /* usado para alinhamento */
#define TAM_SEGM  0xffffffffL /* tamanho de um segmento */
#define TAM_PILHA TAM_SEGM /* tamanho da pilha */
#define TAM_DADOS TAM_SEGM /* tamanho de seg de dados */
#define DESL_INIC 8 /* deslocamento inicial dos parametros na pilha */
#define NBYTE_LIN 18 /* numero de bytes gerados por linha em cadeias */
/* nome do segmento de pilha */
#ifndef SEG_PIL
#define SEG_PIL "pilha"
#endif
/* nome de segmento de dados */
#ifndef SEG_DAD
#define SEG_DAD "dados"
#endif
/*nome do segmento de codigo */
#ifndef SEG_COD
#define SEG_COD "codig"
#endif
/* nome do grupo formado pelos segmentos de dados e pilha */
#ifndef GRUPO_D
#define GRUPO_D "grupo"
#endif
/* categorias de identificadores */
#define CPROG 1 /* programa */
#define CPROC 2 /* procedimento */
#define CFUNC 3 /* funcao */
#define CVARG 4 /* variavel global */
#define CVARL 5 /* variavel local */
#define CPAR  6 /* parametro simples */
#define CTIPO 7 /* tipo estruturado */
#define CVETG 8 /* vetor global */
#define CVETL 9 /* vetor local */
/* niveis lexicos */
#define NGLOBAL 0
#define NLOCAL  1
/* numero de bytes para ...*/
#define NB_CHAR     1
#define NB_INTEIRO  4
#define NB_PONTEIRO 4
#define NB_CADEIA   128
/* alinhamento para vetores */
#define ALIN_INT 4
#define ALIN_PON 4
#define ALIN_CAD 1
/* tipo simbolo */
typedef struct
        {
          char Nome[TAM_NOME];    /* nome do identifador */
          int  Categ;             /* categoria */
          int  Nivel;             /* nivel lexico */
          long Desl;              /* offset */
          int  Tipo;              /* tipo */
        }
        TSimbolo;

/*-----------------------------------------------*/
/* iniciar o espaco alocado no segmento de dados */
/*-----------------------------------------------*/
PUBLIC void IniciarEspacoGlobal();
/*--------------------------------*/
/* definir nivel lexico igual a N */
/*--------------------------------*/
PUBLIC void DefinirNivel(int N);
/*----------------------------------*/
/* definir nome do tipo estruturado */
/*----------------------------------*/
PUBLIC void DefinirNomeDoTipo(char *Id);
/*--------------------------------*/
/* obter nome do tipo estruturado */
/*--------------------------------*/
PUBLIC char *ObterNomeDoTipo();
/*--------------------------*/
/* definir nome do programa */
/*--------------------------*/
PUBLIC void DefinirNomeDoPrograma(char *Id);
/*------------------------*/
/* obter nome do programa */
/*------------------------*/
PUBLIC char *ObterNomeDoPrograma();
/*----------------------------*/
/* definir nome da sub rotina */
/*----------------------------*/
PUBLIC void DefinirNomeDaSubRotina(char *Id);
/*--------------------------*/
/* obter nome da sub rotina */
/*--------------------------*/
PUBLIC char *ObterNomeDaSubRotina();
/*------------------------------------------------*/
/* salvar registradores antes do abre parenteses  */
/*------------------------------------------------*/
PUBLIC void SalvarRegistradores(int *T);
/*----------------------------------------------------*/
/* recuperar registradores depois do fecha parenteses */
/*----------------------------------------------------*/
PUBLIC void RecuperarRegistradores(int *R, int T);
/*-----------------------------------------------*/
/* associar um arquivo a um analisador semantico */
/*-----------------------------------------------*/
PUBLIC void IniciarAnalisadorSemantico(char *NomeAsm);
/*----------------------------------------*/
/* definir N-esima dimensao do tipo vetor */
/*----------------------------------------*/
PUBLIC void DefinirN_ezimaDimensao(char *Id, char *D);
/*---------------------------------------*/
/* definir tipo base do tipo estruturado */
/*---------------------------------------*/
PUBLIC void DefinirTipoBase(int T, int NDim);
/*-----------------------------------*/
/* obter entrada da tabela para tipo */
/*-----------------------------------*/
PUBLIC int ObterTipo(char *Id);
/*-------------------------------------*/
/* obter categoria de um identificador */
/*-------------------------------------*/
PUBLIC int ObterCategoria(char *Id);
/*----------------------------*/
/* iniciar segmento de codigo */
/*----------------------------*/
PUBLIC void IniciarSegmentoDeCodigo();
/*-----------------------------*/
/* terminar segmento de codigo */
/*-----------------------------*/
PUBLIC void TerminarSegmentoDeCodigo();
/*---------------------------*/
/* definir segmento de pilha */
/*---------------------------*/
PUBLIC void DefinirSegmentoDePilha();
/*---------------------------*/
/* iniciar segmento de dados */
/*---------------------------*/
PUBLIC void IniciarSegmentoDeDados();
/*----------------------------*/
/* terminar segmento de dados */
/*----------------------------*/
PUBLIC void TerminarSegmentoDeDados();
/*--------------------------*/
/* gerar diretivas iniciais */
/*--------------------------*/
PUBLIC void IniciarMontagem();
/*--------------------------------------*/
/* gerar ponto de entrada se for o caso */
/*--------------------------------------*/
PUBLIC void TerminarMontagem(char *Inicio);
/*---------------------------------------*/
/* definir e gerar codigo para variavel */
/*---------------------------------------*/
PUBLIC void DefinirVariavelGlobal(char *Id, int Tipo);
/*----------------------------------------*/
/* definir e gerar codigo para parametro */
/*----------------------------------------*/
PUBLIC void DefinirParametro(char *Id, int Tipo);
/*-----------------------------------------*/
/* ajustar os deslocamentos dos parametros */
/*-----------------------------------------*/
PUBLIC void AjustarParametros(int N);
/*---------------------------*/
/* gerar armazenamento local */
/*---------------------------*/
PUBLIC void DefinirVariavelLocal(long *N);
/*----------------------------*/
/* iniciar programa principal */
/*----------------------------*/
PUBLIC void IniciarPrograma(char *Id);
/*-----------------------------*/
/* terminar programa principal */
/*-----------------------------*/
PUBLIC void TerminarPrograma(char *Id);
/*----------------------*/
/* iniciar sub-rotina   */
/*----------------------*/
PUBLIC void IniciarSubRotina(int Escopo, char *Id);
/*-----------------------*/
/* terminar sub-rotina   */
/*-----------------------*/
PUBLIC void TerminarSubRotina(char *Id);
/*---------------*/
/* iniciar bloco */
/*---------------*/
PUBLIC void IniciarBloco(char *Id, int TipoSub);
/*----------------*/
/* terminar bloco */
/*----------------*/
PUBLIC void TerminarBloco();
/*-------------------------------------*/
/* ajustar o tipo de retorno da funcao */
/*-------------------------------------*/
PUBLIC void AjustarTipoDaFuncao(char *NomeFunc, int TipoRet);
/*--------------------------*/
/* iniciar chamada a funcao */
/*--------------------------*/
PUBLIC void IniciarFuncao(int *NA, int *NB, int *TA);
/*---------------------------*/
/* terminar chamada a funcao */
/*---------------------------*/
PUBLIC void TerminarFuncao(int *R, int *T, int NA, int NB, int TA, char *Id);
/*---------------------*/
/* iniciar fator vetor */
/*---------------------*/
PUBLIC void IniciarFatorVetor(int  *NI, int *TA, int *R, int *T, int *P,
                              char *Id);
/*----------------------*/
/* terminar fator vetor */
/*----------------------*/
PUBLIC void TerminarFatorVetor(int NI, int TA, int R, char *Id);
/*-----------------------------*/
/* iniciar atribuicao de vetor */
/*-----------------------------*/
PUBLIC void IniciarAtribuicaoVetor(int *NI, int *T, int *P, char *Id);
/*------------------------------*/
/* terminar atribuicao de vetor */
/*------------------------------*/
PUBLIC void TerminarAtribuicaoVetor(int NI, char *Id);
/*---------------------------------*/
/* operar sobre dois registradores */
/*---------------------------------*/
PUBLIC void Operar(int Op, int R1, int R2, int T1, int T2);
/*---------------------------------*/
/* operar sobre dois registradores */
/*---------------------------------*/
PUBLIC void OperarRelacao(char *Op, int R1, int R2, int T1, int T2);
/*--------------------*/
/* empilhar expressao */
/*--------------------*/
PUBLIC void EmpilharExpressao();
/*----------------------------------------*/
/* gerar codigo para acessar fator (vetor)*/
/*----------------------------------------*/
PUBLIC void GerarIndice1();
/*---------------------------------------------------*/
/* gerar codigo para acessar fator (vetor) - parte 2 */
/*---------------------------------------------------*/
PUBLIC void GerarIndiceN(int D);
/*----------------------------------*/
/* gerar expressao do tipo endereco */
/*----------------------------------*/
PUBLIC void GerarEndereco(char *Id, int *T);
/*--------------------------------*/
/* gerar expressao do tipo cadeia */
/*--------------------------------*/
PUBLIC void GerarCadeia(char *Id, int *T);
/*------------------------------------*/
/* atribuir um valor a um registrador */
/*------------------------------------*/
PUBLIC void GerarFator(int *R, int  *T, int Tk, char *Id);
/*--------------------------*/
/* gerar Fator -> valor(Id) */
/*--------------------------*/
PUBLIC void GerarFatorValor(int *R, int *T, char *Id);
/*----------------------*/
/* gerar sinal de menos */
/*----------------------*/
PUBLIC void GerarMenos(int M, int R);
/*------------------------------------------------------------*/
/* gerar codigo para valor(Id) do lado esquerdo da atribuicao */
/*------------------------------------------------------------*/
PUBLIC void GerarValor(int T, char *Id);
/*------------------------------*/
/* gerar atribuicao mov id, reg */
/*------------------------------*/
PUBLIC void GerarAtribuicao(char *Id, int T);
/*------------------------------*/
/* gerar atribuicao para vetor  */
/*------------------------------*/
PUBLIC void GerarAtribuicaoVetor(char *Id, int T);
/*-------------------------------*/
/* gerar chamada de procedimento */
/*-------------------------------*/
PUBLIC void GerarChamada(char *Id, int NA, int NB);
/*----------------------------------*/
/* gerar comando retorne expressao */
/*----------------------------------*/
PUBLIC void GerarRetorne();
/*--------------------------*/
/* gerar comando se parte 1 */
/*--------------------------*/
PUBLIC void GerarSe1(int *Rot1, int *Rot2);
/*--------------------------*/
/* gerar comando se parte 2 */
/*--------------------------*/
PUBLIC void GerarSe2(int Rot2, int *Rot3);
/*--------------------------*/
/* gerar comando se parte 3 */
/*--------------------------*/
PUBLIC void GerarSe3(int Rot3);
/*--------------------------------*/
/* gerar comando enquanto parte 1 */
/*--------------------------------*/
PUBLIC void GerarEnquanto1(int *Rot1);
/*--------------------------------*/
/* gerar comando enquanto parte 2 */
/*--------------------------------*/
PUBLIC void GerarEnquanto2(int *Rot3);
/*--------------------------------*/
/* gerar comando enquanto parte 3 */
/*--------------------------------*/
PUBLIC void GerarEnquanto3(int Rot1, int Rot3);
/*--------------------------------*/
/* gerar comando enquanto parte 1 */
/*--------------------------------*/
PUBLIC void GerarRepeticao1(int *Rot1);
/*--------------------------------*/
/* gerar comando enquanto parte 2 */
/*--------------------------------*/
PUBLIC void GerarRepeticao2(int Rot1);
/*--------------------------------------------------*/
/* desassociar o arquivo com o analisador semantico */
/*--------------------------------------------------*/
PUBLIC void TerminarAnalisadorSemantico();
/*----------------------------*/
/* listar a tabela de simbolos */
/*----------------------------*/
PUBLIC void Listar();
