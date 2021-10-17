; LDIRVM (unsigned int SRC_RAMAddr, Unsigned int Dest_VRAMAddr, unsigned int Length)
_LDIRVM::
	push ix
	ld ix,#0
	add ix,sp
	ld l,4(ix)
	ld h,5(ix)

	ld e,6(ix)
	ld d,7(ix)

	ld c,8(ix)
	ld b,9(ix)
	pop ix
	call #0x005c

	ret