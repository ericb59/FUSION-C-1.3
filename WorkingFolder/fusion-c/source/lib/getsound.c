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
| 	  2018 mvac7/303bcn
|
|	SOUND
|
*/

#define AY0index 0xA0
#define AY0write 0xA1
#define AY0read  0xA2
//AY from MEGAFLASHROM-SCC+
//#define AY1index 0x10
//#define AY1write 0x11
//#define AY1read  0x12

/* =============================================================================
 GetSound(register) 

 Function : Read PSG register value
 Input    : [char] register number (0 to 13)
 Output   : [char] value 
============================================================================= */
char GetSound(char reg) __naked
{
reg;
__asm
  push ix
  ld   ix,#0
  add  ix,sp
  
  ld   a,4(ix)
  out  (#AY0index),a
  in   a,(#AY0read)
  
  ld   l,a
  
  pop  ix
  ret
__endasm;
}