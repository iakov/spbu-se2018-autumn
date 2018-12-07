	.file	"sort.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	swap
	.type	swap, @function
swap:
.LFB60:
	.cfi_startproc
	movl	(%rdi), %eax
	movl	(%rsi), %edx
	movl	%edx, (%rdi)
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE60:
	.size	swap, .-swap
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	sort
	.type	sort, @function
sort:
.LFB61:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$416, %rsp
	.cfi_def_cfa_offset 448
	movq	%fs:40, %rax
	movq	%rax, 408(%rsp)
	xorl	%eax, %eax
	testl	%esi, %esi
	jle	.L3
	leal	-1(%rsi), %eax
	movq	%rax, %rbp
	leaq	4(,%rax,4), %rcx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L4:
	movl	(%rdi,%rax), %edx
	movl	%edx, (%rsp,%rax)
	addq	$4, %rax
	cmpq	%rax, %rcx
	jne	.L4
	xorl	%r10d, %r10d
	testl	%ebp, %ebp
	movq	%rdi, %rbx
	je	.L11
	.p2align 4,,10
	.p2align 3
.L18:
	leal	1(%r10), %r11d
	cmpl	%r11d, %esi
	jle	.L29
	movl	(%rbx), %r12d
	movslq	%r11d, %rax
	movl	%r11d, %edx
	leaq	(%rdi,%rax,4), %rax
	movl	%r12d, %r8d
	jmp	.L9
	.p2align 4,,10
	.p2align 3
.L30:
	addl	$1, %edx
	movslq	%r10d, %rcx
	addq	$4, %rax
	cmpl	%edx, %esi
	leaq	(%rdi,%rcx,4), %r9
	je	.L7
.L9:
	movl	(%rax), %ecx
	movq	%rax, %r9
	cmpl	%r8d, %ecx
	jge	.L30
	movl	%edx, %r10d
	addl	$1, %edx
	addq	$4, %rax
	cmpl	%edx, %esi
	movl	%ecx, %r8d
	jne	.L9
.L7:
	movl	%r12d, (%r9)
	addq	$4, %rbx
	movl	%r8d, -4(%rbx)
	cmpl	%ebp, %r11d
	movl	%r11d, %r10d
	jl	.L18
	testl	%esi, %esi
	jle	.L3
.L11:
	xorl	%edx, %edx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L14:
	movl	(%rdi,%rdx,4), %ebx
	xorl	%ecx, %ecx
	cmpl	%ebx, (%rsp,%rdx,4)
	setne	%cl
	addq	$1, %rdx
	addl	%ecx, %eax
	cmpl	%edx, %esi
	jg	.L14
.L12:
	movq	408(%rsp), %rsi
	xorq	%fs:40, %rsi
	jne	.L31
	addq	$416, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L29:
	.cfi_restore_state
	movl	(%rbx), %r8d
	movq	%rbx, %r9
	movl	%r8d, %r12d
	jmp	.L7
.L3:
	xorl	%eax, %eax
	jmp	.L12
.L31:
	call	__stack_chk_fail
	.cfi_endproc
.LFE61:
	.size	sort, .-sort
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
