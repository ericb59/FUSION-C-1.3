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
;    FillVram


 .area _CODE

;----------------------------
;   MODULE  FillVram
;
;  void         FillVram(int Startadress, char value, int length);
;   
;   
;   
;
_FillVram::
        
    push ix
    ld   ix,#0
    add  ix,sp
    ld   l,4(ix)
    ld   h,5(ix)
    ld   a,6(ix)
    ld   c,7(ix)
    ld   b,8(ix)
  	call 0x056		; Bios Fill Vram  routine
  	ei
  	pop ix
  	ret