.data
.global _A
_A:
.long 0
.global _B
_B:
.long 0
.global _C
_C:
.long 0

.text
_func:
                                pushl %ebp
                                movl  %esp, %ebp
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
