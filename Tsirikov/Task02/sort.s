	.file	"sort.c"
	.text
	.globl	__sort
	.type	__sort, @function
__sort:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$464, %rsp
	movl	%edi, -452(%rbp)
	movq	%rsi, -464(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -436(%rbp)
	jmp	.L2
.L3:
	movl	-436(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-464(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-436(%rbp), %eax
	cltq
	movl	%edx, -416(%rbp,%rax,4)
	addl	$1, -436(%rbp)
.L2:
	movl	-436(%rbp), %eax
	cmpl	-452(%rbp), %eax
	jl	.L3
	movl	$0, -432(%rbp)
	jmp	.L4
.L8:
	movl	$0, -428(%rbp)
	jmp	.L5
.L7:
	movl	-428(%rbp), %eax
	cltq
	movl	-416(%rbp,%rax,4), %edx
	movl	-428(%rbp), %eax
	addl	$1, %eax
	cltq
	movl	-416(%rbp,%rax,4), %eax
	cmpl	%eax, %edx
	jle	.L6
	movl	-428(%rbp), %eax
	cltq
	movl	-416(%rbp,%rax,4), %edx
	movl	-428(%rbp), %eax
	addl	$1, %eax
	cltq
	movl	-416(%rbp,%rax,4), %eax
	xorl	%eax, %edx
	movl	-428(%rbp), %eax
	cltq
	movl	%edx, -416(%rbp,%rax,4)
	movl	-428(%rbp), %eax
	addl	$1, %eax
	cltq
	movl	-416(%rbp,%rax,4), %edx
	movl	-428(%rbp), %eax
	cltq
	movl	-416(%rbp,%rax,4), %eax
	movl	-428(%rbp), %ecx
	addl	$1, %ecx
	xorl	%eax, %edx
	movslq	%ecx, %rax
	movl	%edx, -416(%rbp,%rax,4)
	movl	-428(%rbp), %eax
	cltq
	movl	-416(%rbp,%rax,4), %edx
	movl	-428(%rbp), %eax
	addl	$1, %eax
	cltq
	movl	-416(%rbp,%rax,4), %eax
	xorl	%eax, %edx
	movl	-428(%rbp), %eax
	cltq
	movl	%edx, -416(%rbp,%rax,4)
.L6:
	addl	$1, -428(%rbp)
.L5:
	movl	-452(%rbp), %eax
	subl	$1, %eax
	cmpl	%eax, -428(%rbp)
	jl	.L7
	addl	$1, -432(%rbp)
.L4:
	movl	-452(%rbp), %eax
	subl	$1, %eax
	cmpl	%eax, -432(%rbp)
	jl	.L8
	movl	$0, -424(%rbp)
	movl	$0, -420(%rbp)
	jmp	.L9
.L11:
	movl	-420(%rbp), %eax
	cltq
	movl	-416(%rbp,%rax,4), %edx
	movl	-420(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	-464(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	je	.L10
	addl	$1, -424(%rbp)
.L10:
	addl	$1, -420(%rbp)
.L9:
	movl	-420(%rbp), %eax
	cmpl	-452(%rbp), %eax
	jl	.L11
	movl	-424(%rbp), %eax
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L13
	call	__stack_chk_fail@PLT
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	__sort, .-__sort
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
