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
;     GetCPU
;	  ChangeCPU





 .area _CODE
;----------------------------
;   MODULE  GetCPU
;
;   char GetCPU(void) 
;   
;   Return 0: Z80 mode        1: R800 Rom Mode     2: R800 DRAM Mode
;   Only For MSX Turbo-R
;

_GetCPU::
  call 0x0183		; 
  ei
  ld   l,a 			; Return value to L 
  ld   h,#0
  ret


;----------------------------
;   MODULE  ChangeCPU
;
;   void ChangeCPU (char n)
;   Change CPU Mode
;   0: Z80 mode        1: R800 Rom Mode     2: R800 DRAM Mode
;   Only For MSX Turbo-R
;

_ChangeCPU::
  push ix
  ld   ix,#0
  add  ix,sp
  ld   a,4(ix)
  call 0x0180		
  ei
  pop ix
  ret