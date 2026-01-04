	.text
	.align 4,0x90

.globl _basic_clear
_basic_clear:
	pushq	%rbp
	movq	%rsp, %rbp
	testl	%esi, %esi
	jle	Lend
	movslq	%esi, %rax
	movl	$0, (%rdi,%rax,4)
Lend:
	popq	%rbp
	ret
