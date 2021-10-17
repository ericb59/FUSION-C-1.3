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
|                V1.3  -  December - 2019                   |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|                                                           |
|                                                           |
\___________________________________________________________/
*/
/* 
|    functions for MSX1 Screen 2 
|	 SC2Line	
|     2019 Eric Boez
|    
*/


#include "../../header/vdp_graph1.h"
#include <stdlib.h>

void SC2Line( unsigned int x1,  unsigned int y1,  unsigned int x2,  unsigned int y2, char color)
{

    int sy,sx, er,e2,dx,dy;
    
    dx=abs(x2-x1);
    sx=-1;
    if ((int)(x1-x2)<0)
        sx=1;

    dy=abs(y2-y1);
    sy=-1;
    if ((int)(y1-y2)<0)
        sy=1;

    er=-dx;

    if ((int)(dx-dy)>0)
        er=dx;

    er=(int)(er/2);

    while (!(x1==x2 && y1==y2)){


      SC2Pset(x1,y1,color);

      e2=er;
      if ((e2+dx)>0)
      {
          er=er - dy;
         x1=x1+sx;

      }
     if ((e2-dy) < 0 )
    {
         er=er+dx;
         y1=y1+sy;
    }

  }
}