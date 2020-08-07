
.text

.global _Vetor
_Vetor:
                                pushl %ebp
                                movl  %esp, %ebp
                                subl  $12, %esp
                                subl  $36, %esp
                                movl  $0, %ebx
                                movl  %ebx, -12(%ebp)
                                movl  $0, %ebx
                                movl  %ebx, -4(%ebp)
R0:
                                movl  -4(%ebp), %ebx
                                movl  $3, %ecx
                                cmpl  %ecx, %ebx
                                jl    R1
                                movl  $0, %ebx
                                jmp   R2
R1:
                                movl  $1, %ebx
R2:
                                cmpl  $0, %ebx
                                jne   R3
                                jmp   R4
R3:
                                movl  $0, %ebx
                                movl  %ebx, -8(%ebp)
R5:
                                movl  -8(%ebp), %ebx
                                movl  $3, %ecx
                                cmpl  %ecx, %ebx
                                jl    R6
                                movl  $0, %ebx
                                jmp   R7
R6:
                                movl  $1, %ebx
R7:
                                cmpl  $0, %ebx
                                jne   R8
                                jmp   R9
R8:
                                movl  $0, %eax
                                movl  -4(%ebp), %ebx
                                addl  %ebx, %eax
                                movl  -8(%ebp), %ebx
                                movl  $3, %ecx
                                mull  %ecx
                                addl  %ebx, %eax
                                addl  %eax, %eax
                                addl  %eax, %eax
                                leal  -48(%ebp), %ebx
                                addl  %ebx, %eax
                                pushl %eax
                                movl  -12(%ebp), %ebx
                                popl  %eax
                                xchgl %ebx, %eax
                                movl  %eax, (%ebx)
                                movl  -12(%ebp), %ebx
                                movl  $1, %ecx
                                addl  %ecx, %ebx
                                movl  %ebx, -12(%ebp)
                                movl  -8(%ebp), %ebx
                                movl  $1, %ecx
                                addl  %ecx, %ebx
                                movl  %ebx, -8(%ebp)
                                jmp   R5
R9:
                                movl  -4(%ebp), %ebx
                                movl  $1, %ecx
                                addl  %ecx, %ebx
                                movl  %ebx, -4(%ebp)
                                jmp   R0
R4:
                                movl  $0, %ebx
                                movl  %ebx, -4(%ebp)
R10:
                                movl  -4(%ebp), %ebx
                                movl  $3, %ecx
                                cmpl  %ecx, %ebx
                                jl    R11
                                movl  $0, %ebx
                                jmp   R12
R11:
                                movl  $1, %ebx
R12:
                                cmpl  $0, %ebx
                                jne   R13
                                jmp   R14
R13:
                                movl  $0, %ebx
                                movl  %ebx, -8(%ebp)
R15:
                                movl  -8(%ebp), %ebx
                                movl  $3, %ecx
                                cmpl  %ecx, %ebx
                                jl    R16
                                movl  $0, %ebx
                                jmp   R17
R16:
                                movl  $1, %ebx
R17:
                                cmpl  $0, %ebx
                                jne   R18
                                jmp   R19
R18:
                                jmp   R21
.data
R20:
.byte 'V','e','t','['
.byte 0

.text
R21:
                                leal  R20, %ebx
                                pushl %ebx
                                call  _impcad
                                addl  $4, %esp
                                movl  -4(%ebp), %ebx
                                pushl %ebx
                                call  _impint
                                addl  $4, %esp
                                jmp   R23
.data
R22:
.byte ','
.byte 0

.text
R23:
                                leal  R22, %ebx
                                pushl %ebx
                                call  _impcad
                                addl  $4, %esp
                                movl  -8(%ebp), %ebx
                                pushl %ebx
                                call  _impint
                                addl  $4, %esp
                                jmp   R25
.data
R24:
.byte ']',' ','=',' '
.byte 0

.text
R25:
                                leal  R24, %ebx
                                pushl %ebx
                                call  _impcad
                                addl  $4, %esp
                                pushl %ebx
                                movl  $0, %eax
                                movl  -4(%ebp), %ebx
                                addl  %ebx, %eax
                                movl  -8(%ebp), %ebx
                                movl  $3, %ecx
                                mull  %ecx
                                addl  %ebx, %eax
                                popl  %ebx
                                addl  %eax, %eax
                                addl  %eax, %eax
                                leal  -48(%ebp), %ebx
                                addl  %eax, %ebx
                                movl  (%ebx), %ebx
                                pushl %ebx
                                call  _impint
                                addl  $4, %esp
                                jmp   R27
.data
R26:
.byte ' '
.byte 0

.text
R27:
                                leal  R26, %ebx
                                pushl %ebx
                                call  _impcad
                                addl  $4, %esp
                                movl  -8(%ebp), %ebx
                                movl  $1, %ecx
                                addl  %ecx, %ebx
                                movl  %ebx, -8(%ebp)
                                jmp   R15
R19:
                                jmp   R29
.data
R28:
.byte '\','n'
.byte 0

.text
R29:
                                leal  R28, %ebx
                                pushl %ebx
                                call  _impcad
                                addl  $4, %esp
                                movl  -4(%ebp), %ebx
                                movl  $1, %ecx
                                addl  %ecx, %ebx
                                movl  %ebx, -4(%ebp)
                                jmp   R10
R14:
                                movl  %ebp, %esp
                                popl  %ebp
                                ret

.text

.global _Prog
_Prog:
                                call  _Vetor
                                movl  $0, %ebx
                                movl  $1, %eax
                                int   $0x80
.global _start
_start:
                                jmp   _Prog
