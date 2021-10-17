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
|                   V1.2a   -  11-2019                      |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|					    	P S G 							|
|                                                           |
\___________________________________________________________/
|
|     2019-2020 Eric Boez
|
|	PutSprite
|
*/

#define FUSION 2019
#include "../../header/msx_fusion.h"
#include "../../header/vdp_sprites.h"

void 	PutSprite( char sprite_no,  char pattern_no, char x,  char y,  char ec_color ) __naked
{
	sprite_no,pattern_no,x,y,ec_color;

__asm

	push  ix
    ld ix,#0
    add ix,sp
    ld  a,4(ix) 	; sprite_no
    rlca
    rlca
    ld hl,(#0xF928)	; add HL to A
    add a,l 
    ld l,a
    adc a,h 
    sub l 
    ld h,a 
	di 
	
    call _SetVDPwrite 
    di
	ld  c,#0x98
    ld	a, 7 (ix)	; y
    out (c),a
    
    ld	a, 6 (ix)	; x
    out (c),a

    ld	a, 5 (ix)	; pattern_no
    out (c),a
    
    ld	a, 8 (ix)	; ec_color
    out (c),a
    ei
    pop ix
    
    ret

__endasm;
}