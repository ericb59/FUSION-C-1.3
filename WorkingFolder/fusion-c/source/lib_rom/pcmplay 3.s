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
;    PCMPlay




 .area _CODE
;----------------------------
;   MODULE  PCMPlay
;
;   void PCMPlay(int start, int length)
;   
;   Play PCM from VRAM adress
;   on MSX Turbo-R 
;

_PCMPlay::
  push ix     
  ld   ix,#0
  add  ix,sp
  ld   l,4(ix)
  ld   h,5(ix)   
  ld   c,6(ix)
  ld   b,7(ix)
  ld   a,#0x80           ; Input parameter: 0b100000000

  call 0x0186		; interslotcall
  ei
  pop ix
  ret