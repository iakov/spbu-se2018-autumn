	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14
	.globl	_sort                   ## -- Begin function sort
	.p2align	4, 0x90
_sort:                                  ## @sort
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movl	$0, -24(%rbp)
LBB0_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_4 Depth 2
	movl	-24(%rbp), %eax
	movl	-20(%rbp), %ecx
	subl	$1, %ecx
	cmpl	%ecx, %eax
	jge	LBB0_14
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rax
	movslq	-24(%rbp), %rcx
	cmpl	$-1, (%rax,%rcx,4)
	je	LBB0_12
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
LBB0_4:                                 ##   Parent Loop BB0_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movl	-28(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB0_11
## %bb.5:                               ##   in Loop: Header=BB0_4 Depth=2
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	cmpl	$-1, (%rax,%rcx,4)
	je	LBB0_9
## %bb.6:                               ##   in Loop: Header=BB0_4 Depth=2
	movq	-8(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movl	(%rax,%rcx,4), %edx
	movq	-8(%rbp), %rax
	movslq	-24(%rbp), %rcx
	cmpl	(%rax,%rcx,4), %edx
	jg	LBB0_8
## %bb.7:                               ##   in Loop: Header=BB0_4 Depth=2
	movq	-8(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movl	(%rax,%rcx,4), %edx
	movl	%edx, -32(%rbp)
	movq	-8(%rbp), %rax
	movslq	-24(%rbp), %rcx
	movl	(%rax,%rcx,4), %edx
	movq	-8(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movl	%edx, (%rax,%rcx,4)
	movl	-32(%rbp), %edx
	movq	-8(%rbp), %rax
	movslq	-24(%rbp), %rcx
	movl	%edx, (%rax,%rcx,4)
LBB0_8:                                 ##   in Loop: Header=BB0_4 Depth=2
	jmp	LBB0_9
LBB0_9:                                 ##   in Loop: Header=BB0_4 Depth=2
	jmp	LBB0_10
LBB0_10:                                ##   in Loop: Header=BB0_4 Depth=2
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	LBB0_4
LBB0_11:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_12
LBB0_12:                                ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_13
LBB0_13:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
	jmp	LBB0_1
LBB0_14:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
