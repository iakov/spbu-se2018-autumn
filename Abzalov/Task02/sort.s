	.file	"sort.c"
	.text
	.globl	_sort
	.def	_sort;	.scl	2;	.type	32;	.endef
_sort:
LFB14:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$72, %esp
	movl	20(%ebp), %eax
	subl	$1, %eax
	cmpl	16(%ebp), %eax
	jne	L2
	movl	$0, %eax
	jmp	L1
L2:
	movl	16(%ebp), %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, -36(%ebp)
	movl	$0, 16(%esp)
	movl	-36(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_sort
	movl	$0, 16(%esp)
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-36(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_sort
	movl	16(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-36(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	20(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, -40(%ebp)
	movl	$0, -20(%ebp)
	jmp	L4
L8:
	movl	-16(%ebp), %eax
	cmpl	20(%ebp), %eax
	jge	L5
	movl	-12(%ebp), %eax
	cmpl	-36(%ebp), %eax
	jge	L6
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %ecx
	movl	8(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jge	L6
L5:
	movl	-20(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	-40(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, (%ecx)
	jmp	L7
L6:
	movl	-20(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	-40(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	-16(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -16(%ebp)
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, (%ecx)
L7:
	addl	$1, -20(%ebp)
L4:
	movl	20(%ebp), %eax
	subl	16(%ebp), %eax
	cmpl	-20(%ebp), %eax
	jg	L8
	movl	$0, -24(%ebp)
	jmp	L9
L10:
	movl	-24(%ebp), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-24(%ebp), %eax
	leal	0(,%eax,4), %ecx
	movl	-40(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	%eax, (%edx)
	addl	$1, -24(%ebp)
L9:
	movl	20(%ebp), %eax
	subl	16(%ebp), %eax
	cmpl	-24(%ebp), %eax
	jg	L10
	cmpl	$0, 24(%ebp)
	je	L11
	movl	$0, -28(%ebp)
	movl	$0, -32(%ebp)
	jmp	L12
L13:
	movl	-32(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-32(%ebp), %eax
	leal	0(,%eax,4), %ecx
	movl	12(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	setne	%al
	movzbl	%al, %eax
	addl	%eax, -28(%ebp)
	addl	$1, -32(%ebp)
L12:
	movl	-32(%ebp), %eax
	cmpl	20(%ebp), %eax
	jl	L13
	movl	-28(%ebp), %eax
	jmp	L1
L11:
L1:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_malloc;	.scl	2;	.type	32;	.endef
