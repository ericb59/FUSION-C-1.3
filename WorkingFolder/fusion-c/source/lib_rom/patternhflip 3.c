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
|                   V1.3 -  04 - 2020                       |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|             A S M  &  C  S O U R C E   C O D E            |
|                                                           |
\___________________________________________________________/
*/
/*  Sprite Pattern Rotation & Sprite Pattern flip routines
|    
|     2020 Eric Boez
|    
|  PatternHFlip
*/ 
//-----------------------------------------------------------------------------
// Pattern Horizontal Flip. : Flip horizontaly a 8x8 Pixels pattern
// *pattern : Address of the 8x8 Pattern
// *buffer  : address of a 8 Bytes buffer
void PatternHFlip (void *Pattern, void *buffer) __naked    
{
 Pattern,buffer;
    __asm

                ;--------------------------------------------
                ;Flip horizontaly 8x8 Pattern 
                ;input:
                ;DE = 8x8 Pattern
                ;HL = 8 bytes buffer
                ;
                ; Fast byte Fliping routine by John Metcaff
                ;
                Push ix
                ld ix,#0
                add ix,sp
                ld e,4(ix)
                ld d,5(ix)
                ld l,6(ix)
                ld h,7(ix)
                pop ix
                ld b,#8
            Hloop:
               push hl
               ld a,(de)
               ld l,a
               rlca
               rlca
               xor l
               and #0xAA
               xor l
               ld l,a
               rlca
               rlca
               rlca
               rrc l
               xor l 
               and #0x66 
               xor l

               pop hl
               ld (hl),a
               inc hl
               inc de
               djnz Hloop

               ret

    __endasm;
}