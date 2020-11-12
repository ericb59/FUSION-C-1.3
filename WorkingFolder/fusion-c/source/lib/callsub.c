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
|  CallSub
|
*/
#define __FUSIONC 2020 
#include "../../header/msx_fusion.h"
/* ------------------------------------------------------------*/
/*   CALLSUB       Call A MSX2 Subrom routine                   */
/*   Regsiters parameters are passed thru the REGDATA Structure */ 
/* -------------------------------------------------------------*/
void CallSub(void *registers) __z88dk_fastcall __naked
{
registers;
  __asm
; In: IX = address of routine in MSX2 SUBROM
;     AF, HL, DE, BC = parameters for the routine
;
; Out: AF, HL, DE, BC = depending on the routine
;
; Changes: IX, IY, AF', BC', DE', HL'
;
; Call MSX2 subrom from MSXDOS. Should work with all versions of MSXDOS.
;
; Notice: NMI hook will be changed. This should pose no problem as NMI is
; not supported on the MSX at all.
  CALSLT  =   0x001C
  NMI     =   0x0066
  EXTROM  =   0x015f
  EXPTBL  =   0xfcc1
  H_NMI   =   0xfdd6

                                ; IX, IY, AF, DE, BC, HL
        push ix                 ; Save Original IX
                      
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
        di

        ; Call Sub Rom from DOS routine
         exx
         ex     af,af'       ; store all registers'
         ld     hl,#EXTROM
         push   hl
         ld     hl,#0xC300
         push   hl           ; push NOP ; JP EXTROM
         push   ix
         ld     hl,#0x21DD
         push   hl           ; push LD IX,<entry>
         ld     hl,#0x3333
         push   hl           ; push INC SP; INC SP
         ld     hl,#0
         add    hl,sp        ; HL = offset of routine
         ld     a,#0xC3
         ld     (H_NMI),a
         ld     (H_NMI+1),hl ; JP <routine> in NMI hook
         ex     af,af'       ;'
         exx                 ; restore all registers
         ld     ix,#NMI
         ld     iy,(EXPTBL-1)
         call   #CALSLT      ; call NMI-hook via NMI entry in ROMBIOS
                             ; NMI-hook will call SUBROM
         exx
         ex     af,af'       ; store all returned registers'
         ld     hl,#010
         add    hl,sp
         ld     sp,hl        ; remove routine from stack
         ex     af,af'       ;'
         exx                 ; restore all returned registers
        
         ; End of routine 
         pop ix       ; recover Address
         ei
         ; Updating AF,DE,BC,HL structure
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
