
	.globl	hoarasort
	.def	hoarasort;	.scl	2;	.type	32;	.endef
	.seh_proc	hoarasort
hoarasort:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	24(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	32(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	24(%rbp), %edx
	movl	32(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -12(%rbp)
	jmp	.L2
.L3:
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	%eax, -12(%rbp)
	jg	.L3
	jmp	.L4
.L5:
	subl	$1, -8(%rbp)
.L4:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	%eax, -12(%rbp)
	jl	.L5
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jg	.L6
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.L7
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -16(%rbp)
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	16(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rdx), %edx
	movl	%edx, (%rax)
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	-16(%rbp), %edx
	movl	%edx, (%rax)
.L7:
	addl	$1, -4(%rbp)
	subl	$1, -8(%rbp)
.L6:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jle	.L2
	movl	-4(%rbp), %eax
	cmpl	32(%rbp), %eax
	jge	.L9
	movl	32(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %r8d
	movl	%eax, %edx
	movq	16(%rbp), %rcx
	call	hoarasort
.L9:
	movl	24(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.L11
	movl	-8(%rbp), %edx
	movl	24(%rbp), %eax
	movl	%edx, %r8d
	movl	%eax, %edx
	movq	16(%rbp), %rcx
	call	hoarasort
.L11:
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	