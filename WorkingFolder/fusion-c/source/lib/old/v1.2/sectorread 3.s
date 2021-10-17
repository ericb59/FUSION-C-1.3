; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                     V1.1 -  03-2019                       |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
;
;	 
;	Definitions for dealing with MEdia Sectors
;
;	Eric Boez 2019
;
;
;	SectorRead
;	SectorWrite
;	SetDiskTrAddress
;
;
	.area _CODE

;--- proc 	SectorRead
;
;	unsigned char SectorRead(unsigned int SectorStart, unsigned char drive, unsigned char NbSectors);
;
_SectorRead::
	push	ix
	ld ix,#0
	add ix,sp
	ld	e,4(ix)
	ld	d,5(ix)
	ld l,6(ix)
	ld h,7(ix)
	ld	c,#0x2F
	call	#5
	ld h,#0
	ld l,a
	pop	ix
	ret

;--- end of proc 


;--- proc 	SectorWrite
;
;	unsigned  char SectorWrite(unsigned int SectorStart, unsigned char drive, unsigned char NbSectors);
;
_SectorWrite::
	push	ix
	ld ix,#0
	add ix,sp
	ld	e,4(ix)
	ld	d,5(ix)
	ld l,6(ix)
	ld h,7(ix)
	ld	c,#0x30
	call	#5
	ld h,#0
	ld l,a
	pop	ix
	ret

;--- end of proc 


;--- proc 	SetDiskTrAddress
;
;	void	SetDiskTrAddress(int adress)
;
_SetDiskTrAddress::
	push	ix
	ld ix,#0
	add ix,sp
	ld	e,4(ix)
	ld	d,5(ix)
	ld	c,#0x1A
	call	#5
	pop	ix
	ret

;--- end of proc 