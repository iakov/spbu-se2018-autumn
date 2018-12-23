	.file	"_sort.c"
	.text
	.globl	_sort
	.def	_sort;	.scl	2;	.type	32;	.endef
_sort:
LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$432, %esp
	.cfi_offset 3, -12
	movl	$0, -8(%ebp)
	jmp	L2
L3:
	movl	-8(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-8(%ebp), %eax
	movl	%edx, -424(%ebp,%eax,4)
	addl	$1, -8(%ebp)
L2:
	movl	-8(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L3
	movl	12(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -12(%ebp)
	jmp	L4
L8:
	movl	-12(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	L5
L7:
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-12(%ebp), %eax
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
	movl	-16(%ebp), %edx
	leal	0(,%edx,4), %ecx
	movl	8(%ebp), %edx
	addl	%ecx, %edx
	movl	(%edx), %ecx
	movl	-12(%ebp), %edx
	leal	0(,%edx,4), %ebx
	movl	8(%ebp), %edx
	addl	%ebx, %edx
	movl	(%edx), %edx
	xorl	%ecx, %edx
	movl	%edx, (%eax)
	movl	-12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	-12(%ebp), %edx
	leal	0(,%edx,4), %ecx
	movl	8(%ebp), %edx
	addl	%ecx, %edx
	movl	(%edx), %ecx
	movl	-16(%ebp), %edx
	leal	0(,%edx,4), %ebx
	movl	8(%ebp), %edx
	addl	%ebx, %edx
	movl	(%edx), %edx
	xorl	%ecx, %edx
	movl	%edx, (%eax)
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	-16(%ebp), %edx
	leal	0(,%edx,4), %ecx
	movl	8(%ebp), %edx
	addl	%ecx, %edx
	movl	(%edx), %ecx
	movl	-12(%ebp), %edx
	leal	0(,%edx,4), %ebx
	movl	8(%ebp), %edx
	addl	%ebx, %edx
	movl	(%edx), %edx
	xorl	%ecx, %edx
	movl	%edx, (%eax)
L6:
	subl	$1, -16(%ebp)
L5:
	cmpl	$0, -16(%ebp)
	jns	L7
	subl	$1, -12(%ebp)
L4:
	cmpl	$0, -12(%ebp)
	jg	L8
	movl	$0, -20(%ebp)
	movl	$0, -24(%ebp)
	jmp	L9
L11:
	movl	-24(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-24(%ebp), %eax
	movl	-424(%ebp,%eax,4), %eax
	cmpl	%eax, %edx
	je	L10
	addl	$1, -20(%ebp)
L10:
	addl	$1, -24(%ebp)
L9:
	movl	-24(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L11
	movl	-20(%ebp), %eax
	addl	$432, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE0:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
