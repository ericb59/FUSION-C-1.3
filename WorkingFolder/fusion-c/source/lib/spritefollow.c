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
|                   V1.3 - 01 - 02 - 2020                   |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|               A S M    S O U R C E   C O D E              |
|                                                           |
\___________________________________________________________/
*/
/*  Sprite Follow 
|    
|     2020 Sylvain Cregut
|    
|  Sprite Follow
*/
 

//  Read and decode relatives Coordinates and set New X,Y position of the sprite
void SpriteFollow(void *SpriteStruct) __naked __z88dk_fastcall
{
SpriteStruct;
__asm
  ld  a,(hl)
  ld  b,a
  inc hl
  ld  a,(hl)
  ld  c,a
  inc hl
  xor a
  rld
  rra
    jp nc,_POS1
    neg
_POS1:
  add b
  ld  b,a
  xor a
  rld
  rra
    jp nc,_POS2
    neg
_POS2:
  add c
  dec hl
  ;ld  a,c
  ld  (hl),a
  dec hl
  ld  a,b
  ld  (hl),a
  ret
__endasm;
}