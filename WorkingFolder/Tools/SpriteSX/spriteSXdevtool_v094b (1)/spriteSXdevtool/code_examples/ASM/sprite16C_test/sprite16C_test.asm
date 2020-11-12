; ==============================================================================
;   sprite16C_test.c
;   test 16x16 multicolor sprites MSX2 ROM (spriteSX)
;   Assemble with asMSX
; ==============================================================================



    .page	1
		.ROM
		;.SIZE 32
		
		;.SEARCH
		

VDPVRAM   EQU   $98 ;VRAM Data (Read/Write)
VDPSTATUS EQU   $99 ;VDP Status Registers

;system vars
MSXVER EQU $002D
FORCLR EQU $F3E9 ;Foreground colour
BAKCLR EQU $F3EA ;Background colour
BDRCLR EQU $F3EB ;Border colour
CLIKSW EQU $F3DB ;0 disabled / 1 enabled
RG1SAV EQU $F3E0 ;VDP REG 1
EXTVDP EQU $FFE7 ;

;BIOS (info by MSX Assembly Page)
;http://map.grauw.nl/resources/msxbios.php
DISSCR EQU $0041 ;inhibits the screen display
ENASCR EQU $0044 ;displays the screen
WRTVDP EQU $0047 ;write data in the VDP-register
RDVRM  EQU $004A ;Reads the content of VRAM
WRTVRM EQU $004D ;Writes data in VRAM
SETRD  EQU $0050 ;Enable VDP to read
SETWRT EQU $0053 ;Enable VDP to write
FILVRM EQU $0056 ;fill VRAM with value
LDIRMV EQU $0059 ;Block transfer to memory from VRAM
LDIRVM EQU $005C ;Block transfer to VRAM from memory
CHGMOD EQU $005F ;Switches to given screenmode
CHGCLR EQU $0062 ;Changes the screencolors
CLRSPR EQU $0069 ;Initialises all sprites
INITXT EQU $006C ;Switches to SCREEN 0 (text screen with 40 * 24 characters)
INIT32 EQU $006F ;Switches to SCREEN 1 (text screen with 32*24 characters)
INIGRP EQU $0072 ;Switches to SCREEN 2 (high resolution screen with 256*192 pixels)
INIMLT EQU $0075 ;Switches to SCREEN 3 (multi-color screen 64*48 pixels)
SETTXT EQU $0078 ;Switches to VDP in SCREEN 0 mode
SETT32 EQU $007B ;Switches VDP in SCREEN mode 1
SETGRP EQU $007E ;Switches VDP to SCREEN 2 mode
SETMLT EQU $0081 ;Switches VDP to SCREEN 3 mode
CALPAT EQU $0084 ;Returns the address of the sprite pattern table
CALATR EQU $0087 ;Returns the address of the sprite attribute table
GSPSIZ EQU $008A ;Returns current sprite size
GRPPRT EQU $008D ;Displays a character on the graphic screen

GICINI EQU $0090 ;Initialises PSG and sets initial value for the PLAY statement
WRTPSG EQU $0093 ;Writes data to PSG-register
RDPSG  EQU $0096 ;Reads value from PSG-register

; more BIOS functions
CHKRAM EQU $0000 ;Tests RAM and sets RAM slot for the system
ENASLT EQU $0024 ;Switches indicated slot at indicated page on perpetual
CHGET  EQU $009F ;One character input
POSIT  EQU $00C6
GTSTCK EQU $00D5 ;Returns the joystick status
GTTRIG EQU $00D8 ;Returns current trigger status
SNSMAT EQU $0141 ;Returns the value of the specified line from the keyboard matrix
KILBUF EQU $0156 ;Clear keyboard buffer




;screen 1
BASE5  EQU $1800 ;name table
BASE6  EQU $2000 ;color table
BASE7  EQU $0000 ;character pattern table

;screen 2
BASE10 EQU $1800 ;name table
BASE11 EQU $2000 ;color table
BASE12 EQU $0000 ;character pattern table
BASE13 EQU $1B00 ;sprite attribute table
BASE14 EQU $3800 ;sprite pattern table

BSATTR  EQU 0x1E00 ;sprite attribute table 
BSDATA  EQU 0x3800 ;sprite pattern table 
BSCOLOR EQU 0x1C00 ;sprite colours

MAIN:

  xor  A
  ld   [CLIKSW],A    ;keys click off

  ;color 15,1,1 
  ld   A,15
  ld   [FORCLR],A
  ld   A,1
  ld   [BAKCLR],A
  ld   A,1
  ld   [BDRCLR],A  
  call CHGCLR 
  
  ;screen 4
  ld   A,4
	call CHGMOD
    
  ;set sprite mode (16x16 nozoom)
  ld   DE,$0100
  call SETUPSPRITES

  ld   HL,PALETTE_DATA
	call SETPALETTE
    
  ld   HL,SPRITE_DATA
  ld   DE,BASE14  
  ld   BC,32*8
  call LDIRVM
  
  ;vuelca a VRAM buffer atributos sprites
  ld   HL,SPRITE_ATTRS
  ld   DE,BSATTR        ;BASE13  
  ld   BC,4*8
  call LDIRVM
  
  
  ; apply line colors of sprites
  ld   HL,COLOR_DATA
  ld   DE,BSCOLOR  
  ld   BC,128
  call LDIRVM
  
  call    PRESSBUT
  
  call    CHKRAM
  
  
  
PRESSBUT:
  halt
  
  ld	 A,0
	call GTTRIG
	bit	 7,A
	ret  NZ
	
  ; button 1, joy A
	ld	 A,1
	call GTTRIG
	bit	 7,A
	ret	 NZ

; button 1, joy B
	ld	 A,2
	call GTTRIG
	bit	 7,A
	ret  NZ
  	
	jp   PRESSBUT
  






  

; set size and zoom of the sprites
; D size -> 0=8x8, 1=16x16
; E zoom -> 1=x2
SETUPSPRITES:
 
  ;in A,(VDPSTATUS)
  
  ld B,0
  
  ld A,D
  cp 1
  jr NZ,STSP1
  set 1,b ; --- if 16x16 sprites => set bit 1

STSP1:
  ld A,E
  cp 1
  jr NZ,STSP2
  set 0,b ; --- if zoom sprites => set bit 0

STSP2:
  ld HL,RG1SAV ; --- read vdp(1) from mem
  ld A,[HL]
  and $fc
  or B
  
  ld  B,A
  ld  C,$01
  call  WRTVDP
  
  ret


//pausa en ciclos de VBLANK. PAL 1seg=50, NTSC 1seg=60. 
; BC = num cicles 
WAIT:
  dec BC
	ld A,B
	or C
	ret Z
	
	halt
  jr  WAIT
  
  


;paleta msx2
; HL - addr palette 
SETPALETTE:
 
  ld   A,[MSXVER]
  or   A
  ret  Z
  
  ;ld  HL,PALETTE00
  xor	A
	di
	out	 [VDPSTATUS],A
	ld	  A,144
	out	 [VDPSTATUS],A
	ld	  BC,$209A
	otir
	ei  
  
  ret
  
  


;SPRITE ATRIBUTE DATAS #########################################################
;Y,X,SPR,COLOR
;SPR*4 in 16x16 mode
SPRITE_ATTRS:
db 0,0,0,2
db 0,16,4,11
db 0,32,8,3
db 0,48,12,14
db 0,64,16,8
db 0,80,20,9
db 0,96,24,12             
db 0,112,28,10 

;END SPRITE ATRIBUTE DATAS #####################################################







; Frutas 16x color

SPRITE_DATA:
; 0-Pepino
db $0F,$1F,$3D,$3F,$7B,$7C,$BF,$BF
db $9F,$EF,$6F,$1F,$0F,$05,$05,$1D
db $C0,$E0,$60,$C0,$40,$80,$80,$84
db $86,$DE,$C0,$C0,$80,$00,$00,$C0
; 1-Pear
db $03,$07,$4F,$CF,$4D,$4F,$2C,$1E
db $3F,$3F,$3F,$3F,$1F,$02,$02,$06
db $C0,$E2,$E6,$E2,$A2,$F4,$38,$7C
db $FE,$FE,$FE,$FC,$F8,$40,$40,$60
; 2-Onion
db $05,$07,$1A,$2E,$6F,$5B,$5C,$5B
db $5F,$58,$6F,$2D,$16,$02,$02,$06
db $40,$C0,$B8,$D4,$D4,$6A,$EA,$6A
db $EA,$6A,$D4,$D4,$F8,$40,$40,$60
; 3-Tomato
db $05,$07,$1F,$3F,$7F,$7F,$7F,$7D
db $7F,$7F,$78,$3F,$1F,$04,$04,$0C
db $40,$C0,$F0,$F8,$FC,$FC,$FC,$7C
db $FC,$FC,$3C,$F8,$F0,$40,$40,$60
; 4-Orange
db $07,$1F,$3F,$3F,$7F,$71,$7F,$7F
db $7F,$7E,$3E,$3F,$1F,$07,$02,$06
db $E0,$F8,$FC,$FC,$FE,$8E,$FE,$FE
db $FE,$7E,$7C,$FC,$F8,$E0,$40,$60
; 5-Lemon
db $00,$07,$1F,$3F,$7F,$71,$FF,$FF
db $7B,$7C,$3F,$1F,$07,$02,$02,$06
db $00,$E0,$F8,$FC,$FE,$8E,$FF,$FF
db $DE,$3E,$FC,$F8,$E0,$40,$40,$60
; 6-Mushroom
db $05,$1E,$3F,$6F,$57,$6E,$3F,$00
db $07,$05,$07,$04,$06,$03,$02,$06
db $60,$F8,$F4,$EA,$76,$BE,$7C,$00
db $E0,$60,$E0,$20,$60,$C0,$40,$60
; 7-Xampi
db $05,$1E,$3F,$6F,$57,$6E,$3F,$07
db $07,$05,$07,$04,$06,$03,$02,$06
db $60,$F8,$F4,$EA,$76,$BE,$7C,$E0
db $E0,$60,$E0,$20,$60,$C0,$40,$60


COLOR_DATA:
; 0-Pepino
db $0C,$0C,$0C,$0C,$02,$02,$03,$03
db $03,$03,$03,$02,$0C,$0F,$0F,$07
; 1-Pear
db $0C,$02,$02,$02,$0C,$02,$02,$02
db $02,$02,$02,$02,$0C,$0E,$0E,$05
; 2-Onion
db $0A,$0A,$0B,$0B,$0B,$0B,$0B,$0B
db $0B,$0B,$0B,$0B,$0B,$0E,$0E,$05
; 3-Tomato
db $0C,$0C,$09,$09,$09,$09,$09,$09
db $09,$09,$09,$09,$09,$05,$0F,$07
; 4-Orange
db $0D,$0D,$0D,$0D,$0D,$0D,$0D,$0D
db $0D,$0D,$0D,$0D,$0D,$0D,$07,$07
; 5-Lemon
db $0D,$0A,$0B,$0B,$0B,$0B,$0B,$0B
db $0B,$0B,$0B,$0B,$0A,$0E,$05,$05
; 6-Mushroom
db $08,$09,$09,$09,$09,$09,$08,$0E
db $0D,$0D,$0D,$0D,$0D,$0D,$0E,$0E
; 7-Xampi
db $0A,$0E,$0A,$0E,$0A,$0E,$0A,$05
db $0F,$0F,$0F,$0F,$0F,$0F,$0E,$0E


; MSX2_Palette
; RB,G
PALETTE_DATA:
db $00,$00
db $00,$00
db $11,$05
db $33,$06
db $25,$02
db $37,$03
db $51,$02
db $27,$06
db $62,$02
db $70,$00
db $63,$06
db $70,$07
db $11,$04
db $70,$03
db $66,$06
db $77,$07

  