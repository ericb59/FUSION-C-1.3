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
;    Locate




 .area _CODE
;----------------------------
;   MODULE  Locate
;
;   void Locate(char x, char y)
;   
;
;  
;

 _Locate::
  push ix
  ld   ix,#0
  add  ix,sp
  ld   h,4(ix) ;x
  inc  h
  ld   l,5(ix) ;y
  inc  l
  call 0x00c6		; locate
  ei
  pop ix
  ret