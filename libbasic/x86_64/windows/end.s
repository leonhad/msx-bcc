        .text
        .align 4,0x90

.globl _basic_exit
_basic_exit:
        xorq %rax, %rax
        pushq %rax
        call _exit
        ret


.globl _main
_main:
        pushq %rbp
        movq %rsp, %rbp
        subq $16, %rsp

        //xor %edi, %edi
        //call _basic_exit

        xorq %rax, %rax
        leave
        ret
