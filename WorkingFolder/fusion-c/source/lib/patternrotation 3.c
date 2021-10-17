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
|  PatternRotation
*/ 

//-----------------------------------------------------------------------------
// Pattern Rotation : Rotate a 8x8 pixels pattern to 90° angles, right or left
// *pattern : Address of the 8x8 Pattern
// *buffer  : address of a 8 Bytes buffer
// direction : // 0 : Rotate to right    1: rotate to Left

void PatternRotation (void *Pattern, void *buffer, char rotation) __naked    
{
    Pattern,buffer,rotation;
    __asm
            ;--------------------------------------------
            ;Rotate 8x8 Pattern 
            ;input:
            ;DE = 8x8 Pattern
            ;HL = 8 bytes buffer
            ;A   =  0x17 equals Clockwise
            ;       0x1F equals Counter Clockwise
            ;
            ;Output:
            ; Rotates a Pattern 90° left or right into a buffer
            ;

                Push ix
                ld ix,#0
                add ix,sp
                ld e,4(ix)
                ld d,5(ix)
                ld l,6(ix)
                ld h,7(ix)
                ld a,8(ix)
                pop ix

                and #1
                ld a,#0x17
                jr  z,rotate        ; If direction is right (=0)
                ld a,#0x1F

            rotate:
               ld (rotloop),a
               xor #0x09
               ld (rotloop+#2),a
               ld c,#8
            rotbigloop:
               ld a,(de)
               inc de
               push hl
               ld b,#8
            rotloop:
               rra
               rl (hl)
               inc hl
               djnz rotloop
               pop hl
               dec c
               jr nz,rotbigloop
               ret

    __endasm;
}