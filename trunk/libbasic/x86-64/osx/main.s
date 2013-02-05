        .text
        .align 4,0x90

.globl _main
_main:
        pushq %rbp
        movq %rsp, %rbp

        call _basic_start
        call _basic_end
