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
	subq	$336, %rsp                      # imm = 0x150
	movl	$0, -4(%rbp)
	movl	-336(%rbp), %esi
	movl	%esi, -68(%rbp)
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf@PLT
	movl	$1, %eax
	addq	$336, %rsp                      # imm = 0x150
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d"
	.size	.L.str, 3

	.ident	"clang version 17.0.6"
	.section	".note.GNU-stack","",@progbits
