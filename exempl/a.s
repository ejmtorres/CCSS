.data
.global _S
_S:
.long 0

.text

.global _FSomar
_FSomar:
                                pushl %ebp
                                movl  %esp, %ebp
                                movl  8(%ebp), %ebx
                                movl  $0, %ecx
                                cmpl  %ecx, %ebx
                                je    R0
                                movl  $0, %ebx
                                jmp   R1
R0:
                                movl  $1, %ebx
R1:
                                cmpl  $0, %ebx
                                jne   R2
                                jmp   R3
R2:
                                movl  $0, %ebx
                                movl  %ebx, %eax
                                jmp   R4
R3:
                                movl  8(%ebp), %ebx
                                pushl %ebx
                                movl  8(%ebp), %ebx
                                movl  $1, %ecx
                                subl  %ecx, %ebx
                                pushl %ebx
                                call  _FSomar
                                addl  $4, %esp
                                movl  %eax, %ecx
                                popl  %ebx
                                addl  %ecx, %ebx
                                movl  %ebx, %eax
R4:
                                movl  %ebp, %esp
                                popl  %ebp
                                ret

.global _PSomar
_PSomar:
                                pushl %ebp
                                movl  %esp, %ebp
                                subl  $4, %esp
                                movl  12(%ebp), %ebx
                                movl  $0, %ecx
                                cmpl  %ecx, %ebx
                                je    R5
                                movl  $0, %ebx
                                jmp   R6
R5:
                                movl  $1, %ebx
R6:
                                cmpl  $0, %ebx
                                jne   R7
                                jmp   R8
R7:
                                movl  $0, %ebx
                                movl  %ebx, %eax
                                movl  8(%ebp), %ebx
                                movl  %eax, (%ebx)
                                jmp   R9
R8:
                                movl  12(%ebp), %ebx
                                movl  $1, %ecx
                                subl  %ecx, %ebx
                                pushl %ebx
                                leal  -4(%ebp), %ebx
                                pushl %ebx
                                call  _PSomar
                                addl  $8, %esp
                                movl  12(%ebp), %ebx
                                movl  -4(%ebp), %ecx
                                addl  %ecx, %ebx
                                movl  %ebx, %eax
                                movl  8(%ebp), %ebx
                                movl  %eax, (%ebx)
R9:
                                movl  %ebp, %esp
                                popl  %ebp
                                ret

.text

.global _Prog
_Prog:
                                movl  $4, %ebx
                                pushl %ebx
                                leal  _S, %ebx
                                pushl %ebx
                                call  _PSomar
                                addl  $8, %esp
                                movl  _S, %ebx
                                pushl %ebx
                                call  _impint
                                addl  $4, %esp
                                jmp   R11
.data
R10:
.byte ' ','e',' '
.byte 0

.text
R11:
                                leal  R10, %ebx
                                pushl %ebx
                                call  _impcad
                                addl  $4, %esp
                                movl  $4, %ebx
                                pushl %ebx
                                call  _FSomar
                                addl  $4, %esp
                                movl  %eax, %ebx
                                pushl %ebx
                                call  _impint
                                addl  $4, %esp
                                movl  $0, %ebx
                                movl  $1, %eax
                                int   $0x80
.global _start
_start:
                                jmp   _Prog
