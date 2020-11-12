; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                   V1.3 -  03-04 2020                      |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
; VDPwrite Functions
;
;	SpriteOff
;	SpriteOn

;----------------------------
;   MODULE  SpriteOff
;
;   void SpriteOff(void)
;   
;   disable Sprites
;   
;
RG1SAV = 0xF3E0 
DPPAGE = 0xFAF5 
ATRBAS = 0xF928 
RG25SAV = 0xFFFA
RG2SAV = 0xF3E1
RG8SAV = 0xFFE7
RG9SAV = 0xFFE8 

	.area _CODE
	
_SpriteOff::
  push ix
  ld a,(RG8SAV)
  or #0b00000010
  ld (RG8SAV),a
  ld b,a
  ld c,#8
  ld ix,#0x0047   ; Write VDP Bios
  ld iy, (0xFCC0)	; mainrom slotaddress 
  call 0x001c		; interslotcall
  ei
  pop ix
  ret


;----------------------------
;   MODULE  SpriteOn
;
;   void SpriteOn(void)
;   
;   Enable Sprites
;   
;

_SpriteOn::
  push ix
  ld a,(RG8SAV)
  and #0b11111101
  ld (RG8SAV),a
  ld b,a
  ld c,#8
  ld ix,#0x0047   ; Write VDP Bios
  ld iy, (0xFCC0)	; mainrom slotaddress 
  call 0x001c		; interslotcall
  ei
  pop ix
  ret
