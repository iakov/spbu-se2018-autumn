	.file	"sort.c"
	.text
	.p2align 4,,15
	.globl	sort
	.type	sort, @function
sort:
.LFB0:
	.cfi_startproc
	leal	-2(%rsi), %eax
	leaq	4(%rdi,%rax,4), %r8
	.p2align 4,,10
	.p2align 3
.L5:
	cmpl	$1, %esi
	jle	.L1
	movq	%rdi, %rax
	xorl	%r9d, %r9d
	.p2align 4,,10
	.p2align 3
.L4:
	movl	(%rax), %edx
	movl	4(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L3
	movl	%ecx, (%rax)
	movl	%edx, 4(%rax)
	movl	$1, %r9d
.L3:
	addq	$4, %rax
	cmpq	%r8, %rax
	jne	.L4
	testl	%r9d, %r9d
	jne	.L5
.L1:
	rep ret
	.cfi_endproc
