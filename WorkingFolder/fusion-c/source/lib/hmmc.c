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
|  HMMC
|  
*/


#include "../../header/vdp_graph2.h"


void	HMMC( void *pixeldata, int DX, int DY, int NX, int NY) __naked
{
	pixeldata,DX,DY,NX,NY;
__asm




;**************************************************************************************
; HMMC (High speed move CPU RAM to VRAM                   Eric
;
; HMMC (void *pixeldatas, int DX, int DY, int NX, int NY, char OP )
; 
; 
;**************************************************************************************

        push ix 
        ld ix,#0
        add ix,sp

        ld  l,4(ix)   ; Load *buffer PixelData address
        ld  h,5(ix)  
        ld  d,14(ix)
        di 

        call  _VDPready

        ld     a,#36
        out    (#0x99),a
        ld     a,#128+#17
        out    (#0x99),a    ;R#17 := 32

        ld     c,#0x9b
        ld     a,6(ix)  ;
        out    (c),a    ; R36 XS low byte
        ld     a,7(ix)  ;
        out    (c),a    ; R37 XS high byte
        ld     a,8(ix)  ;
        out    (c),a    ; R38 YS low byte
        ld     a,9(ix)  ;
        out    (c),a    ; R39 YS high byte
        ld  a,10(ix)    ;
        out    (c),a    ; R40 DX low byte
        ld  a,11(ix)    ;
        out    (c),a    ; R41 DX high byte
        ld  a,12(ix)    ;
        out    (c),a    ; R42 DY low byte
        ld  a,13(ix)    ;
        out    (c),a    ; R43 DY high byte     

        
        ld a,(hl)       ; First Color data to register 44
        out    (c),a    ; R44 
        xor a
        out    (c),a    ; R45 Parameters  DIX=DIY=0 
        ld  a,#0b11110000
        out (c),a       ; R46 command to do it

        ld  a,#128+#44
        out (#0x99),a
        ld  a,#128+#17
        out (#0x99),a       ; VDP(17)<=44
   loopHMMC:
         ld  a,#2
         out (#0x99),a
         ld  a,#0x8f
         out (#0x99),a
         in  a,(#0x99)
         
         and #1
         jp z, exitHMMC       ; if CE = 1 Exit
         and #128
         jp nz, loopHMMC      ; if TR = 0 Loop
         inc hl 
         ld a,(hl)
         out  (#0x9b),a
         jp loopHMMC

  exitHMMC:
        xor a
        
        out (#0x99),a
        ld  a,#0x8f
        out (#0x99),a
        in  a,(#0x99)

        ei
        pop ix
        ret

__endasm;
}