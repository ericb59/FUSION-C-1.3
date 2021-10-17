; ___________________________________________________________
;/               __           _                              \
;|              / _|         (_)                             |
;|             | |_ _   _ ___ _  ___  _ __                   |
;|             |  _| | | / __| |/ _ \| '_ \                  |
;|             | | | |_| \__ \ | (_) | | | |                 |
;|             |_|  \__,_|___/_|\___/|_| |_| *               |
;|                                                           |
;|               The MSX C Library for SDCC                  |
;|                     V1.3 -  05-2020                       |
;|                                                           |
;|                Eric Boez &  Fernando Garcia               |
;|                                                           |
;|               A S M  S O U R C E   C O D E                |
;|                                                           |
;| https://github.com/Threetwosevensixseven/ayfxedit-improved|
;|                                                           |
;|          https://shiru.untergrund.net/software.shtml      |
;\___________________________________________________________/
;
;    AYFX Sound Effect Driver
;	 based on Shiru's, modified by Artrag in April 6 2014
;
;	This AYFX Replayer can play up to 3 SoundFx at the same time, over the 3 PSG Channels
;
.area _DATA
DATA_AREA: 
afxNoisePeriod: .ds 1
afxBnkAdr: .ds 2
afxAYREGS: .ds 14

; descriptors channels 11 bytes to the channel:
; 0 (2) the current address (the channel is free, if the high byte = $ 00)
; 2 (2) Time effect
; 4 (1) the volume
; 5 (1) bits of the mixer
; 6 (2) pitch period
; 8 (1) looping effect if != $00
; 9 (2) starting point if looping

afxChData: .ds 33
END_DATA_AREA:
; endmap

afxTonA= 0
afxTonB= 2
afxTonC= 4
afxNoise= 6
afxMixer= 7
afxAmplA= 8
afxAmplB= 9
afxAmplC= 10

loopingsfx= 0 ; sfx with $ up to loopingsfx (excluded) will loop, the higher $ will go once

; ------------------------------------------------- ------------- ;
; Initialization player effects. ;
; Turns off all channels , sets variables . ;
; ------------------------------------------------- ------------- ;
.area _CODE
_InitFX::

; ld hl, sfxBank_miz
; ld de,miz_buffer
; call mom_depack_rom

_StopFX::
	ld hl,#DATA_AREA
	ld b,#END_DATA_AREA-#DATA_AREA
	afxloop:
	ld (hl),#0
	inc hl
	djnz afxloop

	push ix
    ld ix,#0
    add ix,sp
    ld l,4(ix)   
    ld h,5(ix)        
    pop ix      

	inc hl
	ld (afxBnkAdr),hl 			; reserve table address offsets

	xor a
	ld (afxNoisePeriod),a

	ld hl, #afxChData 			; mark all channels as empty
	ld de, #0x00ff
	ld b, #3

	afxInit0:
	ld (hl),d
	inc hl
	ld (hl),d
	inc hl
	ld (hl),e
	inc hl
	ld (hl),e
	inc hl
	ld (hl),d
	inc hl
	ld (hl),e
	inc hl
	ld (hl),d
	inc hl
	ld (hl),d
	inc hl
	ld (hl),d
	inc hl
	ld (hl),d
	inc hl
	ld (hl),d
	inc hl
	djnz afxInit0
	ret

; ------------------------------------------------- ------------- ;
; Playback of the current frame . ;
; With no parameters . ;
; ------------------------------------------------- ------------- ;

_UpdateFX::
	push ix
	
	; ROUT
	;out buffered sfx data
	xor a ; --- FIXES BITS 6 AND 7 OF MIXER ---
	ld hl,#afxAYREGS+afxMixer
	set 7,(hl)
	res 6,(hl)
	ld c,#0xA0
	ld hl,#afxAYREGS
	afxsfxloop:
	out (c),a
	inc c
	outi
	dec c
	inc a
	cp #13
	jr nz,afxsfxloop
	;/out buffered sfx data

	

	ld ix, #afxChData
	ld b, #3
	afxFrameLoop:
	ld a, 1(ix) ; significant byte addresses effect
	or a ; if 0, the channel is not active
	jr z, afxFrameChSkip
	ld h, a
	ld l, 0(ix) ; low byte address effect

	ld a, (hl) ; read information bytes
	inc hl

	ld c, a
	ld 5(ix), a ; remember bits mixer
	and #15
	ld 4(ix), a ; remember volume

	bit 5 , c ; changing pitch period
	jr z, afxFrameNoTone

	ld a, (hl) ; remember period
	inc hl
	ld 6(ix), a
	ld a,(hl)
	inc hl
	ld 7(ix), a

	afxFrameNoTone:
	bit 6 , c ; period change noise
	jr z, afxFrameNoNoise
	ld a, (hl) ; period obtain
	cp #0x20 ; if it is more than 31 , the effect is over
	jr c, afxFrameNoise

	ld a,8(ix)
	and a
	jr z,afxa1
	; looping effect
	ld l,9(ix) ; restart the effect from the beginning
	ld h,10(ix)

	ld 0(ix), l ; remember address
	ld 1(ix), h

	inc 2(ix) ; increment the playing time
	jr nz, afxFrameLoop
	inc 3(ix)
	jr afxFrameLoop

	afxa1: ; no loop
	xor a ; vanishes high byte address and the volume
	ld 1(ix), a
	ld 4(ix), a
	jr afxFrameChSkip

	afxFrameNoise:
	inc hl ; remember period noise
	ld (afxNoisePeriod), a

	afxFrameNoNoise:

	ld 0(ix), l ; remember address
	ld 1(ix), h

	inc 2(ix) ; increment the playing time
	jr nz, afxFrameChSkip
	inc 3(ix)

	afxFrameChSkip:
	ld de, #11 ; the next channel
	add ix, de
	djnz afxFrameLoop

	; ld a, (afxAYREGS + AmplA)
	; ld c, a
	ld a, (#afxChData+0 * 11 +4)
	; cp c
	; jr c, afxSkipCh0
	ld (#afxAYREGS + afxAmplA), a
	ld a, (#afxChData +0 * 11 + 6 )
	ld (#afxAYREGS + afxTonA +0), a
	ld a, (#afxChData +0 * 11 +7 )
	ld (#afxAYREGS + afxTonA +1), a

	ld a, (#afxAYREGS + afxMixer)
	and #0b11110110
	ld c, a
	ld a, (#afxChData +0 * 11 + 5 )
	rra
	rra
	rra
	rra
	and #0b00001001
	or c
	ld (#afxAYREGS + afxMixer), a

	afxSkipCh0:

	; ld a, (afxAYREGS + AmplB)
	; ld c, a
	ld a, (#afxChData +1 * 11 +4)
	; cp c
	; jr c, afxSkipCh1
	ld (#afxAYREGS + afxAmplB), a
	ld a, (#afxChData +1 * 11 + 6 )
	ld (#afxAYREGS + afxTonB +0), a
	ld a, (#afxChData +1 * 11 +7 )
	ld (#afxAYREGS + afxTonB +1), a

	ld a, (#afxAYREGS + afxMixer)
	and #0b11101101
	ld c, a
	ld a, (#afxChData +1 * 11 + 5 )
	rra
	rra
	rra
	and #0b00010010
	or c
	ld (#afxAYREGS + afxMixer), a

	afxSkipCh1:

	; ld a, (afxAYREGS + AmplC)
	; ld c, a
	ld a, (#afxChData +2 * 11 +4)
	; cp c
	; jr c, afxSkipCh2
	ld (#afxAYREGS + afxAmplC), a
	ld a, (#afxChData +2 * 11 + 6 )
	ld (#afxAYREGS + afxTonC +0), a
	ld a, (afxChData +2 * 11 +7 )
	ld (#afxAYREGS + afxTonC +1), a

	ld a, (#afxAYREGS + afxMixer)
	and #0b11011011
	ld c, a
	ld a, (#afxChData +2 * 11 + 5 )
	rra
	rra
	and #0b00100100
	or c
	ld (#afxAYREGS + afxMixer), a

	afxSkipCh2:

	ld ix, #afxChData
	ld a,5(ix) ; +0 * 11 +5
	and 16(ix) ; +1 * 11 +5
	and 27(ix) ; +2 * 11 +5
	rla
	jr c, afxNoNoise
	ld a, (afxNoisePeriod)
	ld (#afxAYREGS + afxNoise), a
	afxNoNoise:
	pop ix
	ret

; ------------------------------------------------- ------------- ;
; Running effect on the free channel. In the absence ;
; free channels selects the most long -sounding . ;
; Input : A = number of effect 0 .. 255 ;
; ------------------------------------------------- ------------- ;

_PlayFX::
	push ix

    ld ix,#0
    add ix,sp
    ld a,4(ix) 

	push iy
	ex af,af'

	ld ix, #afxChData ; empty channel search
	ld de,#11
	ld b,#3
	afxb1: 
	;ld a,1(ix)
	or a
	jr z,afxfreechan
	add ix,de
	djnz afxb1
	; no free channels

	ld iy, #afxChData ; search the channel that plays from more time
	ld ix, #afxChData ; in case of 3 looping channels use channel A
	ld de, #0 ; in de the longest time while searching
	ld bc,#11
	ld a, #3
	afxPlay0:
	inc 8(iy)
	dec 8(iy)
	jr nz, afxPlay1 ; skip channels with looping effects
	ld l, 2(iy) ; compare time channel with the highest
	ld h, 3(iy)
	sbc hl,de
	jr c, afxPlay1
	add hl,de ; remember the longest time
	ex de,hl
	push iy ; remember the address of the channel in ix
	pop ix
	afxPlay1:
	add iy,bc
	dec a
	jr nz,afxPlay0
	; expect to address the effect
	afxfreechan:
	ld h, a
	ex af,af'
	ld l, a
	add hl, hl
	ld bc, (afxBnkAdr) ; address offset table effects
	add hl, bc
	ld c, (hl)
	inc hl
	ld b, (hl)
	add hl, bc ; effect address obtained in hl

	ld 0(ix), l ; record in the channel descriptor
	ld 1(ix), h
	ld 2(ix), #0 ; reset execution Time
	ld 3(ix), #0

	ld 8(ix), #0 ; reset looping flag

	cp #loopingsfx ; up to sfx $loopingsfx-1 will loop
	jr nc,afxc1

	ld 8(ix), #-1 ; set looping flag
	ld 9(ix), l ; record in the channel descriptor for later use
	ld 10(ix), h

	afxc1:
	pop iy
	pop ix
	ret

