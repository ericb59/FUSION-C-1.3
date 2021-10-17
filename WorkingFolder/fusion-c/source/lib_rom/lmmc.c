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
|  LMMC
|  
*/


#include "../../header/vdp_graph2.h"


void	LMMC( void *pixeldata, unsigned int DX, unsigned int DY, unsigned int NX, unsigned int NY, char OP ) __naked
{
	pixeldata,DX,DY,NX,NY,OP;
__asm

ACPAGE = 0xFAF6
DPPAGE = 0xFAF5
FORCLR = #0xF3E9     ; foreground color
EXBRSA = 0xFAF8			 ; the slot of SUB-ROM (0 for MSX1)


;**************************************************************************************
; LMMC Logical move  CPU RAM to VRAM                   Eric
;
; LMMC (void *pixeldatas, unsigned int XS, unsigned int YS, unsigned int DX, unsigned int DY, char OP )
; 
; 
;**************************************************************************************


    push ix 
        ld ix,#0
        add ix,sp

        ld  l,4(ix)   ;  Load *buffer PixelData address
        ld  h,5(ix)  
        di 

        call    _VDPready
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

        ld a,14(ix)     ; OP
        and #0x0f
        or #0b10110000
        out (c),a       ; R46 command to do it

        ld  a,#128+#44
        out (#0x99),a
        ld  a,#128+#17
        out (#0x99),a       ; VDP(17)<=44
   loopLMMC:
         ld  a,#2
         call  statusLMMC
         
         rra
         jp nc, exitLMMC    ; is CE finish ?
         rla
         rla
         jp nc, loopLMMC    ; TR? transferring?
         inc hl 
         ld a,(hl)
         out  (#0x9b),a
         jp loopLMMC
  exitLMMC:
        xor a
        call  statusLMMC
        ei
        pop ix
        ret
  statusLMMC:
        out (#0x99),a
        ld  a,#0x8f
        out (#0x99),a
        in  a,(#0x99)
        ret


__endasm;
}