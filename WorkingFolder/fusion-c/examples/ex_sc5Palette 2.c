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
|                                            FUSION-C v1.1  |
\___________________________________________________________/
*/
// Example : Screen 5 Color palette
// 
// Works on MSX2 and upper
// 
//
//
// 
//
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_graph2.h"

 
void main(void)
{ 
  int i,x,y;

    char mypalette[] = 
    {
    0, 0,0,0,
    1, 2,1,1,
    2, 6,5,4,
    3, 5,4,3,
    4, 5,5,3,
    5, 6,5,3,
    6, 7,6,4,
    7, 3,2,1,
    8, 7,5,2,
    9, 6,4,2,
    10, 4,3,2,
    11, 6,0,1,
    12, 5,3,2,
    13, 3,3,2,
    14, 3,1,0,
    15, 6,6,6
  };

  Screen(5);
  SetColors(0,0,0);
  SetPalette((Palette *)mypalette);
  
  x=10;
  y=10;
  
  for ( i = 0; i < 16; ++i)
  {
    BoxFill( x*i, 100, x*i+15, 140, i, 0);
  }

WaitForKey();
Screen(0);
Exit(0);

}
