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
|                                                           |
\___________________________________________________________/
|
|     2019-2020 Eric Boez
|
|	fPutSprite
|
*/

#define FUSION 2019
#include "../../header/msx_fusion.h"
#include "../../header/vdp_sprites.h"

void 	fPutSprite(void *parameters)   __z88dk_fastcall	 __naked
{
	parameters;

__asm

;----------------------------
;   MODULE	Fast PUTSPRITE
;
;	fPutSprite ( void *parameters );
;	Eric Boez 2020


    ld  a,(HL) 	; sprite_no
    ex de,HL 	; Save HL
    rlca
    rlca
    ld hl,(ATRBAS); add HL to A
    		
    add a,l 	; Address calculation
    ld l,a
    adc a,h 
    sub l 
    ld h,a 
	  di 
    call _SetVDPwrite 
    ld  c,#0x98 
    ex de,hl 	; Retrieve HL
    inc hl
    di
  	outi
  	outi
  	outi
  	outi
  	ei
    ret

__endasm;
}