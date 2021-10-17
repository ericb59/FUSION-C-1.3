; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                   V1.0 - 09-10-11 2018                    |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
;
; Direct reading of the joystick thru PSG Port 
; return result inside the defined Structure
;
; Eric Boez & GDX 2019 

.area _CODE

_JoystickReadTo::

 ld a,(hl)				; Input: A = joystick port (1 or 2)
 inc hl



  and #2
  ld  c,#0b00001111  	; Joystick 1
  jr  z,Joy2    		; Jump if A was 1
  ld  c,#0b01001111  	; Joystick 2
Joy2:
  ld  a, #15
  out (#0xA0),a
  in  a,(#0xA2)
  and #0x80   			; Keep the bit 7 (KANA/Code LED)
  or  c
  out (#0xA1),a

  ld  a, #14
  out (#0xA0),a
  in  a,(#0xA2)
  cpl			 		; invert the bits , thus 1 means pressed
  ld c,a

  xor a
  rrc c
  rla
  ld (hl),a ; Up
  inc hl

  xor a
  rrc c
  rla
  ld (hl),a ; Down
  inc hl

  xor a
  rrc c
  rla
  ld (hl),a ; Left
  inc hl

  xor a
  rrc c
  rla
  ld (hl),a ; Right
  inc hl

  xor a
  rrc c
  rla
  ld (hl),a ; B1
  inc hl

  xor a
  rrc c
  rla
  ld (hl),a ; B2

  ld a,c
  rrca
  rrca
  and #15
  inc hl
  ld (hl),a 		; "global direction as byte value"

  ret