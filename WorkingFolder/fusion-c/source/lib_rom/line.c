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
|   Line
|
|
*/


#include "../../header/vdp_graph2.h"

void Line ( unsigned int x1,  unsigned int y1,  unsigned int x2,  unsigned int y2, char color, char OP ) 
{

    char R45;
    int dx,dy;
    unsigned int shortside,longside;

    R45=0b00000000;

    dx=x2-x1;
    dy=y2-y1;


    if (dx<0)
    {
        dx=dx*-1;
        R45=R45 | 0b00000100;
    }
   
    //////////////////////////
    if (dy<0)
    {
        dy=dy*-1;
        R45=R45 | 0b00001000;
     }
    
     //////////////////////////
    if (dy>dx)
    {
        longside=dy;
        shortside=dx;
        R45=R45 | 0b00000001;
    } 
    else
    {
        longside=dx;
        shortside=dy;
        R45=R45 | 0b00000000;
    }

    VDPLINE(x1,y1,longside,shortside,color,R45,OP);
    
}


