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
|  TURBOMODE
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
/* TURBOMODE               Panasonic MSX2+ Turbo Mode.       */
/* --------------------------------------------------------- */
void TurboMode(char mode)                                                        //  Only works on Panasonic FS-A1WSX, FS-A1WX, FS-A1FX. 1: To activate  0: To desactivate
{
      mode+=128;
      OutPort(0x40,8);
      if (InPort(0x40)==247)
      {

        OutPort(0x41,129 - mode);
      }
}
