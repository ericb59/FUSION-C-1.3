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
;    Inkey



 .area _CODE
;----------------------------
;   MODULE  Inkey  
;
;    Inkey (void)
;   
;   Check Key hit without waiting. Return Key Ascci code or 0 if no key was hit
;   
;
; 
_Inkey::
   push ix
   push iy
   ld   ix,#0x009c   ; CHSNS Tests the status of the keyboard buffer
   ld   iy,(0xFCC0)  ; mainrom slotaddress
   call 0x001c     ; interslotcall

   ld l,#0
   jr z,bufferEmpty
      ;jr   bufferNotEmpty

bufferNotEmpty:   
   ld   ix,#0x009f   ; chget bios function. Buffer is not empty thus no wait. 
   call 0x001c     ; interslotcall
   ei
   ld   l,a      ; Return to register L

bufferEmpty:
   ei
   ld h,#0

   pop iy
   pop ix
   ret