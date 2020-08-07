/*----------------------------------*/
/* Autor: Elias Jose Moreira Torres */
/* <ejmt_ce@yahoo.com.br>           */
/* Este software esta disponivel    */
/* via licenca GPL                  */
/*----------------------------------*/

/*---------------------------------------*/
/* lib_es.asm - biblioteca de rotinas de */
/* entrada e saida do compilador CCSS    */
/* Autor: Elias Jose Moreira Torres      */
/* dezembro de 2005                      */
/*---------------------------------------*/

.data

.comm Digitos, 11, 1

Caract:
.long 0

Negativo:
.long 0

Dez:
.long 10

TamCad:
.long 129

UltCar:
.long 10

ProxLin:
.long 10

.text
/*--------------------------------------*/
/* rotina para ler cadeia de caracteres */
/* para buffer apontado por 8(%ebp)     */
/*--------------------------------------*/
.global _lercad
_lercad:
                                pushl %ebp
                                movl  %esp, %ebp

				pushl %eax
				pushl %ebx
				pushl %ecx
				pushl %edx

				movl  $3, %eax
				movl  $0, %ebx
				movl  8(%ebp) ,%ecx
				movl  $129, %edx
				int   $0x80
				
				movl  8(%ebp), %edi
				movl  UltCar, %eax
				repne scasb
				decl  %edi
				movl  $0, (%edi)

				popl  %edx
				popl  %ecx
				popl  %ebx
				popl  %eax

				movl  %ebp, %esp
                                popl  %ebp
                                ret

/*--------------------------------*/
/* rotina para imprimir caractere */
/* apontado por 8(%ebp)           */
/*--------------------------------*/
.global _impcar
_impcar:
                                pushl %ebp
                                movl  %esp, %ebp

				pushl %eax
				pushl %ebx
				pushl %ecx
				pushl %edx

				movl  $4, %eax
				movl  $1, %ebx
				movl  8(%ebp) ,%ecx
				movl  $1, %edx
				int   $0x80

				popl  %edx
				popl  %ecx
				popl  %ebx
				popl  %eax

                                movl  %ebp, %esp
                                popl  %ebp
                                ret

/*-------------------------------------------*/
/* rotina para imprimir cadeia de caracteres */
/* apontada por 8(%ebp)                      */
/*-------------------------------------------*/
.global _impcad
_impcad:
                                pushl %ebp
                                movl  %esp, %ebp

				pushl %eax
				pushl %ebx

				movl  8(%ebp), %ebx
impcad_rep:			
				movb  (%ebx), %al
				cmpb  $0, %al
				je    impcad_fim
				cmpb  $'\', %al
				jne   impcad_normal
				incl  %ebx
				movb  (%ebx), %al
				cmpb  $'n', %al				
				je    impcad_n
				movl  $'\\', Caract
				movl  $Caract, %eax
				pushl %eax
				call  _impcar
				addl  $4, %esp
				jmp   impcad_normal
				
impcad_n:			
				movl  ProxLin, %eax
				movl  %eax, Caract
				movl  $Caract, %eax
				pushl %eax
				call  _impcar
				addl  $4, %esp
				incl  %ebx
				jmp   impcad_rep
impcad_normal:			
				pushl %ebx
				call  _impcar
				addl  $4, %esp
				incl  %ebx
				jmp   impcad_rep
impcad_fim:
				popl  %ebx
				popl  %eax

                                movl  %ebp, %esp
                                popl  %ebp
                                ret

/*---------------------------------*/
/* rotina para ler um inteiro para */
/* endereco apontado por 8(%ebp)   */
/*---------------------------------*/
.global _lerint
_lerint:
                                pushl %ebp
                                movl  %esp, %ebp

				pushl %eax
				pushl %ebx
				pushl %ecx
				pushl %edx

lerinterro:                     
				movl  $Digitos, %ebx
				pushl %ebx
				call  _lercad
				addl  $4, %esp
				movl  $0, %eax
                                movl  $0, %ebx
				movl  $0, %ecx
lerintcx1:                      
				movb  Digitos(%ebx), %dl
				cmpb  $10, %dl
				je    lerintcx2
				incl  %ecx
				incl  %ebx
				jmp   lerintcx1
lerintcx2:				
				jecxz lerintfim
				movl  $0, %ebx
				movb  Digitos(%ebx), %dl
                                cmpb  $'-', %dl
                                jne   lerintpositivo
                                movl  $1, Negativo
                                incl  %ebx
				decl  %ecx
                                jmp   lerintcontinua
lerintpositivo:                 
				movl  $0, Negativo
lerintcontinua:                 
				mull  Dez
                                movb  Digitos(%ebx), %dl
                                cmpb  $'0', %dl
                                jb    lerinterro
                                cmpb  $'9', %dl
                                ja    lerinterro
                                subb  $'0', %dl
                                movb  $0, %dh
                                addl  %edx, %eax
                                inc   %ebx
                                loop  lerintcontinua
                                cmpl  $1, Negativo
                                jne   lerintfim
                                neg   %eax
lerintfim:                      
				movl  8(%ebp), %ebx
                                movl  %eax, (%ebx)

				popl  %edx
				popl  %ecx
				popl  %ebx
				popl  %eax

				movl  %ebp, %esp
                                popl  %ebp
                                ret

/*-----------------------------------------*/
/* rotina para imprimir inteiro em 8(%ebp) */
/*-----------------------------------------*/
.global _impint
_impint:
                                pushl %ebp
                                movl  %esp, %ebp

				pushl %eax
				pushl %ecx
				pushl %edx

                                movl  8(%ebp), %eax
                                cmpl  $0, %eax
                                je    impintzero
                                jg    impintpositivo
                                negl  %eax
                                movl  $'-', Caract
				movl  $Caract, %edx
                                pushl %edx
                                call  _impcar
                                addl  $4, %esp
impintpositivo:                 
				movl  $0, %ecx
impintempilha:                  
				movl  $0, %edx
                                idivl Dez
                                pushl %edx
                                incl  %ecx
                                cmpl  $0, %eax
                                jne   impintempilha
impintdesempilha:               
				popl  %edx
                                addl  $0x0030, %edx
				movl  %edx, Caract
				movl  $Caract, %edx
                                pushl %edx
                                call  _impcar
                                addl  $4, %esp
                                decl  %ecx
                                cmpl  $0, %ecx
                                jne   impintdesempilha
                                jmp   impintfim
impintzero:                     
				movl  $'0', Caract
				movl  $Caract, %edx
                                pushl %edx
                                call  _impcar
                                addl  $4, %esp

impintfim:                      
				popl  %edx
				popl  %ecx
				popl  %eax

				movl  %ebp, %esp
                                popl  %ebp
                                ret
