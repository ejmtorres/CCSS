
.text
_func:
                                pushl %ebp
                                movl  %esp, %ebp
                                movl  8(%ebp), %ebx
                                movl  12(%ebp), %ecx
                                addl  %ecx, %ebx
                                movl  %ebx, %eax
                                movl  %ebp, %esp
                                popl  %ebp
                                ret

.text
_main:
                                pushl %ebp
                                movl  %esp, %ebp
                                movl  $1, %ebx
                                pushl %ebx
                                movl  $2, %ebx
                                pushl %ebx
                                call  _func
                                addl  $8, %esp
                                movl  %eax, %ebx
                                movl  %ebx, %eax
                                movl  %ebp, %esp
                                popl  %ebp
                                ret
.global _start
_start:
                                call  _main
                                movl  %eax, %ebx
                                movl  $1, %eax
                                int   $0x80
