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
|  HMMM
|  
*/


#include "../../header/vdp_graph2.h"


void	HMMM( unsigned int SX, unsigned int SY, unsigned int DX, unsigned int DY, unsigned int NX, unsigned int NY) __naked
{
	SX,SY,DX,DY,NX,NY;
__asm

ACPAGE = 0xFAF6
DPPAGE = 0xFAF5
FORCLR = #0xF3E9     ; foreground color
EXBRSA = 0xFAF8			 ; the slot of SUB-ROM (0 for MSX1)

;****************************************************************
;  HMMM (High speed move VRAM to VRAM)
;  copy a rectangle from 'source' VRAM to 'destination' VRAM
;  XS X coordinate of pixel source (left side)
;  YS Y coordinate of pixel source (upper side)
;  XD X coordinate of pixel destination (left side)
;  YD Y coordinate of pixel destination (upper side)
;  DX number of pixels to the right
;  DY number of pixels to the bottom
;****************************************************************


  push ix
  ld ix,#0
  add ix,sp

  di
  call    _VDPready
  ld    a,#32
  out    (#0x99),a
  ld    a,#128+#17
  out    (#0x99),a    ;R#17 := 32

  ld    c,#0x9b
  ld  a,4(ix)   ;
  out    (c),a    ; R32 X1 low byte
  ld  a,5(ix)   ;
  out    (c),a    ; R33 X1 high byte
  ld  a,6(ix)   ;
  out    (c),a    ; R34 Y1 low byte
  ld  a,7(ix)   ;
  out    (c),a    ; R35 Y1 high byte
  ld  a,8(ix)   ;
  out (c),a     ; R36 X2 low byte
  ld  a,9(ix)   ;
  out    (c),a    ; R37 X2 high byte
  ld  a,10(ix)  ;
  out    (c),a    ; R38 Y2 low byte
  ld  a,11(ix)  ;
  out    (c),a    ; R39 Y2 high byte
  ld  a,12(ix)  ;
  out    (c),a    ; R40 DX low byte
  ld  a,13(ix)  ;
  out    (c),a    ; R41 DX high byte
  ld  a,14(ix)  ;
  out    (c),a    ; R42 DY low byte
  ld  a,15(ix)  ;
  out    (c),a    ; R43 DY high byte
  xor a         ;
  out    (c),a    ; R44 dummy (color not used )
  out    (c),a    ; R45 DIX and DIY ! DX and DY express in incremental direction ! internal VRAM
          ; byte DIX,DIY=0, explained:
          ; The 0 copies the block starting from the upper left, the 1 from right/bottom.
          ; what s the difference? when copying overlapping source/destination
          ; (a scroller for example)
          ; when scrolling from right to left DIX/DIY can both be 0
          ;  but copying from left to right DIX must be 1. just figure it out...
          ; Then give coord.positive from right upper corner to left.

  ld a,#0b11010000  ;HMMM command
  out    (c),a    ;do it
  ei
  pop    ix
  ret



__endasm;
}