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
|                   V1.0 - 09-10-11 2018                    |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|					    	P S G 							|
|                                                           |
\___________________________________________________________/
|
|     2006/11/25    t.hara  
|     2018 Eric Boez
| 	  2018 mvac7/303bcn
|
|	PSGread
|
*/

#define FUSION 2019
#include "../../header/msx_fusion.h"
#include "../../header/psg.h"

//intern MSX AY
#define AY0index 0xA0
#define AY0write 0xA1
#define AY0read  0xA2
//AY from MEGAFLASHROM-SCC+
//#define AY1index 0x10
//#define AY1write 0x11
//#define AY1read  0x12

/* --------------------------------------------------------- */
/*  PSG register read                                        */

 char PSGread(  char psgreg ) {

    OutPort( 0xA0, psgreg );
    return InPort( 0xA2 );
}