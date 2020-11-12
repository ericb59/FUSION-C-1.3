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
|                                            FUSION-C v1.3  |
\___________________________________________________________/
*/
// Exampple : SetAdjust
//
//  Works on MSX1 and Upper 
//

#include "fusion-c/header/msx_fusion.h"
#include <stdio.h>


void main(void)							
{
signed char x,y;
char j;

x=y=j=0;
SetColors(15,4,7);
Screen(1);

Locate (0,0);
Print("Use arrow Keys to Adjust \n Screen");


 while (Inkey()!=27)
 {
      j=JoystickRead(0);
     
  
        
      switch (j)
      {
          case 1:
            y--;
          break;

          case 3:
            x++;
          break;

          case 5:
            y++;
          break;

          case 7:
            x--;
          break;

      }
         if (x<-8)
            x=-8;
         if (x>7)
            x=7;

         if (y<-8)
            y=-8;
         if (y>7)
            y=7;

        Locate (0,2);
        printf(" %d , %d ",x,y);

        SetAdjust(x,y);
    
 }

 
 Exit(0);
  
}