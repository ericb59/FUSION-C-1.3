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
|  LMCM8
|  
*/


#include "../../header/vdp_graph2.h"


void	LMCM8( void *buffer, unsigned int XS, unsigned int YS, unsigned int NX, unsigned int NY, char OP) __naked
{
	buffer,XS,YS,NX,NY,OP;
__asm

ACPAGE = 0xFAF6
DPPAGE = 0xFAF5
FORCLR = #0xF3E9         ; foreground color
EXBRSA = 0xFAF8			 ; the slot of SUB-ROM (0 for MSX1)


;**************************************************************************************
; LMCM8 (Logical move to CPU memory)                    Eric
;
; LMCM8 ( void *buffer, unsigned int XS, unsigned int YS, unsigned int NX, unsigned int NY, char OP)
; This function works with Screen Mode 8 to 12
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
        ld     a,6(ix)  
        out    (c),a      ; R32 XS low byte
        ld     a,7(ix)  
        out    (c),a      ; R33 XS high byte
        ld     a,8(ix)  
        out    (c),a      ; R34 YS low byte
        ld     a,9(ix)  
        out    (c),a      ; R35 YS high byte

        out (c),a       ;R36 dummy
        out (c),a       ;R37 dummy
        out (c),a       ;R38 dummy
        out (c),a       ;R39 dummy

        ld  a,10(ix)    
        out    (c),a      ; R40 DX low byte
        ld  a,11(ix)    
        out    (c),a      ; R41 DX high byte
        ld  a,12(ix)    
        out    (c),a      ; R42 DX low byte
        ld  a,13(ix)    
        out    (c),a      ; R43 DX high byte     

        out    (c),a      ; R44 Dummy
        xor a
        out    (c),a      ; R45 Parameters DIX and DIY in incremental direction with internal internal VRAM

        ld  a,#7          ;clear TR status
         
         out (#0x99),a
         ld  a,#0x8f
         out (#0x99),a
         in  a,(#0x99)

        ld a,#0b10100000
        out    (c),a              ; R46 Do the command

        ld a,d                    ; TEsing if TIMP mode is requested        
        sub a,#8  
        jp c,LoopLMCM8notimp      ; If no TIMP operator, go to the simplest routine

       LoopLMCM8:                 ; Loop with TIMP
              ld  a,#2
              out (#0x99),a
              ld  a,#0x8f
              out (#0x99),a
              in  a,(#0x99)

              and #1
              jp z, ExitLMCM8     ; if CE = 1 Exit
              and #128
              jp nz, LoopLMCM8    ; if TR = 0 Loop

                                         
              ld  a,#7                ; Prepare reading pixels
              out (#0x99),a
              ld  a,#0x8f
              out (#0x99),a
             
              in  a,(#0x99)               ; Pixel Readiung
              cp #0
              jp z,valuezero8             ; If pixel color=0, do not push it in RAM     
        notimp8:
              ld  (hl),a                 ; Put Pixel color in RAM
        valuezero8:
              inc hl
              jp  LoopLMCM8

        ExitLMCM8:
              ld  a,#7                   ; Reading Last pixel ? !
              out (#0x99),a
              ld  a,#0x8f
              out (#0x99),a
              in  a,(#0x99)
              ld  (hl),a

              xor a
             
              out (#0x99),a
              ld  a,#0x8f
              out (#0x99),a
              in  a,(#0x99)

              ei
              pop ix
              ret

      LoopLMCM8notimp:            ; Loop With no Timp
              ld  a,#2
              out (#0x99),a
              ld  a,#0x8f
              out (#0x99),a
              in  a,(#0x99)

              and #1
              jp z, ExitLMCM8     ; if CE = 1 Exit
              and #128
              jp nz, LoopLMCM8notimp    ; if TR = 0 Loop

              ld  a,#7                ; Prepare reading pixels
              out (#0x99),a
              ld  a,#0x8f
              out (#0x99),a
             
              in  a,(#0x99)               ; Pixel Reading
              
              ld  (hl),a                 ; Put Pixel color in RAM
              inc hl
              jp  LoopLMCM8notimp
              jp ExitLMCM8



__endasm;
}