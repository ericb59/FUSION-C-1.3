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
; Call Bios functions
;
;    JoystickRead
;    TriggerRead


 .area _CODE

_CallBiosRetX1:

  ld iy, (0xFCC0)	; mainrom slotaddress 
  call 0x001c		; interslotcall
  ei
  ld   l,a 			; Return value to L 
  ld   h,#0
  pop  ix
  ret

;----------------------------
;   MODULE  JoystickRead
;
;   char JoystickRead(char joyNumber)
;   
;   
;   
;

_JoystickRead::
  push ix
  ld a,(hl)
  ld  ix,#0x00d5       ; Bios Joystick Read routine
  jp  _CallBiosRetX1



  ;---------------------------- 
;   MODULE  TriggerRead
;
;   unsigned char TriggerRead(char joyNumber)
;   
;   
;   
;
_TriggerRead::
  
  ld   a,(hl)
  push ix
  ld   ix,#0x00d8       ; Bios Trigger Read routine
  jp _CallBiosRetX1

