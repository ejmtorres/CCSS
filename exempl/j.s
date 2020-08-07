.data
.comm _C, 129, 1

.text

.global _Jota
_Jota:
                                leal  _C, %ebx
                                pushl %ebx
                                call  _lercad
                                addl  $4, %esp
                                jmp   R1
.data
R0:
.byte '.'
.byte 0

.text
R1:
                                leal  R0, %ebx
                                pushl %ebx
                                call  _impcad
                                addl  $4, %esp
                                leal  _C, %ebx
                                pushl %ebx
                                call  _impcad
                                addl  $4, %esp
                                movl  $0, %ebx
                                movl  $1, %eax
                                int   $0x80
.global _start
_start:
                                jmp   _Jota
