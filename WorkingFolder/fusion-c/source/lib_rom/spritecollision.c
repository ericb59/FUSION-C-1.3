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
|                C   S O U R C E   C O D E                  |
|         compilation : > sdcc -mz80 -c  msx_misc.c         |
|                                                           |
\___________________________________________________________/
*/ 
/*    spritecollision 
|     Detect  Sprite collision
|     2018/2019/2020 Eric Boez
*/
#define __FUSIONC 2020 
#include "../../header/msx_fusion.h"


int SpriteCollisionX(void)
{
	return(((VDPstatus(4) << 8) | (VDPstatus(3) & 0xff))-12);
	
}

int SpriteCollisionY(void)
{
	return(((VDPstatus(6) << 8) | (VDPstatus(5) & 0xff))-8);
	
}

