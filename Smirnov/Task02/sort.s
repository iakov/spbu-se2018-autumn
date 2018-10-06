    .text
	.globl	_sort
	.def	_sort;	.scl	2;	.type	32;	.endef
_sort:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	%esp, %eax
	movl	%eax, %ebx
	movl	$0, -12(%ebp)
	movl	12(%ebp), %eax
	leal	-1(%eax), %edx
	movl	%edx, -28(%ebp)
	sall	$2, %eax
	leal	3(%eax), %edx
	movl	$16, %eax
	subl	$1, %eax
	addl	%edx, %eax
	movl	$16, %ecx
	movl	$0, %edx
	divl	%ecx
	imull	$16, %eax, %eax
	call	___chkstk_ms
	subl	%eax, %esp
	movl	%esp, %eax
	addl	$3, %eax
	shrl	$2, %eax
	sall	$2, %eax
	movl	%eax, -32(%ebp)
	movl	$0, -16(%ebp)
	jmp	L12
L13:
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %ecx
	movl	-32(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%ecx, (%eax,%edx,4)
	addl	$1, -16(%ebp)
L12:
	movl	-16(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L13
	movl	$0, -20(%ebp)
	jmp	L14
L19:
	movl	12(%ebp), %eax
	subl	-20(%ebp), %eax
	leal	-1(%eax), %edx
	movl	-32(%ebp), %eax
	movl	(%eax,%edx,4), %eax
	movl	%eax, -36(%ebp)
	movl	$0, -24(%ebp)
	jmp	L15
L17:
	movl	-24(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-24(%ebp), %eax
	addl	$1, %eax
	leal	0(,%eax,4), %ecx
	movl	8(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jle	L16
	movl	-24(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -40(%ebp)
	movl	-24(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-24(%ebp), %eax
	addl	$1, %eax
	leal	0(,%eax,4), %ecx
	movl	8(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	%eax, (%edx)
	movl	-24(%ebp), %eax
	addl	$1, %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-40(%ebp), %eax
	movl	%eax, (%edx)
L16:
	addl	$1, -24(%ebp)
L15:
	movl	12(%ebp), %eax
	subl	-20(%ebp), %eax
	subl	$1, %eax
	cmpl	-24(%ebp), %eax
	jg	L17
	movl	12(%ebp), %eax
	subl	-20(%ebp), %eax
	addl	$1073741823, %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	cmpl	-36(%ebp), %eax
	je	L18
	addl	$1, -12(%ebp)
L18:
	addl	$1, -20(%ebp)
L14:
	movl	-20(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L19
	movl	-12(%ebp), %eax
	movl	%ebx, %esp
	movl	-4(%ebp), %ebx
	leave
	ret
