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
|         compilation : > sdcc -mz80 -c  msx_misc.c         |
|                                                           |
\___________________________________________________________/
*/
/*  ReadMsxtype
|    
|     2018 Eric Boez
*/
#define __FUSIONC 2020 
#include "../../header/msx_fusion.h"


char ReadMSXtype(void)
{
        unsigned char *p;
        unsigned char bios_slot;
        REGDATA Register;

        p = (char *) 0xFCC0;
        bios_slot = p[0];   //gives you bios slot/sublot
        Register.IY=bios_slot;  //bios slot/subslot
        Register.IX=0x000C;   //  
        Register.HL=0x002D; 
        Register.AF=bios_slot; 
        CallBios(&Register);
        return(Register.AF);
}

