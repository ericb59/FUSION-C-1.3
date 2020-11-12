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
|  PatternVFlip
*/ 


//-----------------------------------------------------------------------------
// Pattern Vertical Flip. : Flip vertically a 8x8 Pixels pattern
// *pattern : Address of the 8x8 Pattern
// *buffer  : address of a 8 Bytes buffer
void PatternVFlip (void *Pattern, void *buffer) __naked    
{
 Pattern,buffer;
    __asm

                Push ix
                ld ix,#0
                add ix,sp
                ld e,4(ix)
                ld d,5(ix)
                ld l,6(ix)
                ld h,7(ix)
                pop ix
                ld bc,#7
                add hl,bc
                ld b,#8
            Vloop:
               ld a,(de)
               ld (hl),a
               inc de 
               dec hl

               djnz Vloop

               ret

    __endasm;
}