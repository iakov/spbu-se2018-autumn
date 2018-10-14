	.file	"sort.c"
	.text
	.globl	Sort
	.def	Sort;	.scl	2;	.type	32;	.endef
	.seh_proc	Sort
Sort:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r12
	.seh_pushreg	%r12
	subq	$56, %rsp
	.seh_stackalloc	56
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movq	%rcx, -48(%rbp)
	movl	%edx, -40(%rbp)
	movq	%rsp, %rax
	movq	%rax, %r8
	movl	-40(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -104(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %r11
	movl	$0, %r12d
	movslq	%eax, %rdx
	movq	%rdx, %r9
	movl	$0, %r10d
	cltq
	salq	$2, %rax
	addq	$15, %rax
	shrq	$4, %rax
	salq	$4, %rax
	call	___chkstk_ms
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -112(%rbp)
	movl	$0, -92(%rbp)
	jmp	.L2
.L3:
	movl	-92(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movq	-112(%rbp), %rdx
	movl	-92(%rbp), %eax
	cltq
	movl	%ecx, (%rdx,%rax,4)
	addl	$1, -92(%rbp)
.L2:
	movl	-92(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jl	.L3
	movl	$0, -92(%rbp)
	jmp	.L4
.L8:
	movl	$0, -88(%rbp)
	jmp	.L5
.L7:
	movl	-88(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-88(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rcx
	movq	-48(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jle	.L6
	movl	-88(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -116(%rbp)
	movl	-88(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	-48(%rbp), %rax
	addq	%rax, %rdx
	movl	-88(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	-48(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rdx), %edx
	movl	%edx, (%rax)
	movl	-88(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movl	-116(%rbp), %edx
	movl	%edx, (%rax)
.L6:
	addl	$1, -88(%rbp)
.L5:
	movl	-40(%rbp), %eax
	subl	-92(%rbp), %eax
	subl	$1, %eax
	cmpl	%eax, -88(%rbp)
	jl	.L7
	addl	$1, -92(%rbp)
.L4:
	movl	-40(%rbp), %eax
	subl	$1, %eax
	cmpl	%eax, -92(%rbp)
	jl	.L8
	movl	$0, -92(%rbp)
	jmp	.L9
.L11:
	movl	-92(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movq	-112(%rbp), %rdx
	movl	-92(%rbp), %eax
	cltq
	movl	(%rdx,%rax,4), %eax
	cmpl	%eax, %ecx
	je	.L10
	addl	$1, -84(%rbp)
.L10:
	addl	$1, -92(%rbp)
.L9:
	movl	-92(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jl	.L11
	movl	-84(%rbp), %eax
	movq	%r8, %rsp
	leaq	-72(%rbp), %rsp
	popq	%r12
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
