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
|  VDPAlternate
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
/* VDPINTERLACE               Activating Alternate mode      */
/* --------------------------------------------------------- */
void VDPalternate(char oddpage, char OnTime, char OffTime)           // Activating Alternate mode mode. Enter the Odd page. Must be 1 or 3. 0 to cancel Alternate mode
{
  unsigned int reg2,reg13;
  if (OnTime>15)
      OnTime=15;

   if (OffTime>15)
      OffTime=15;

  reg2=(oddpage<<5) | 0b00011111;
  if (oddpage==0)
  {
    reg13=0b00000000;     // Cancel the alternate mode
  }
  else
  {
    reg13=OnTime << 4 | OffTime ;
  }
  
  Poke(0xF3E1,reg2);                    // Save Register values
  Poke(0xFFEC,reg13);
  

  VDPwrite(13,reg13);
  VDPwrite(2,reg2);

}
