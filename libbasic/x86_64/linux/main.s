    .text
    .align 4,0x90

.globl _start
_start:
    pushq %rbp
    movq %rsp, %rbp

    call _basic_start
    call _basic_end

    popq %rbp
    ret
