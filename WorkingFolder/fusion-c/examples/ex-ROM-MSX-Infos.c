/*
 ___________________________________________________________
/               __           _                              \
|              / _|         (_)                             |
|             | |_ _   _ ___ _  ___  _ __                   |
|             |  _| | | / __| |/ _ \| '_ \                  |
|             | | | |_| \__ \ | (_) | | | |                 |
|             |_|  \__,_|___/_|\___/|_| |_| *               |
|                                                           |
|               The MSX C Library for SDCC                  |
|                 E X A M P L E  C O D E                    |
|                                            FUSION-C v1.3  |
\___________________________________________________________/
*/
// This code example shows how to retrieve information from MSX ROM
// 
//
// Works on MSX1 and Upper 
// 

#define __SDK_ADDRCODE__ 0x405b
#define __SDK_ADDRDATA__ 0xC000
#define __SDK_MSXVERSION__ 2
#define __SDK_CRT0__ crt0.rel
#define __SDK_EXT__ ROM 
#define __SDK_ROMSIZE__ 0x8000
#define __SDK_OPTIMIZATION__ 1
 
#include "fusion-c/header/msx_fusion.h"

#include <stdio.h>

typedef struct {
    char charset;           // Act as Input. Must be set to the joyport to read
    char date_format;
    char default_frequency;
    char keyboard_type;
    char basic_version;
    char msx_version;
    char internal_midi;

} MSX_INFO;

MSX_INFO MSXdata;

// This assembler Routine is reading Variables located in ROM
// This version only works for ROM

void ReadMSXinfo(void *data) __z88dk_fastcall
{
    __asm
            push hl         ; save HL 
            ld a,(#0xFCC1)
            ld hl,#0x2B       ; Adresse to read 
            di
            call #0x000c      ; Read from slot
            ei

            pop hl          ; retrieve DATA adress
                    
            ld   b,a          ; save result to b
            and #0b00001111   ; Extract Character Set 
           
            ld (hl),a         ; Send Character Set 

            ld a,b
            rrca
            rrca
            rrca
            rrca
            and #0b00000111   ; Extract Date Format
            inc hl
            ld (hl),a      ; send Date Format 
            ld a,b 
            rlca
            and #0b00000001   ; extract  frequency
            inc hl
            ld (hl),a

            push hl         ; save HL 
            ld a,(#0xFCC1)
            ld hl,#0x2C       ; Adresse to read 
            di
            call #0x000c      ; Read from slot
            ei

            pop hl            ; retrieve DATA adress
                    
            ld   b,a          ; save result to b
            and #0b00001111   ; Extract Keyboard type
            inc hl
            ld (hl),a         ; Send Keyboard Type 
            ld a,b
            rrca
            rrca
            rrca
            rrca
            and #0b00001111   ; Extract Basic Version 
            inc hl
            ld (hl),a         ; send Basic Version 

            push hl           ; save HL 
            ld a,(#0xFCC1)
            ld hl,#0x2D       ; Adresse to read 
            di
            call #0x000c      ; Read from slot
            ei

            pop hl
            inc hl
            ld (hl),a         ; Send MSX VERSION

            push hl           ; save HL 
            ld a,(#0xFCC1)
            ld hl,#0x2E       ; Adresse to read 
            di
            call #0x000c      ; Read from slot
            ei

            pop hl
            inc hl
            ld (hl),a         ; Send Internal Midi



            ret

    __endasm;
}

void main (void)
{

char charset_array[3][14]={{"Japanese"},{"International"},{"Korean"}};
char date_array[3][6]={{"Y-M-D"},{"M-D-Y"},{"D-M-Y"}};
char frequency_array[2][5]={{"60Hz"},{"50Hz"}};

char Keyboard_array[7][14]={{"Japanese"},{"International"},{"French"},{"UK"},{"German"},{"USSR"},{"SPAIN"}};
char basic_array[2][14]={{"Japanses"},{"International"}};
char msx_array[4][8]={{"MSX1"},{"MSX2"},{"MSX2+"},{"Turbo-R"}};
char midi_array[2][4]={{"NO"},{"YES"}};


Screen(0);
  
ReadMSXinfo(&MSXdata);
printf ("This MSX is a ");
printf("%s",msx_array[MSXdata.msx_version]);
printf("\n\r________________");


printf("\n\r The character set is  %s",charset_array[MSXdata.charset]);
printf("\n\rThe date format is %s",date_array[MSXdata.date_format]);
printf("\n\rIts default frequency is %s",frequency_array[MSXdata.default_frequency]);
printf("\n\rIts keyboard type is %s",Keyboard_array[MSXdata.keyboard_type]);
printf("\n\rIts basic version is %s",basic_array[MSXdata.basic_version]);

printf("\n\rDoes it have internal midi ? %s",midi_array[MSXdata.internal_midi]);

if (MSXdata.internal_midi==1 && MSXdata.default_frequency==0)
{
  printf("This computer is most probably a Panasonic Turbo-r Panasonic FS A1-GT");

}


WaitKey();
Exit(0);

}