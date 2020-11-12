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
|	 SC2BoxLine	
|     2019 Eric Boez
|    
*/


#include "../../header/vdp_graph1.h"
#include <stdlib.h>

void SC2BoxLine( unsigned int x1,  unsigned int y1,  unsigned int x2,  unsigned int y2, char color )
{
  
    SC2Line(x1,y1,x2,y1,color);
    SC2Line(x1,y1,x1,y2,color);
    SC2Line(x2,y2,x2,y1,color);
    SC2Line(x2,y2,x1,y2,color);
  

}