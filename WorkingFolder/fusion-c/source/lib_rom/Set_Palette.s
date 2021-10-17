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
;---------------------------------------------------------
;    set and restore screen palette for Screen 0 to 7, 9 and 10
;	Low level memory functions
;
;	(c) 1997, SOLID MSX C
;
;	SDCC port 2015
;
;	SetPalette 
;	SetColorPalette 
;	RestorePalette 
;
;
;
;----------------------------------------------------------

	.area _CODE

	
;-----------------------------------------------
;	Sets palette, provide table pointer
;
_SetPalette::
        ; Sets colors by given RGB-table in HL-reg
	
	push ix
	ld ix,#0
	add ix,sp
	ld l,4(ix)
	ld h,5(ix)
	pop ix
	
_isetpalette:	
	ld	b,#0x10		; 16 colours
SPcoLoop:
	di
	ld	a,(hl)
	inc	hl
	out	(#0x99),a	; colour Nr.
	ld	a, #128+#16
	out	(#0x99),a       
	ld	a,(hl)		; red
	inc	hl
	inc	hl
	sla	a
	sla	a
	sla	a
	sla	a		; bits 4-7
	ld	c,a
	ld	a,(hl)		; blue bits 0-3
	dec	hl
	or	c
	out	(#0x9A),a
	ld	a,(hl)		; green bits 0-3
	inc	hl
	inc	hl
	out	(#0x9A),a
	ei 
	djnz	SPcoLoop
	ret
	
;-----------------------------------------------
;	Sets palette, provide table pointer
;
_RestorePalette::
	ld	hl, #__msx_palette
	jr	_isetpalette

	;.area	_XDATA
	
;---------------------------------------------------
;        colour  R  G  B   bright 0..7   Name
;---------------------------------------------------
__msx_palette:
	.db #0,  #0,#0,#0		;transparent
	.db #1,  #0,#0,#0		;black
	.db #2,  #1,#6,#1		;bright green
	.db #3,  #3,#7,#3		;light green
	.db #4,  #1,#1,#7		;deep blue
	.db #5,  #2,#3,#7		;bright blue
	.db #6,  #5,#1,#1		;deep red
	.db #7,  #2,#6,#7		;light blue
	.db #8,  #7,#1,#1		;bright red
	.db #9,  #7,#3,#3		;light red
	.db #10, #6,#6,#1		;bright yellow
	.db #11, #6,#6,#3		;pale yellow
	.db #12, #1,#4,#1		;deep green
	.db #13, #6,#2,#5		;purple
	.db #14, #5,#5,#5		;grey
	.db #15, #7,#7,#7		;white


;-----------------------------------------------
;  Sets R,G,B Parameters of One Color 
;  SetSC5ColorPalette(char ColorNumber, char Red, char Green, char Blue)
;  Eric Boez 2019
;

_SetColorPalette::
	push ix								; IX est un registre CPU. il est utilisé par SDCC. On doit donc le sauvegarder dans la pile  avant de l'utiliser
	ld ix,#0							;
	add ix,sp 							; SP est un registre qui contient l'adresse du dernier éléments empilé dans la pile

	ld a,4(ix)  						; On récupère le 4eme byte après le dernier élément empilé. Ce qui correspond à la première variable entrée dans la fonction. : ColorNumber, et on la mets dans le regsitre a
	ld h,5(ix)  						; Idem pour la varaible entrrée Red
	ld d,6(ix)  						; idem pour le Green
	ld e,7(ix)  						; idem pour le blue
	pop ix 								; On a plus besoin de IX, on remet le registre dans son état initiale

	      			
	di 									; On desactive les interuptions
	out	(#0x99),a	 					; On envois sur le port 0x99 (qui correspond à un port du VDP) la valeur a 
	ld	a, #128+#16 					; 
	out	(#0x99),a        				; On dit au VDP de passer sur un autre registre #16
	 
	ld a, h  		 					; On charge h qui contient la valeur Red dans a
	sla a 								; On décale les bits pour passer de ça : 00000111 à ça 011100000
	sla a
	sla a 
	sla a
	or e                             	; On ajoute la valeur de Blue, ce qui va donner quelque chose commme ça : 01110111

	out	(#0x9A),a 						; On envois ça au VDP sur le port 0x99

	ld a, d   							; on charge la valeur de Green
	out	(#0x9A),a 	 					; Et on l'envois au VDP
	ei
	ret 
