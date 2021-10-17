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
| 	  GetOSVersion For MSX-DOS
|
|	Need io.h
|
*/

#define FUSION 2020
#include "../../header/io.h"


char GetOSversion(void)
{
__asm
  
  call  _OS_version
  ld  h, #0
  ld  a,(#__os_ver)
  ld  l, a
  ret
__endasm;  
}