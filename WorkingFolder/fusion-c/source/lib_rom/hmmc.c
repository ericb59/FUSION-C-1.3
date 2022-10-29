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


void	HMMC( void *pixeldata, unsigned int DX, unsigned int DY, unsigned int NX, unsigned int NY) __naked
{
	pixeldata,DX,DY,NX,NY; 
__asm

;**************************************************************************************
; HMMC High speed move CPU RAM to VRAM                   Eric
;
; HMMC (void *pixeldatas, unsigned int DX, unsigned int DY, unsigned int NX, unsigned int NY)
; 
; 
;**************************************************************************************

        push ix 
        ld ix,#0
        add ix,sp

        ld  l,4(ix)   ; Load *buffer PixelData address
        ld  h,5(ix)  
        di 

        call  _VDPready

        ld     a,#36
        out    (#0x99),a
        ld     a,#128+#17
        out    (#0x99),a    ;R#17 := 36

        ld     c,#0x9b
        ld     a,6(ix)  ;
        out    (c),a    ; R36 DX low byte
        ld     a,7(ix)  ;
        out    (c),a    ; R37 DX high byte
        ld     a,8(ix)  ;
        out    (c),a    ; R38 DY low byte
        ld     a,9(ix)  ;
        out    (c),a    ; R39 DY high byte
        ld      a,10(ix)    ;
        out    (c),a    ; R40 NX low byte
        ld      a,11(ix)    ;
        out    (c),a    ; R41 NX high byte
        ld      a,12(ix)    ;
        out    (c),a    ; R42 NY low byte
        ld      a,13(ix)    ;
        out    (c),a    ; R43 NY high byte     

        
        ld a,(hl)       ; data adress to register 44
        out    (c),a    ; R44 
        xor a
        out    (c),a    ; R45 Parameters  DIX=DIY=VRAM expansion0 
        ld  a,#0b11110000
        out (c),a       ; R46 command to do it

        ld  a,#128+#44
        out (#0x99),a
        ld  a,#128+#17
        out (#0x99),a       ; VDP(17)<=44


         ld  a,#2           ; Read Status Register #2
         out (#0x99),a
         ld  a,#0x8f
         out (#0x99),a
         inc hl
   loopHMMC:
       
         in  a,(#0x99)

         rra
         jp nc, exitHMMC    ; is CE finish ?

         outi

         jp loopHMMC

  exitHMMC:
        xor a
        
        out (#0x99),a
        ld  a,#0x8f
        ei
        out (#0x99),a
        
        pop ix
        ret


__endasm;
}