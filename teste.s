.data
.global _I1
_I1:
.long 0
<<<<<<< HEAD
.global _C1
_C1:
.byte 0
.global _C2
_C2:
.byte 0

.text
=======
.data
.global _C1
_C1:
.byte 0

.text
_main:
                                pushl %ebp
                                movl  %esp, %ebp
                                movl  %ebp, %esp
                                popl  %ebp
                                ret
>>>>>>> dcc950ab22e2879c3a4b7c27be50d6816311fc9c
