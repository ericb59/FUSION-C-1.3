/*
 ___________________________________________________________
/               __           _                              \
|              / _|         (_)                             |
|             | |_ _   _ ___ _  ___  _ __                   |
|             |  _| | | / __| |/ _ \| '_ \                  |
|             | | | |_| \__ \ | (_) | | | |                 |
|             |_|  \__,_|___/_|\___/|_| |_| *               |
|                                                           |
|               The MSX C Library for SDCC                  |
|                     V1.3 - 04 2020                        |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|                                                           |
\___________________________________________________________/
*/ 
/*    2019-2020 Eric Boez
|
|  Point
|  
*/


#include "../../header/vdp_graph2.h"


char	Point( unsigned int X,  unsigned int Y ) __naked
{
	X,Y;
__asm

ACPAGE = 0xFAF6
DPPAGE = 0xFAF5
FORCLR = #0xF3E9         ; foreground color
EXBRSA = 0xFAF8			 ; the slot of SUB-ROM (0 for MSX1)

;****************************************************************
;	POINT gets pixel 										Eric
;		 Point ( unsigned int x, unsigned  int y ) 
;****************************************************************


		  push ix
		  ld ix,#0
		  add ix,sp
  
		  di
		  call  _VDPready
		  ld    a,#32
		  out   (#0x99),a
		  ld    a,#128+#17
		  out   (#0x99),a    ;R#17 := 32

		  ld   c,#0x9b

		  ld  a,4(ix)  ;
		  out  (c),a   ; R32 DX low byte

		  ld  a,5(ix)  ;
		  out (c),a    ; R33 DX high byte

		  ld  a,6(ix)  ;
		  out (c),a    ; R34 DY low byte

		  ld  a,7(ix)  ;
		  out (c),a    ; R35 DY high byte

		  out (#0x99),a
		  ld  a,#128+#45
		  out (#0x99),a
		  
		  ld  a,#0b01000000
		  out (#0x99),a
		  ld  a,#128+#46
		  out (#0x99),a

		  call  _VDPready

		  ld  a,#7     
		  out (#0x99),a
		  ld  a,#0x8f
		  out (#0x99),a
		  in  a,(#0x99)
		  ld l,a
		  ld h,#0

		  xor a
		  out (#0x99),a
		  ld  a,#0x8f
		  out (#0x99),a
		  ei
		  pop ix
		  ret


__endasm;
}