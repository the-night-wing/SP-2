	include C:\masm32\include\kernel32.inc
	include C:\masm32\include\user32.inc

	includelib C:\masm32\lib\kernel32.lib
	includelib C:\masm32\lib\user32.lib
	.model small
	.code
main:
LFB0:
	push	ebp
	mov	ebp, esp
	and	esp, -16
	call main
	fld	DWORD PTR LC0
	fstp	DWORD PTR a
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
	ret
LFE0:
LC0:
	.long	1085485875
LC1:
	.long	1083388723
LC2:
	.long	1080452710
LC3:
	.long	1082759578
end main