
	.text
	.globl	sort
	.def	sort;	.scl	2;	.type	32;	.endef
	.seh_proc	sort
sort:
	pushq	%rbp
	.seh_pushreg	%rbp
	subq	$416, %rsp
	.seh_stackalloc	416
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movl	%ecx, 304(%rbp)
	movq	%rdx, 312(%rbp)
	movl	$0, 276(%rbp)
	movl	$0, 284(%rbp)
	jmp	.L2
.L3:
	movl	284(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	312(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	284(%rbp), %eax
	cltq
	movl	%edx, -128(%rbp,%rax,4)
	addl	$1, 284(%rbp)
.L2:
	movl	284(%rbp), %eax
	cmpl	304(%rbp), %eax
	jl	.L3
	movl	$0, 284(%rbp)
	jmp	.L4
.L8:
	movl	284(%rbp), %eax
	addl	$1, %eax
	movl	%eax, 280(%rbp)
	jmp	.L5
.L7:
	movl	284(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	312(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	280(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	312(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jle	.L6
	movl	284(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	312(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, 272(%rbp)
	movl	284(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	312(%rbp), %rax
	addq	%rax, %rdx
	movl	280(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	312(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	movl	280(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	312(%rbp), %rax
	addq	%rax, %rdx
	movl	272(%rbp), %eax
	movl	%eax, (%rdx)
.L6:
	addl	$1, 280(%rbp)
.L5:
	movl	280(%rbp), %eax
	cmpl	304(%rbp), %eax
	jl	.L7
	addl	$1, 284(%rbp)
.L4:
	movl	284(%rbp), %eax
	cmpl	304(%rbp), %eax
	jl	.L8
	movl	$0, 284(%rbp)
	jmp	.L9
.L11:
	movl	284(%rbp), %eax
	cltq
	movl	-128(%rbp,%rax,4), %edx
	movl	284(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	312(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	je	.L10
	addl	$1, 276(%rbp)
.L10:
	addl	$1, 284(%rbp)
.L9:
	movl	284(%rbp), %eax
	cmpl	304(%rbp), %eax
	jl	.L11
	movl	276(%rbp), %eax
	addq	$416, %rsp
	popq	%rbp
	ret
	.seh_endproc
