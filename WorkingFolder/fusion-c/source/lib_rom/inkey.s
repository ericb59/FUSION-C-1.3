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

   call #0x009c   ; CHSNS Tests the status of the keyboard buffer
   ld l,#0
   jr z,bufferEmpty

bufferNotEmpty:   
   call #0x009f   ; chget bios function. Buffer is not empty thus no wait. 
   ei
   ld   l,a      ; Return to register L

bufferEmpty:
   ei
   ld h,#0
   ret