.data
.global _I1
_I1:
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
.data
.global _C1
_C1:
.byte 0
.global _start
_start:
                                call  _main
                                movl  $0, %ebx
                                movl  $1, %eax
                                int   $0x80
