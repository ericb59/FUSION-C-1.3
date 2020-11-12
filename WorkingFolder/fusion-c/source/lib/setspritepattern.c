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
|                   V1.2a - 11 2019                         |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|         compilation : > sdcc -mz80 -c  msx_misc.c         |
|                                                           |
\___________________________________________________________/
*/
/*  setspritepattern & SetSpriteColors 
|  
|     2019 Eric Boez
*/
#define __FUSIONC 2020 
#include "../../header/msx_fusion.h"


#define SCRMOD  0xFCAF      /* current screen mode */
#define ACPAGE  0xFAF6      /* active page number */
#define DPPAGE  0xFAF5      /* display page number */
#define ATRBAS  0xF928      /* sprite attribute table base address */
#define PATBAS  0xF926      /* sprite pattern generator table base address */




/* --------------------------------------------------------- */
/*  set sprite pattern                                       */
/* --------------------------------------------------------- */
void SetSpritePattern(  char pattern_no,  char* p_pattern,  char s_size ) {

    CopyRamToVram(p_pattern, Peekw( 0xF926 ) + (pattern_no << 3), s_size);

}


void SetSpriteColors(char spriteNumber, char *data)
{
		CopyRamToVram(data, (Peekw( 0xF928 )-512) + (spriteNumber << 4), 16);   // Sprite color table is at ATRBAS - 512

}