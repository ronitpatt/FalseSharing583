	.text
	.file	"test.cpp"
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
	subq	$32, %rsp
	movl	$0, -20(%rbp)
	movl	$1, transposed(%rip)
	movl	$2, transposed+12(%rip)
	movl	$3, transposed+24(%rip)
	movl	$4, transposed+36(%rip)
	movl	$5, transposed+48(%rip)
	movl	$.L.str, %edi
	movl	$transposed, %esi
	movl	$transposed+4, %edx
	movl	$transposed+32, %ecx
	xorl	%eax, %eax
	callq	printf@PLT
	movq	$transposed, -16(%rbp)
	movl	$0, -4(%rbp)
	cmpl	$3, -4(%rbp)
	jg	.LBB0_3
	.p2align	4, 0x90
.LBB0_2:                                # =>This Inner Loop Header: Depth=1
	movq	-16(%rbp), %rax
	movl	(%rax), %esi
	movl	4(%rax), %edx
	movl	8(%rax), %ecx
	movl	$.L.str.1, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	addq	$12, -16(%rbp)
	incl	-4(%rbp)
	cmpl	$3, -4(%rbp)
	jle	.LBB0_2
.LBB0_3:
	movl	$1, %eax
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	obj,@object                     # @obj
	.bss
	.globl	obj
	.p2align	2, 0x0
obj:
	.zero	48
	.size	obj, 48

	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%p %p %p\n"
	.size	.L.str, 10

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"%d %d %d \n"
	.size	.L.str.1, 11

	.type	transposed,@object              # @transposed
	.local	transposed
	.comm	transposed,48,16
	.ident	"clang version 17.0.6"
	.section	".note.GNU-stack","",@progbits
