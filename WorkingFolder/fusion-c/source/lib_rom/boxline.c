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
|                   V1.2a - August - 2019                   |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|          C   &   A S M    S O U R C E   C O D E           |
|                                                           |
|                                                           |
\___________________________________________________________/
*/
/* Graphics functions for MSX2 and better
|    
|     2019 Eric Boez
|    
|   Boxfline
|
|
*/


#include "../../header/vdp_graph2.h"
void BoxLine( unsigned int x1,  unsigned int y1,  unsigned int x2,  unsigned int y2, char color, char OP )
{
  if (OP==255)
  {
    BoxFill( x1, y1, x2, y2, color,0);
  }
  else
  {
    Line(x1,y1,x2,y1,color,OP);
    Line(x1,y1,x1,y2,color,OP);
    Line(x2,y2,x2,y1,color,OP);
    Line(x2,y2,x1,y2,color,OP);
  }

}