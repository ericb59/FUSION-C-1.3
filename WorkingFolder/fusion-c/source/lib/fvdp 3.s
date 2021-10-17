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
;	fVDP

;****************************************************************
;  fVDP Fast VDP Command Action
;  void  fVDP (void *parameters)
;****************************************************************
_fVDP::

      di
      ld  a,#32                ; Start with Reg 32
      out (#0x99),a
      ld  a,#128+#17
      out (#0x99),a            ;R#17 := 32

      ld  bc,#0x0f9b           ; c=#x0fx9b

fvdpWait:
      ld  a,#2
      out (#0x99),a           
      ld  a,#128+#15
      out (#0x99),a
      in  a,(#0x99)
      rrca
      jp  c, fvdpWait        ; wait CE
                
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


      ld  a,#128+#44
      out (#0x99),a
      ld  a,#128+#17
      out (#0x99),a       ; VDP(17)<=44


loop_fVDP:
         ld  a,#2           ; Read Status Register #2
         out (#0x99),a
         ld  a,#0x8f
         out (#0x99),a
         in  a,(#0x99)

         rra
         jp nc, exit_fVDP    ; is CE finish ?
         rla
         rla
         jp nc, loop_fVDP   ; TR? transferring?
         outi
         jp loop_fVDP

exit_fVDP:
        out (#0x99),a
        ld  a,#0x8f
        out (#0x99),a
        ei
        ret