	.file	"sort.c"
	.text
	.globl	_bubblesort
	.def	_bubblesort;	.scl	2;	.type	32;	.endef
_bubblesort:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -4(%ebp)
	jmp	L2
L6:
	movl	$0, -8(%ebp)
	jmp	L3
L5:
	movl	-8(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-8(%ebp), %eax
	addl	$1, %eax
	leal	0(,%eax,4), %ecx
	movl	8(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jle	L4
	movl	-8(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -12(%ebp)
	movl	-8(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-8(%ebp), %eax
	addl	$1, %eax
	leal	0(,%eax,4), %ecx
	movl	8(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	%eax, (%edx)
	movl	-8(%ebp), %eax
	addl	$1, %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%eax, (%edx)
L4:
	addl	$1, -8(%ebp)
L3:
	movl	12(%ebp), %eax
	subl	-4(%ebp), %eax
	subl	$1, %eax
	cmpl	-8(%ebp), %eax
	jg	L5
	addl	$1, -4(%ebp)
L2:
	movl	12(%ebp), %eax
	subl	$1, %eax
	cmpl	-4(%ebp), %eax
	jg	L6
	nop
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
