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
// PatternRotation, Pattern Flip example
// Any 8x8 pixel pattern can be modified on the fly
//
// Works on MSX1 and Upper 
//

#include "fusion-c/header/msx_fusion.h"
#include <stdio.h>

// Main 
void main(void)							
{

	unsigned int vram_adr;	
  unsigned int i;		

  unsigned char buffer[2048];
  unsigned char buffer2[2048];
 
  SetColors(15,1,7);
	Screen(1);							
	vram_adr=Peekw(0xF3C1);				            // Read the adress where charaters data are stored in VRAM (It may change, but the correct value is alway at 0xF3B7)

	printf("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ\n\r");	

	

  printf("\n\rNow we will rotate all the letters  to a 90 angle... Press a Key");
  

 CopyVramToRam( vram_adr, buffer, 2048);        // Copy the actual font patterns to a buffer
 
 for (i = 0; i < 255; ++i)
 {
   PatternRotation(buffer+i*8,buffer2+i*8,0);   // Rotate each character of the font stored in Buffer, and put them in buffer2

 }
 Beep();
 WaitKey();
 CopyRamToVram(buffer2, vram_adr, 2048);        // Copy the new font to the VRAM 
 WaitKey();

 CopyRamToVram(buffer, vram_adr, 2048);        // Copy back original font
 printf("\n\rNow we will flip horizontally all letters... Press a Key");
 WaitKey();
 for (i = 0; i < 255; ++i)
 {
   PatternHFlip(&buffer+i*8,&buffer2+i*8);      // Flip all letters

 }
 Beep();
 CopyRamToVram(buffer2, vram_adr, 2048);      // Copy the new font to the VRAM
 WaitKey();

 CopyRamToVram(buffer, vram_adr, 2048);   // Copy back original font
 printf("\n\rNow we will flip vetically all letters ... Press a Key");

 WaitKey();
 for (i = 0; i < 255; ++i)
 {
   PatternVFlip(&buffer+i*8,&buffer2+i*8);    // Flip all letter Up/down

 }
 Beep();
 CopyRamToVram(buffer2, vram_adr, 2048);    // Copy the new font to the VRAM
 WaitKey();
 CopyRamToVram(buffer, vram_adr, 2048);     // Copy back original font


Exit(0);
  
}