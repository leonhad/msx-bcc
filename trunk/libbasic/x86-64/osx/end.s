	.text
	.align 4,0x90

.globl _basic_end
_basic_end:
	pushq %rbp
	movq %rsp, %rbp

	xorl %edi, %edi
	call _exit
