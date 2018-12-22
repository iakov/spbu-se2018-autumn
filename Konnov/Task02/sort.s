	.file	"sort01.c"
	.text
	.globl	_Sort
	.def	_Sort;	.scl	2;	.type	32;	.endef
_Sort:
LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$416, %esp
	movl	$0, -12(%ebp)
	movl	$0, -4(%ebp)
	jmp	L2
L3:
	movl	-4(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, -416(%ebp,%eax,4)
	addl	$1, -4(%ebp)
L2:
	movl	-4(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L3
	movl	$0, -4(%ebp)
	jmp	L4
L8:
	movl	12(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -8(%ebp)
	jmp	L5
L7:
	movl	-8(%ebp), %eax
	subl	$1, %eax
	movl	-416(%ebp,%eax,4), %edx
	movl	-8(%ebp), %eax
	movl	-416(%ebp,%eax,4), %eax
	cmpl	%eax, %edx
	jle	L6
	movl	-8(%ebp), %eax
	subl	$1, %eax
	movl	-416(%ebp,%eax,4), %eax
	movl	%eax, -16(%ebp)
	movl	-8(%ebp), %eax
	leal	-1(%eax), %edx
	movl	-8(%ebp), %eax
	movl	-416(%ebp,%eax,4), %eax
	movl	%eax, -416(%ebp,%edx,4)
	movl	-8(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, -416(%ebp,%eax,4)
L6:
	subl	$1, -8(%ebp)
L5:
	movl	-8(%ebp), %eax
	cmpl	-4(%ebp), %eax
	jg	L7
	addl	$1, -4(%ebp)
L4:
	movl	-4(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L8
	movl	$0, -4(%ebp)
	jmp	L9
L11:
	movl	-4(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-4(%ebp), %eax
	movl	-416(%ebp,%eax,4), %eax
	cmpl	%eax, %edx
	je	L10
	addl	$1, -12(%ebp)
L10:
	addl	$1, -4(%ebp)
L9:
	movl	-4(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L11
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE0:
	.ident	"GCC: (i686-win32-dwarf-rev0, Built by MinGW-W64 project) 8.1.0"
