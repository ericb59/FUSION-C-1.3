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
|                   V1.2 - 08 2019                          |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|                                                           |
|                                                           |
\___________________________________________________________/
*/
/*  width
|    
|     2018 Eric Boez
*/
#define __FUSIONC 2020 
#include "../../header/msx_fusion.h"


// Width of screen in text mode
void Width( char n)
{

    if ((*(char *)0xFCAF)==0)       // If Actual Screen Mode is 0
    {
        Poke(0xF3AE,n); // set column number for SCREEN 0
        Screen(0);
    }
    if ((*(char *)0xFCAF)==1)           // If Actual Screen mode is 1
    {
        Poke(0xF3AF,n); // set column number for SCREEN 1
        Screen(1);
    }
}
