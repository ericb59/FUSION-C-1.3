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
|                     V1.3 - 04 2020                        |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|                                                           |
\___________________________________________________________/
*/ 
/*    2019-2020 Eric Boez
|
|  VDPINTERLACE
|  
*/
#define __FUSIONC 2020 
#include "../../header/msx_fusion.h"

#define SCRMOD  0xFCAF      /* current screen mode */
#define ACPAGE  0xFAF6      /* active page number */
#define DPPAGE  0xFAF5      /* display page number */
#define ATRBAS  0xF928      /* sprite attribute table base address */
#define PATBAS  0xF926      /* sprite pattern generator table base address */





/* --------------------------------------------------------- */
/* VDPINTERLACE               Activating Interlace mode      */
/* --------------------------------------------------------- */
void VDPinterlace(char oddpage)           // Activating interlace mode. Enter the Odd page. Must be 1 or 3. 0 to cancel Interlace mode
{
  unsigned int reg2,reg9;

  reg9=Peek(0xFFE8) | 0b00001100;
  reg2=(oddpage<<5) | 0b00011111;
  if (oddpage==0)
  {
    reg9=Peek(0xFFE8) & 0b11110011;     // Cancel the interlace mode
  }
  
  Poke(0xF3E1,reg2);                    // Save Register values
  Poke(0xFFE8,reg9);
  

  VDPwrite(9,reg9);
  VDPwrite(2,reg2);

}
