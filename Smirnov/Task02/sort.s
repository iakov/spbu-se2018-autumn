	.text
	.globl	_sort
	.def	_sort;	.scl	2;	.type	32;	.endef
_sort:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$432, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)
	jmp	L2
L3:
	movl	-8(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-8(%ebp), %eax
	movl	%edx, -420(%ebp,%eax,4)
	addl	$1, -8(%ebp)
L2:
	movl	-8(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L3
	movl	$0, -12(%ebp)
	jmp	L4
L9:
	movl	$0, -16(%ebp)
	jmp	L5
L7:
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-16(%ebp), %eax
	addl	$1, %eax
	leal	0(,%eax,4), %ecx
	movl	8(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jle	L6
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-16(%ebp), %eax
	addl	$1, %eax
	leal	0(,%eax,4), %ecx
	movl	8(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	%eax, (%edx)
	movl	-16(%ebp), %eax
	addl	$1, %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	%eax, (%edx)
L6:
	addl	$1, -16(%ebp)
L5:
	movl	12(%ebp), %eax
	subl	-12(%ebp), %eax
	subl	$1, %eax
	cmpl	-16(%ebp), %eax
	jg	L7
	movl	12(%ebp), %eax
	subl	-12(%ebp), %eax
	addl	$1073741823, %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	12(%ebp), %eax
	subl	-12(%ebp), %eax
	subl	$1, %eax
	movl	-420(%ebp,%eax,4), %eax
	cmpl	%eax, %edx
	je	L8
	addl	$1, -4(%ebp)
L8:
	addl	$1, -12(%ebp)
L4:
	movl	-12(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L9
	movl	-4(%ebp), %eax
	leave
	ret
