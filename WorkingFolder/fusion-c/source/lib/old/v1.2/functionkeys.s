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
; void FunctionKeys(char n)
;
;     2018 Eric Boez
; Hide or Show Functions keys, 

.area _CODE

_FunctionKeys::

    push  ix
    push  iy
    ld ix,#0
    add ix,sp
    ld  a,4(ix)

    ld   ix,#0x00cf         ; Bios show 
    bit 0,a
    call nz,hide

    ld   iy,(#0xFCC0)     ; mainrom slotaddress
    call 0x001c           ; interslotcall
    ei
    pop iy
    pop ix
    ret

hide:
    ld   ix,#0x00cc         ; Bios show 
    ret 
