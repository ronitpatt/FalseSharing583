	.text
	.file	"test.cpp"
	.globl	_Z4workPv                       # -- Begin function _Z4workPv
	.p2align	4, 0x90
	.type	_Z4workPv,@function
_Z4workPv:                              # @_Z4workPv
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movl	$0, -4(%rbp)
	.p2align	4, 0x90
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	movl	-4(%rbp), %eax
	cmpl	elements_per_thread(%rip), %eax
	jge	.LBB0_3
# %bb.2:                                #   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
	incl	(%rax)
	incl	-4(%rbp)
	jmp	.LBB0_1
.LBB0_3:
	ud2
.Lfunc_end0:
	.size	_Z4workPv, .Lfunc_end0-_Z4workPv
	.cfi_endproc
                                        # -- End function
	.globl	_Z5work2Pv                      # -- Begin function _Z5work2Pv
	.p2align	4, 0x90
	.type	_Z5work2Pv,@function
_Z5work2Pv:                             # @_Z5work2Pv
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movl	$0, -4(%rbp)
	.p2align	4, 0x90
.LBB1_1:                                # =>This Inner Loop Header: Depth=1
	movl	-4(%rbp), %eax
	cmpl	elements_per_thread(%rip), %eax
	jge	.LBB1_3
# %bb.2:                                #   in Loop: Header=BB1_1 Depth=1
	movq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
	incl	64(%rax)
	incl	-4(%rbp)
	jmp	.LBB1_1
.LBB1_3:
	ud2
.Lfunc_end1:
	.size	_Z5work2Pv, .Lfunc_end1-_Z5work2Pv
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	andq	$-64, %rsp
	subq	$256, %rsp                      # imm = 0x100
	.cfi_offset %rbx, -24
	movl	$0, 60(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 128(%rsp)
	leaq	48(%rsp), %rdi
	leaq	64(%rsp), %rbx
	movl	$_Z4workPv, %edx
	xorl	%esi, %esi
	movq	%rbx, %rcx
	callq	pthread_create@PLT
	leaq	40(%rsp), %rdi
	movl	$_Z5work2Pv, %edx
	xorl	%esi, %esi
	movq	%rbx, %rcx
	callq	pthread_create@PLT
	movq	48(%rsp), %rdi
	xorl	%esi, %esi
	callq	pthread_join@PLT
	movq	40(%rsp), %rdi
	xorl	%esi, %esi
	callq	pthread_join@PLT
	movl	64(%rsp), %esi
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	movl	128(%rsp), %esi
	movl	$.L.str.1, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	leaq	-8(%rbp), %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
                                        # -- End function
	.type	elements_per_thread,@object     # @elements_per_thread
	.data
	.globl	elements_per_thread
	.p2align	2, 0x0
elements_per_thread:
	.long	1000000                         # 0xf4240
	.size	elements_per_thread, 4

	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"front: %d\n"
	.size	.L.str, 11

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"back: %d\n"
	.size	.L.str.1, 10

	.ident	"clang version 17.0.6"
	.section	".note.GNU-stack","",@progbits
