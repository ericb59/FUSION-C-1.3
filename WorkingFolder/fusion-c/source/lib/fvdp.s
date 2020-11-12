; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                     V1.3 - 02 - 2020                      |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;|                                                           |
;\___________________________________________________________/
;
;
;	VDPgraph2.s	- MSX2 graphics VDP functions For MSX2
;
;
;		fVDP

;****************************************************************
;  fVDP Fast VDP Command Action
;   
;****************************************************************
_fVDP::
      di
    fvdpWait:
      ld  a,#2
      out (#0x99),a           
      ld  a,#128+#15
      out (#0x99),a
      in  a,(#0x99)
      and #1
      jp  nz, fvdpWait        ; wait CE
      xor a
      out (#0x99),a
      ld  a,#128+#15
      out (#0x99),a


      ld  a,#32
      out (#0x99),a
      ld  a,#128+#17
      out (#0x99),a ;R#17 := 32

      ld  bc,#0x0e9b  ; c=#0ex9b
                
      OUTI    
      OUTI
      OUTI
      OUTI
      OUTI
      OUTI
      OUTI
      OUTI
      OUTI
      OUTI
      OUTI
      OUTI
      OUTI
      OUTI
      OUTI      

      ei
      ret