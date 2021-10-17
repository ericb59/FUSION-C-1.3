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
|   polygon
|
|
*/


#include "../../header/vdp_graph2.h"

void Polygon (unsigned int num_vertices, unsigned int *vertices, char color, char OP) 
{
  int i;

  for(i=0;i<num_vertices-1;i++)
  {
    Line(vertices[(i<<1)+0], vertices[(i<<1)+1],  vertices[(i<<1)+2],  vertices[(i<<1)+3],color,OP);
  }
     Line(vertices[0],  vertices[1],   vertices[(num_vertices<<1)-2],  vertices[(num_vertices<<1)-1],   color, OP);
}
