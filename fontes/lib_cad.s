/*----------------------------------*/
/* Autor: Elias Jose Moreira Torres */
/* <ejmt_ce@yahoo.com.br>           */
/* Este software esta disponivel    */
/* via licenca GPL                  */
/*----------------------------------*/

/*-------------------------------------*/
/* lib_cad.asm - biblioteca de rotinas */
/* para manipular cadeias de caractere */
/* do compilador CCSS                  */
/* Autor: Elias Jose Moreira Torres    */
/* agosto de 2020                      */
/*-------------------------------------*/

.text
/*---------------------------------------*/
/* rotina para concatenar duas cadeias   */
/* de caracteres  apontadas por 12(%ebp) */
/* e 8(%ebp)                             */
/*---------------------------------------*/
.globl _conccad
_conccad: 
                                pushl %ebp
                                movl  %esp, %ebp

                                pushl %eax
                                pushl %ecx
                                pushl %esi
                                pushl %edi
				pushf

                                cld
                                movl  $129, %ecx
                                movl  $0, %eax
                                movl  12(%ebp), %edi
                                repne scasb
                                dec   %edi
                                movl  8(%ebp), %esi
                                rep   movsb

				popf
                                popl  %edi
                                popl  %esi
                                popl  %ecx
                                popl  %eax

                                movl  %ebp, %esp
                                popl  %ebp
                                ret

/*----------------------------------*/
/* rotina para copiar uma cadeia    */
/* apontada por 8(%ebp)  para outra */
/* apontada por 12(%ebp)            */
/*----------------------------------*/
.globl _copcad
_copcad:
                                pushl %ebp
                                movl  %esp, %ebp

                                pushl %eax
                                pushl %ebx
                                pushl %ecx
                                pushl %edx
                                pushl %esi
                                pushl %edi
                                pushf

                                cld
                                movl  12(%ebp), %edi
                                movl  8(%ebp), %esi
copcadloop:                     
				cmpl  $0, (%esi)
                                je    copcadfim
                                movsb
                                jmp   copcadloop
copcadfim:                      
				movsb

                                popf
                                popl  %edi
                                popl  %esi
                                popl  %edx
                                popl  %ecx
                                popl  %ebx
                                popl  %eax

                                movl  %ebp, %esp
                                popl  %ebp
                                ret

/*-----------------------------------*/
/* rotina para comparar duas cadeias */
/* apontadas por 16(%ebp) e 12(%ebp) */
/* resultado em 8(%ebp)              */
/* = -1 se primeira < segunda        */
/* = +1 se primeira > segunda        */
/* = 0  se primeira = segunda        */
/*-----------------------------------*/
.globl _cmpcad
_cmpcad:
                                pushl %ebp
                                movl  %esp, %ebp

                                pushl %eax
                                pushl %ebx
                                pushl %ecx
                                pushl %edx
                                pushl %esi
                                pushl %edi
                                pushf

                                movl  16(%ebp), %esi
                                movl  12(%ebp), %edi
cmpcadloop:                     
				cmpsb
                                ja    cmpcadmaior
                                jb    cmpcadmenor
                                dec   %esi
                                cmpl  $0, (%esi)
                                je    cmpcadigual
                                inc   %esi
                                jmp   cmpcadloop
cmpcadmaior:                    
				movl  $1, %eax
                                jmp   cmpcadfim
cmpcadmenor:                    
				movl  $-1, %eax
                                jmp   cmpcadfim
cmpcadigual:                    
				movl  $0, %eax
cmpcadfim:                      
				movl  8(%ebp), %ebx
                                movl  %eax, (%ebx)

                                popf
                                popl  %edi
                                popl  %esi
                                popl  %edx
                                popl  %ecx
                                popl  %ebx
                                popl  %eax

                                movl  %ebp, %esp
                                popl  %ebp
                                ret
