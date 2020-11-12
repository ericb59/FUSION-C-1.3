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
|                     V1.03 - 04-2020                       |
|                                                           |
|              Eric Boez &  Fernando Garcia                 |
|                                                           |
|      AYFX Driver . Play Sound FX sound made with          |
|                AYFX Shiru's Sound Editor                  |
|                                                           |
| https://github.com/Threetwosevensixseven/ayfxedit-improved|
|                                                           |
|          https://shiru.untergrund.net/software.shtml      |
\___________________________________________________________/
*                         (°□°)
* 
* 
*/




#ifndef _AYFX_H
#define _AYFX_H

void      InitFX(void *SndBankAddr);        // Init of the AYFX Player driver, with the address of the Sound Bank
void      PlayFX(char SoundFX);             // Play a Sound FX
void      StopFX(void);                     // Stop A sound FX
void      UpdateFX(void);                   // Part of the main loop. CUrrently playing sounds


#endif
