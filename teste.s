
.text
_func:
                                pushl %ebp
                                movl  %esp, %ebp
                                movl  $2, %ebx
                                pushl %ebx
                                movl  $3, %ebx
                                movl  $4, %ecx
                                movl  $0, %edx
                                xchgl %eax, %ebx
                                idivl %ecx
                                xchgl %eax, %ebx
                                movl  $1, %ecx
                                subl  %ecx, %ebx
                                movl  %ebx, %ecx
                                popl  %ebx
                                xchgl %eax, %ebx
                                imull %ecx
                                xchgl %eax, %ebx
                                movl  %ebx, 8(%ebp)
                                movl  %ebp, %esp
                                popl  %ebp
                                ret

.text
_main:
                                pushl %ebp
                                movl  %esp, %ebp
                                movl  %ebp, %esp
                                popl  %ebp
                                ret
.global _start
_start:
                                call  _main
                                movl  $0, %ebx
                                movl  $1, %eax
                                int   $0x80
