    .text
    .align 4,0x90

.globl _basic_end
_basic_end:
    mov $60, %rax
    xor %rdi, %rdi
    syscall
