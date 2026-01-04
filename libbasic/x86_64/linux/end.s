        .text
        .align 4,0x90

.globl _basic_exit
_basic_exit:
        xorq %rax, %rax
        pushq %rax
        call _exit
        ret
