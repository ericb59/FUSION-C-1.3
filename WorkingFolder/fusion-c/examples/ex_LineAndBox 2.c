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
|                                            FUSION-C v1.2  |
\___________________________________________________________/
*/
// Example : Draw Box and line on Screen 7
// 
// Works on MSX2 and upper  
//
//
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_graph2.h"


void main(void)
{
    unsigned int i,j;

    SetColors(15,5,7);
    Screen(7);
    SetColors(15,5,7);

    BoxLine(50,100,500,200,2,255);
    BoxLine(50,100,500,200,11,0);
   
    BoxFill(250,20,512,100,12,0);
    BoxFill(250,30,512,50,12,2);
    BoxFill(250,40,512,60,12,3);
    BoxFill(250,50,512,70,10,2);


  for (j=10; j<30;j++)
  {
    for ( i = 10; i < 500; ++i)
    {
      Pset(i,j,6,0);
    }
}


    
     // now Drawing same lines
      for ( i = 0; i < 511; ++i)
      {
         Line(256,106,i,0,10,0);
         Line(256,106,i,211,9,0);
      }
      for ( i = 0; i < 211; ++i)
      {
         Line(256,106,0,i,6,0);
         Line(256,106,511,i,12,0);
      }

    
    
    WaitKey();
    Screen(0);


    Exit(0);
}