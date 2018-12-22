.globl sort
sort:
.LFB38:
	.cfi_startproc
	movl	p(%rip), %r11d
	cmpl	$1, %r11d
	jle	.L8
	xorl	%r9d, %r9d
	movl	$1, %r10d
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L7:
	movl	numbers+4(,%r9,4), %r8d
	movl	numbers(,%r9,4), %edx
	movl	%r9d, %edi
	cmpl	%edx, %r8d
	jge	.L3
	addl	$1, %eax
	testl	%r10d, %r10d
	movb	$1, changed+1(%r9)
	jle	.L3
	leal	1(%r9), %esi
	movslq	%r9d, %rcx
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L15:
	cmpl	%r8d, %edx
	jle	.L3
.L5:
	cmpb	$0, changed(%rcx)
	jne	.L4
	addl	$1, %eax
	movb	$1, changed(%rcx)
.L4:
	xorl	%r8d, %edx
	movslq	%esi, %rsi
	subl	$1, %edi
	movl	%edx, numbers(,%rcx,4)
	xorl	numbers(,%rsi,4), %edx
	movl	%edx, numbers(,%rsi,4)
	xorl	numbers(,%rcx,4), %edx
	leal	1(%rdi), %esi
	testl	%esi, %esi
	movl	%edx, numbers(,%rcx,4)
	movslq	%edi, %rcx
	movl	%edx, %r8d
	movl	numbers(,%rcx,4), %edx
	jg	.L15
	.p2align 4,,10
	.p2align 3
.L3:
	addl	$1, %r10d
	addq	$1, %r9
	cmpl	%r11d, %r10d
	jne	.L7
	rep ret
.L8:
	xorl	%eax, %eax
	ret
	.cfi_endproc
