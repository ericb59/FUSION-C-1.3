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
// Example : Screen 5 Color blinking
// 
// Works on MSX2 and upper
// 
//
//
// 
//


#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_graph2.h"


// Original Palette //
char OriginalPalette[] = 
    {
    0, 0,0,0,
    1, 0,0,0,
    2, 1,6,1,
    3, 3,7,3,
    4, 1,1,7,
    5, 2,3,7,
    6, 5,1,1,
    7, 2,6,7,
    8, 7,1,1,
    9, 7,3,3,
    10, 6,6,1,
    11, 6,6,3,
    12, 1,4,1,
    13, 6,2,5,
    14, 5,5,5,
    15, 7,7,7
  };


// Wait for 1/8 second //
void wait(void)
{
   int t;

  SetRealTimer(0); 

  t=0;
  while (t<6){
    t=RealTimer(); 
  }
}

void main(void)
{ 
  int i,x,y,j;
  char r=7;
  char g=7;
  char b=7;

  // New palette definition //
    char mypalette[] = 
    {
    0, 0,0,0,
    1, 0,0,0,
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
    15, 7,7,7
  };

  // New palette for Color 15 only //
  char Col15[]={2, r,g,b};

  SetColors(0,0,0);
  Screen(5);
  VDP50Hz();

  
  SetPalette((Palette *)mypalette);
  
  x=0;
  y=10;
  // Draw rectangles of colors
  i=1;
  while (i<16)
  {
    Rect( x, y, x+15, 180, i, FILL_ALL);
    i++;
    x=x+15;
  }

  // Blinking color 1 to 15  //
  for (j=1;j<=15;j++) {
    
    r=g=b=0;
    while (i<7)
    {
      wait();
      
      r++;
      g++;
      b++;
      SetColorPalette(j, r, g, b);
      i++;
    }

    r=g=b=7;
      
    while (i>0)
    {
      wait();
      
      r--;
      g--;
      b--;
      SetColorPalette(j, r, g, b);
      i--;

    }
    SetPalette((Palette *)mypalette);
  }

Beep();
WaitKey();
RestorePalette();

Beep();
WaitForKey();
SetColors(15,4,7);
Screen(0);
Exit(0);

}
