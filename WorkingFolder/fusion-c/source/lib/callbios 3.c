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
|                     V1.3 - 05 2020                        |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|                                                           |
\___________________________________________________________/
*/ 
/*    2019-2020 Eric Boez
|
|  CallBios
|
*/
#define __FUSIONC 2020 
#include "../../header/msx_fusion.h"


/* ------------------------------------------------------------*/
/*   CALLBIOS       Call A MSX BIOS  routine                    */
/*   Regsiters parameters are passed thru the REGDATA Structure */ 
/* -------------------------------------------------------------*/

void CallBios(void *registers) __z88dk_fastcall __naked
{
registers;
  __asm

                              ; IX, IY, AF, DE, BC, HL
        push ix               ; Save Original IX
                      
        push hl                 ; save original HL 
        push hl 
        pop ix 

        ld a,4(ix) 
        
        ld e,6(ix)
        ld d,7(ix)
        
        ld c,8(ix) 
        ld b,9(ix) 
        
        ld l,2(ix) 
        ld h,3(ix) 
        push hl 
        pop iy 

        ld l,0(ix) 
        ld h,1(ix) 

        push hl 

        ld l,10(ix) 
        ld h,11(ix)

        pop ix 
        

        ; Call BIOS routine
        di 
        ld iy, (0xFCC0) ; mainrom slotaddress 
        call 0x001c   ; interslotcall
        ei
       

         ; End of routine 
         pop ix       ; recover Address

         ; Updating AF,DE,BC,HL Structure 
         ld 4(ix),a
         ld 5(ix),#0
         ld 6(ix),e 
         ld 7(ix),d 
         ld 8(ix),c 
         ld 9(ix),b 
         ld 10(ix),l 
         ld 11(ix),h
         pop ix
         ret
  __endasm;
}

