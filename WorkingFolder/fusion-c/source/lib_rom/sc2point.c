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
/* 
|    functions for MSX1 Screen 2 
|	 SC2Point	
|     2019 Eric Boez
|    
*/


#include "../../header/vdp_graph1.h"
#include <stdlib.h>

char SC2Point(unsigned int x, unsigned int y) __naked
{
    x,y;
    
    __asm
  
  push ix
  ld   ix,#0
  add  ix,sp
  ld   c,4(ix)         ;
  ld   b,5(ix) 

  ld   e,6(ix)
  ld   d,7(ix)

  push iy
  ld   iy,(#0xFCC0)     ; mainrom slotaddress
  
  ld   ix,#0x010E       ; SCALXY
  call #0x001c          ; interslotcall

  ld   ix,#0x0111       ; MAPXYC
  call #0x001c          ; interslotcall

  ld   ix,#0x011D       ; READC
  call #0x001c          ; interslotcall

  ld l,a
  ei
  pop  iy
  pop  ix
  ret
  __endasm;

}