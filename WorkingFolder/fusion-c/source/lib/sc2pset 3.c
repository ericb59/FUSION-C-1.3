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
|                V1.3  -  December - 2019                   |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|                                                           |
|                                                           |
\___________________________________________________________/
*/
/* Pset, Line & BoxFill & BoxLine functions for MSX1 Screen 2 
|    
|     2019 Eric Boez
|    
*/


#include "../../header/vdp_graph1.h"
#include <stdlib.h>

void SC2Pset(char x, char y, char color) __naked
{
  x,y,color;
  __asm
        // Fast PSET Routine for SCREEN 2
        // Thank you to Ping Pong for this code

        push ix
        push hl
        push de
        push bc
        push af
        ld ix, #12
        add ix, sp

        ld a, 1(ix)
        srl a
        srl a
        srl a
        ld h, a
        ld a, 1(ix)
        and #7
        ld e, a

        ld a, 0(ix)

        and #248
        add a, e
        ld l,a

        ; HL = Address
        push hl

        ld a, 0(ix)
        and #7
        ld de,#_bittable
        ld h,#0
        ld l, a
        add hl, de
        ld e,(hl)
        pop hl

        ld a,l
        di
        out (0x99),a
        ld a,h
        and #0x3f
        out (0x99),a
        nop
        nop
        nop ; ajout pour VDP MSX1

        in a, (0x98)

        ld b, a

        or e
        cp #0xff



        jr nz, _Pset_Color_1$

        ; here we go if the readed byte was 255. So we assume that and invert using the mask the readed byte.

        xor e


        ld b, #0xf0
        jr _Pset_Color_3$
_Pset_Color_1$:

        ld b, #0x0f

_Pset_Color_3$:
        ld e,a
        ld a,l

        out (0x99),a

        ld a,h
        or #0x40
        out (0x99),a

        ld a, e
        out (0x98),a

        ld a, #32
        add a, h
        ld h, a

        ld a,l
        out (0x99),a
        ld a,h
        and #0x3f
        out (0x99),a
        nop
        nop
        nop ; ajout pour VDP MSX1
        in a, (0x98)
        and b
        ld d, a
        ld a,l

        out (0x99),a

        ld a,h
        or #0x40
        out (0x99),a
        ei

        ld a, 2(ix)
        bit 7, b
        jr nz, _Pset_Color_2$

        sla a
        sla a
        sla a
        sla a
_Pset_Color_2$:
        or d

        out (0x98),a

        pop af
        pop bc
        pop de
        pop hl
        pop ix
        ret
_bittable:  .db #128,#64,32,#16,#8,#4,#2,#1

__endasm;
}















