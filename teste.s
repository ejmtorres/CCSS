.data
.global _I1
_I1:
.long 0
.data
.global _C1
_C1:
.byte 0
.global _C2
_C2:
.byte 0

.text
_main:
                                pushl %ebp
                                movl  %esp, %ebp
                                movl  %ebp, %esp
                                popl  %ebp
                                ret
