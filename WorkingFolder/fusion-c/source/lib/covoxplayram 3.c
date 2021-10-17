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
| CovoxPlayRam
|
*/

// Play Sample to Covox From RAM
void CovoxPlayRam(void *address, unsigned int length, char speed) __naked
{
  address,length,speed;
    __asm
        di
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix)                  
        ld h,5(ix)
        ld e,6(ix)                 
        ld d,7(ix)    
        ld c,8(ix)

    loop2:

        ld a,(hl)
        ld b,c
        di
        play2:
        out   (#0x91), a  
               
        wait2:                       ; Wait loop 
        nop
        djnz wait2
        inc hl
        dec de
        ld a,d
        or e
        jp nz,loop2 
        
        pop ix
        ei
    ret       

    __endasm;
}
