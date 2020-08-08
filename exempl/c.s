
.text

.global _Simples
_Simples:
                                movl  $123, %ebx
                                pushl %ebx
                                call  _impint
                                addl  $4, %esp
                                movl  $456, %ebx
                                pushl %ebx
                                call  _impint
                                addl  $4, %esp
                                movl  $789, %ebx
                                pushl %ebx
                                call  _impint
                                addl  $4, %esp
                                movl  $0, %ebx
                                movl  $1, %eax
                                int   $0x80
.global _start
_start:
                                jmp   _Simples
