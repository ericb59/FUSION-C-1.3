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
|  LMCM5
|  
*/


#include "../../header/vdp_graph2.h"


void	LMCM5( void *buffer, unsigned int XS, unsigned int YS, unsigned int NX, unsigned int NY, char OP) __naked
{
	buffer,XS,YS,NX,NY,OP;
__asm

ACPAGE = 0xFAF6
DPPAGE = 0xFAF5
FORCLR = #0xF3E9         ; foreground color
EXBRSA = 0xFAF8			 ; the slot of SUB-ROM (0 for MSX1)

;**************************************************************************************
; LMCM5 (Logical move to CPU memory)						         	Eric
;
; LMCM5( void *buffer, unsigned int XS, unsigned int YS, unsigned int DX, unsigned int DY, char OP)
; This function works with Screen Mode 5 & 7
; Logicap operator : Only 0 and 8 are available
;**************************************************************************************


        push ix 
        ld ix,#0
        add ix,sp

        ld  l,4(ix)  
        ld  h,5(ix)  
        ld  d,14(ix)
        di 

        call    _VDPready
        ld     a,#32
        out    (#0x99),a
        ld     a,#128+#17
        out    (#0x99),a    ;R#17 := 32

        ld     c,#0x9b
        ld     a,6(ix)  ;
        out    (c),a    ; R32 XS low byte
        ld     a,7(ix)  ;
        out    (c),a    ; R33 XS high byte
        ld     a,8(ix)  ;
        out    (c),a    ; R34 YS low byte
        ld     a,9(ix)  ;
        out    (c),a    ; R35 YS high byte

        out (c),a   	;R36 dummy
        out (c),a   	;R37 dummy
        out (c),a   	;R38 dummy
        out (c),a   	;R39 dummy

        ld  a,10(ix)    ;
        out    (c),a    ; R40 DX low byte
        ld  a,11(ix)    ;
        out    (c),a    ; R41 DX high byte
        ld  a,12(ix)    ;
        out    (c),a    ; R42 DX low byte
        ld  a,13(ix)    ;
        out    (c),a    ; R43 DX high byte     

        out    (c),a    ; R44 Dummy
        xor a
        out    (c),a    ; R45 Parameters DIX and DIY in incremental direction with internal internal VRAM

        ld  a,#7        ;clear TR status
        
        out (#0x99),a
        ld  a,#0x8f
        out (#0x99),a
        in  a,(#0x99)

        ld a,#0b10100000
        out    (c),a     ; R46 Do the command

       loopLMCM5:

              ld  a,#2
              out (#0x99),a
              ld  a,#0x8f
              out (#0x99),a
              in  a,(#0x99)

              and #1
              jp z, exitLMCM5         ; if CE = 1 Exit
              and #128
              jp nz, loopLMCM5        ; if TR = 0 Loop

			        xor a
              ; read pixels
              ld  a,#7    ; 1px
              out (#0x99),a
              ld  a,#0x8f
              out (#0x99),a
              in  a,(#0x99)
               ; --------------- ScreenMode 5 & 7, merging 2 pixels
              rla
              rla
              rla
              rla
              ld  b,a

              ld a,d                
              cp #8              ; Testing if TIMP is requiered
      
              in  a,(#0x99)     ; retrieve second pixel

                ; ---------------- end screen 5 & 7
              jp nz,notimp5
              ; do timp    
              cp #0
              jp z,valuezero5     ; If pixel color=0, do not push it in RAM     
        notimp5:  
              or  b
              ld  (hl),a          ; Put Pixel color in RAM
        valuezero5:
              inc hl
              jp  loopLMCM5

        exitLMCM5:
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