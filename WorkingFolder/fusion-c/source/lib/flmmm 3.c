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
|  fLMMM
|  
*/


#include "../../header/vdp_graph2.h"


void	fLMMM( MMMtask *VDPtask ) __z88dk_fastcall  __naked
{
	VDPtask;

__asm

;****************************************************************
;  fLMMM (Fast high speed Logical move VRAM to VRAM)
;   for not simplest case, structure provided
;****************************************************************


    ; push ix
    ; ld ix,#0
    ; add ix,sp
    ; ld l,4(ix)
    ; ld h,5(ix)
    ; pop ix

      di
      call  _VDPready
      
      ld  a,#32
      out (#0x99),a
      ld  a,#128+#17
      out (#0x99),a ;R#17 := 32

      ld  bc,#0x0E9b  ; b=0x0E c=0x9b
                      ; b=6x2bytes + dummy + DI...
      otir            ; X,Y,X2,Y2,DX,DY,DIY,DIX

      ld  a,(hl)      ; Logical, operation
      bit #7,a
      jp  nz, lb_flq
      or  #0x90       ;LMMM command
    lb_flq:
      out (c),a       ; do it, VDP!

      ei
      ret

__endasm;

}