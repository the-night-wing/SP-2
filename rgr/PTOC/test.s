	.file	"ccMzeaaa.i"
	.intel_syntax noprefix
	.comm	_b, 4, 2
	.comm	_a, 12, 2
	.comm	_n, 4, 2
	.comm	_d, 4, 2
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB0:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	and	esp, -16
	call	___main
	fld	DWORD PTR LC0
	fstp	DWORD PTR _a
	fld	DWORD PTR LC1
	fstp	DWORD PTR _a+4
	fld	DWORD PTR LC2
	fstp	DWORD PTR _a+8
	fld	DWORD PTR LC3
	fstp	DWORD PTR _b
	mov	DWORD PTR _n, 1
	mov	DWORD PTR _d, 5
	fld	DWORD PTR _a
	fld	DWORD PTR _a+4
	faddp	st(1), st
	fstp	DWORD PTR _b
	mov	eax, 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE0:
	.section .rdata,"dr"
	.align 4
LC0:
	.long	1085485875
	.align 4
LC1:
	.long	1083388723
	.align 4
LC2:
	.long	1080452710
	.align 4
LC3:
	.long	1082759578
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
