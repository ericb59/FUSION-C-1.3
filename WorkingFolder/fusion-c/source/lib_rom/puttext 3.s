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
;    PutText



 GRPACX   =  #0xFCB7
 GRPACY   =  #0xFCB9 
 LOGOPR   =  #0xFB02
 FORCLR   =   0xF3E9       ; foreground color 
 BAKCLR   =   0xF3EA       ; background color
 BDRCLR   =   0xF3EB       ; border color

 .area _CODE
;----------------------------
;   MODULE  PutText  
;
;   PutText( int X, int Y,  char *str, char LogOp )
;   
;   Print string on graphics screen at position x,y using LogOperator
;   (ignores \n\l\t and other text features)
;
; 


   
_PutText::
  push ix
  ld ix,#0
  add ix,sp
  ld l,4(ix)
  ld h,5(ix)
  ld (GRPACX),hl ; X
  ld l,6(ix)
  ld h,7(ix)
  ld (GRPACY),hl ; Y
  ld a,10(ix)
  ld (LOGOPR),a  ; LogOp
  ld l,8(ix)
  ld h,9(ix)

lb_ptlp:  
  ld   a,(hl)
  or   a
  jr   z, lb_ptEx
  call 0x008D       ; Call Bios
  ei
  inc hl
  jr  lb_ptlp
lb_ptEx:
  pop ix
  ret