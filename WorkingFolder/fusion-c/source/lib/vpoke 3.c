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
|  Vpoke
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
/* VPOKE                                                     */
/* --------------------------------------------------------- */

void Vpoke( unsigned int address,  char data ) {
  
    SetVDPWrite( address );
    DisableInterrupt();
    OutPort( 0x98, data );
    EnableInterrupt();
}

