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
// Example : Draw circle on screen 2
//
// Works on MSX1 and upper  
//

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_graph2.h"
#include "fusion-c/header/vdp_circle.h"


 
void main(void)
{ 
    int i=255;

    Screen(2);
  for (i = 80; i > 25; --i)
  {
      SC2Circle(100, 100,i, i);
  }

WaitKey();
Screen(0);

}
