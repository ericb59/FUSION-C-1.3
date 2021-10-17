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
|                     V1.3  2019-2020                       |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|         compilation : > sdcc -mz80 -c  msx_misc.c         |
|                                                           |
\___________________________________________________________/
*/
/*  Play Sample to Covox 
|    
|     2019-2020 Eric Boez 
|
| Sample must be mono, 8bits PCM Wav file
| Exporting 8 Bits PCM file with Audacity.
| File > Export > Export to Wav
| In the File Type, Choose Other uncompressed format
| Then, choose Unsigned 8-Bit PCM in the Encoding field
| And Raw-Hader Less as Header
|
|
| CovoxPlayVRAM
|
*/

#define __FUSIONC 2020 
#include "../../header/msx_fusion.h"

// Play Sample to Covox From VRAM
void CovoxVram(unsigned int length, char speed)__naked
{
 length;speed;   

__asm
        
        push ix
        ld ix,#0
        add ix,sp
        ld e,4(ix)                  ; lenght value  Byte high
        ld d,5(ix)                  ; lenght value Byte low
        ld c,6(ix)                  ; wait value
        di
    Loop:
        
        in      a, (#0x98)          ; read Vram adress, and increment for next read

        out     (#0x91), a          ; send data to covox 

        ld b,c
        wait:                       ; Wait loop 
        nop
        djnz wait
        dec de
        ld a,d
        or e
        jp nz,Loop                  ; Loop  'lenght' times
         ei
        pop ix                          ; end 
       
    ret
        
__endasm;

}




void CovoxPlayVram(char page, unsigned int start_adress, unsigned int length, char speed)
{
    // Prepare VDP for reading data from Start_adress, in current screen mode and  defined vram page
    if( Peek( 0xFCAF ) >= 7 ) {
        VDPwriteNi( 14, (start_adress >> 14) | (page << 2) );
    }
    else {
        VDPwriteNi( 14, (start_adress >> 14) | (page << 1) );
    }
    OutPort( 0x99, (unsigned char)start_adress );
    OutPort( 0x99, (unsigned char)(start_adress >> 8) & 0x3F );
    
    // Send data to covox port #91 (Printer port)
    CovoxVram(length, speed);
             
}
