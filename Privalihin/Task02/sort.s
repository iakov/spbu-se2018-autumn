	.file	"sort.c"
	.text
	.globl	sort
	.def	sort;	.scl	2;	.type	32;	.endef
	.seh_proc	sort
sort:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_setframe	%rbp, 16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L6:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8(%rbp)
	jmp	.L3
.L5:
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	16(%rbp), %rax
	movl	(%rax), %edx
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jle	.L4
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -12(%rbp)
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	16(%rbp), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	16(%rbp), %rdx
	movl	(%rdx), %edx
	movl	%edx, (%rax)
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	16(%rbp), %rax
	movl	-12(%rbp), %edx
	movl	%edx, (%rax)
.L4:
	addl	$1, -8(%rbp)
.L3:
	movl	-8(%rbp), %eax
	cmpl	24(%rbp), %eax
	jl	.L5
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cmpl	24(%rbp), %eax
	jl	.L6
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
