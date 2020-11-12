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
|                 E X A M P L E  C O D E                    |
|                                            FUSION-C v1.0  |
\___________________________________________________________/
*/
// Example : Print and Input test
// 
// Works on MSX1 and upper

// 
//
#include "fusion-c/header/msx_fusion.h"


void main (void)
{
   char *text="FUSION-C Ready !";
   char text_input[20];

   Cls();
   Print (text);
  
  Locate (3,5);
  Print ("What is your surname ?\a");
  InputString(text_input,20);

  Print ("Nice to meet you \t:");
  Print (text_input);

  Exit(0);
 
}