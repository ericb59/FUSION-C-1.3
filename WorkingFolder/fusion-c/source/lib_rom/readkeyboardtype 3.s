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
;    ReadKeyboardType





 .area _CODE
;----------------------------
;   MODULE  ReadKeyboardType 
;
;   char ReadKeyboardType(void)
;   
;   Return Keyboard type 0:Japanese, 1:International, 2: French, 3: UK, 4:German 
;   
;
_ReadKeyboardType::
  ld   hl,#0x2c       ; Adresse to read
  call 0x000c   ; 
  ei
  and #0b00001111
  ld   l,a      ; Return value to L 
  ret