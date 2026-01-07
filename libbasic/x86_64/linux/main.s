    .text
    .p2align 4
	.type _start, @function
.globl _start
_start:
    .cfi_startproc
	endbr64

    pushq %rbp
    movq %rsp, %rbp

    call _basic_start
    call _basic_end

    xorl	%eax, %eax
    popq %rbp
    ret

    .cfi_endproc

