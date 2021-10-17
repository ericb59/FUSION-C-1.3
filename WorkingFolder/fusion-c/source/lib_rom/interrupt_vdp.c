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
|                     V1.3 - 12-12-2020 	                |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|                 C     S O U R C E   C O D E               |
|                                                           |
|                                                           |
\___________________________________________________________/
*/
/*  
|	VDP Interrupt functions   For ROM
|     Eric Boez 2020
*/
#define __FUSIONC 2020 
#include "../../header/msx_fusion.h"

 // H.TIMI
#define VDP_HOOK 0xFD9F



// Interruption set up routines
void InitVDPInterruptHandler(unsigned int Routine)
{
      Poke(VDP_HOOK,0xc3);
      Pokew(VDP_HOOK+1,(unsigned int)Routine);
}

void EndVDPInterruptHandler(void)
{
     
      Poke(VDP_HOOK,0xc9);
      Poke(VDP_HOOK+1,0xc9);
      Poke(VDP_HOOK+2,0xc9);

}


