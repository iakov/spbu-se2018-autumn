	.file	"sort.c"
	.text
	.globl	_quickSort
	.def	_quickSort;	.scl	2;	.type	32;	.endef
_quickSort:
LFB14:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	12(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	jmp	L2
L5:
	subl	$1, 16(%ebp)
L3:
	movl	16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	cmpl	-20(%ebp), %eax
	jl	L4
	movl	12(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	L5
L4:
	movl	12(%ebp), %eax
	cmpl	16(%ebp), %eax
	je	L7
	movl	12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	16(%ebp), %eax
	leal	0(,%eax,4), %ecx
	movl	8(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	%eax, (%edx)
	addl	$1, 12(%ebp)
	jmp	L7
L9:
	addl	$1, 12(%ebp)
L7:
	movl	12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	cmpl	-20(%ebp), %eax
	jg	L8
	movl	12(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	L9
L8:
	movl	12(%ebp), %eax
	cmpl	16(%ebp), %eax
	je	L2
	movl	16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	12(%ebp), %eax
	leal	0(,%eax,4), %ecx
	movl	8(%ebp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	%eax, (%edx)
	subl	$1, 16(%ebp)
L2:
	movl	12(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	L3
	movl	12(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	%eax, (%edx)
	movl	12(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 16(%ebp)
	movl	12(%ebp), %eax
	cmpl	-20(%ebp), %eax
	jge	L11
	movl	-20(%ebp), %eax
	subl	$1, %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_quickSort
L11:
	movl	16(%ebp), %eax
	cmpl	-20(%ebp), %eax
	jle	L13
	movl	-20(%ebp), %eax
	leal	1(%eax), %edx
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edx, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_quickSort
L13:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE14:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
