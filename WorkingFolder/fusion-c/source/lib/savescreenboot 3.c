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
|                     V1.3 - 05 2020                        |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|                                                           |
\___________________________________________________________/
*/ 
/*    2019-2020 Eric Boez
|
|  SaveScreenBoot
|
*/
#define __FUSIONC 2020 
#include "../../header/msx_fusion.h"

/* ------------------------------------------------------------*/
/*   SAVESCREENBOOT       Save Screen parameters to MSX2 SRAM   */
/*                                                              */ 
/* -------------------------------------------------------------*/

void SaveScreenBoot(char nb)
{   

    char value,i;
    const unsigned int address[]={0b0000000000100001,0b0000000000100010,0b0000000000100110,0b0000000000101000,0b0000000000100111,0b0000000000100011,0b0000000000100100,0b0000000000100101};
    char data[8];

    REGDATA Register;

     // Screen1 Width
    value=_WidthScreen1; 
    if (_ScreenMode==0)
    {
             //Screen 0 width
            value=_WidthScreen0; 
    }
    data[0]=ReadAdjust(0);
    data[1]=ReadAdjust(1);
    data[2]=_ForegroundColor;
    data[3]=_BorderColor;
    data[4]=_BackgroundColor;
    data[5]=_ScreenMode;
    data[6]=value & 0b00001111;
    data[7]=(value >> 4) & 0b00000011;
    if (nb>8 || nb<1)
        nb=8;
    for (i = 0; i < nb; ++i)
    {
         Register.IX=0x01F9;
         Register.BC=address[i];           // Save X Screen Offset
         Register.AF=data[i];
         CallSub(&Register);
    }
         
}