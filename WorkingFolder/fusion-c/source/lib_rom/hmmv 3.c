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
|  HMMV
|  
*/


#include "../../header/vdp_graph2.h"


void	HMMV( unsigned int DX, unsigned int DY, unsigned int NX, unsigned int NY, char COL) __naked
{
	DX,DY,NX,NY,COL;
__asm

ACPAGE = 0xFAF6
DPPAGE = 0xFAF5
FORCLR = #0xF3E9     ; foreground color
EXBRSA = 0xFAF8			 ; the slot of SUB-ROM (0 for MSX1)


;****************************************************************
; HMMV painting the rectangle in high speed          Eric
; void  HMMV( unsigned int XS, unsigned int YS, unsigned int DX, unsigned int DY, char COL);
; 
;****************************************************************

  push ix
  ld ix,#0
  add ix,sp

  di
  call    _VDPready
  ld    a,#36
  out    (#0x99),a
  ld    a,#128+#17
  out    (#0x99),a    ;R#17 := 36

  ld    c,#0x9b
  ld  a,4(ix)  ;
  out    (c),a    ; R36 DX low byte

  ld  a,5(ix)  ;
  out    (c),a    ; R37 DX high byte

  ld  a,6(ix)  ;
  out    (c),a    ; R38 DY low byte

  ld  a,7(ix)  ;
  out    (c),a    ; R39 DY high byte

  ld  a,8(ix)  ;
  out (c),a     ; R40 NX low byte

  ld  a,9(ix)  ;
  out    (c),a    ; R41 NX high byte

  ld  a,10(ix) ;
  out    (c),a    ; R42 NY low byte

  ld  a,11(ix) ;
  out    (c),a    ; R43 NY high byte

  ld  a,12(ix) ;

  out    (c),a     ; R44 COL low byte

  xor a        ;

  out    (c),a     ; R45 DIX and DIY ! DX and DY express in incremental direction ! internal VRAM

  or    #0b11000000   ;HMMV command

  out    (c),a    ;do it
  ei
  pop    ix
  ret

__endasm;
}