proc main:
	push	ebp
	mov	ebp, esp

	and	esp, -16
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


LC0:
	dword	1085485875
LC1:
	dword	1083388723
LC2:
	dword	1080452710
LC3:
	dword	1082759578

endp main
end