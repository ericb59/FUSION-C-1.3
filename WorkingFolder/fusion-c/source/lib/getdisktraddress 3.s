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
; Call DOS functions
; 1995, SOLID MSX C & SDCC port 2015
; 2019-2020 Eric Boez
;
;
;	GetDiskTrAddress

;----------------------------
;   MODULE  GetDiskTrAddress
;   
;	unsigned int  	GetDiskTrAddress(void);
;	Return Current disk transfert address
;
;
;
 .area _CODE
 
 
  _GetDiskTrAddress::
	  push  ix
	  ld c,#0x57
	  call  #5
	  pop ix
	  ld h,d
	  ld l,e 
	
	  ret