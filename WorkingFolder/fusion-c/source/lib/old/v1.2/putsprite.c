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
|                   V1.2a - 08 2019                         |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|         compilation : > sdcc -mz80 -c  msx_misc.c         |
|                                                           |
\___________________________________________________________/
*/
/*  putsprite
|     2006/11/25    t.hara  
|     2019 Eric Boez
*/
#include "../../header/msx_fusion.h"


#define SCRMOD  0xFCAF      /* current screen mode */
#define ACPAGE  0xFAF6      /* active page number */
#define DPPAGE  0xFAF5      /* display page number */
#define ATRBAS  0xF928      /* sprite attribute table base address */
#define PATBAS  0xF926      /* sprite pattern generator table base address */


/* --------------------------------------------------------- */
/*  put sprite                                               */

void Put( char sprite_no, char pattern_no,  char x,  char y,  char ec_color ) 
{
	sprite_no; 
	pattern_no;
	x; 
	y; 
	ec_color;

__asm
    push ix
	ld ix,#0
	add ix,sp

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
   
    pop ix
    ei
__endasm;

}


void PutSprite( char sprite_no, char pattern_no,  char x,  char y,  char ec_color ) {
 
    SetVDPWrite(Peekw( ATRBAS ) + (unsigned int)(sprite_no << 2) );
    Put( sprite_no, pattern_no,  x,  y,  ec_color );
	
}
