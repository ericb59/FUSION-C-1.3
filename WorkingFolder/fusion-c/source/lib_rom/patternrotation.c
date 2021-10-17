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
            ;DE = 8x8 Pattern address  
            ;HL = 8 bytes buffer
            ;A   =  0 Clockwise (R)
            ;       1 equals Counter Clockwise (L)
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
                ld c,#8
                and #1
    
                jr  z,rotbigloopR        ; If direction is right (=0)

            ; Left Rotation
            rotbigloopL:
               ld a,(de)
               inc de
               push hl
               ld b,#8
            rotloopL:
               rra
               rl (hl)
               inc hl
               djnz rotloopL
               pop hl
               dec c
               jr nz,rotbigloopL
               ret

            ; Right Rotation 
            rotbigloopR:
               ld a,(de)
               inc de
               push hl
               ld b,#8
            rotloopR:
               rla
               rr (hl)
               inc hl
               djnz rotloopR
               pop hl
               dec c
               jr nz,rotbigloopR
               ret

    __endasm;
}