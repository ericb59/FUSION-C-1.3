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
; void FillVram(int Startadress, char value, int length)
;  
;     2018 Eric Boez


.area _CODE

_FillVram::
        
        push ix
        ld   ix,#0
        add  ix,sp
        ld   l,4(ix)
        ld   h,5(ix)
        ld   a,6(ix)
        ld   c,7(ix)
        ld   b,8(ix)
        push iy
        ld   ix,#0x0056       ; Bios Fill Vram  routine
        ld   iy,(#0xFCC0)      ; mainrom slotaddress
        call 0x001c           ; interslotcall
        ei
        ld l,a
        pop IY
        pop IX
        ret 
