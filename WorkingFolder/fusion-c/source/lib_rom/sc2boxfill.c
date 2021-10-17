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
|	 SC2BoxFill	
|     2019 Eric Boez
|    
*/


#include "../../header/vdp_graph1.h"
#include <stdlib.h>

void SC2BoxFill (unsigned int x1, unsigned int y1, unsigned int x2, int y2, char color )
{
  int i;

  for (i=y1; i<=y2; i++)
  {
     SC2Line(x1,i,x2,i,color);
  }

}