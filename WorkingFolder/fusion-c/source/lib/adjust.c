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
|  SetAdjust
|  ReadAdjust
*/
#define __FUSIONC 2020 
#include "../../header/msx_fusion.h"

#define SCRMOD  0xFCAF      /* current screen mode */
#define ACPAGE  0xFAF6      /* active page number */
#define DPPAGE  0xFAF5      /* display page number */
#define ATRBAS  0xF928      /* sprite attribute table base address */
#define PATBAS  0xF926      /* sprite pattern generator table base address */



/* --------------------------------------------------------- */
/* SETADJUST   Adjust screen offset                          */
/* --------------------------------------------------------- */
void SetAdjust(signed char x, signed char y)
{
    char value;

     // vx=x;
      if (x<0)
        x+=16;
        
    //  vy=y;
      if (y<0)
        y+=16;

      value = (y<<4) | x ;
      Poke(0xFFF1,value);     // Reg 18 Save
      VDPwrite(18,value);
    
}

/* --------------------------------------------------------- */
/* READADJUST   Read and Return screen offset                */
/* --------------------------------------------------------- */
signed char ReadAdjust(char xy) // If xy=0 returns X offset. if xy=11 Returns Y offset
{
      signed char r;
      if (xy==0)                  // Return X
      {
            r=((*(char *)0xFFF1) &0b00001111);
            if (r>7)
                r=r-16;
      } 
      else                         // Return y
      {
            r=((*(char *)0xFFF1 >> 4) &0b00001111);
            if (r>7)
                r=r-16;
      }
    return(r);

}      