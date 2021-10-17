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
|   BoxFill
|
|
*/


#include "../../header/vdp_graph2.h"
#define       RPeek( address )     ( *( (volatile unsigned char*)(address) ) )

void BoxFill (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, char color, char op )
{
    char scmode;

    scmode=RPeek (0xFCAF);

    if (op==0 && scmode > 7)
    {

        HMMV( x1, y1, x2-x1, y2-y1, color);   // Using HMMV only with Scree8 and no OP

    } 
    else
    {
        LMMV( x1, y1, x2-x1, y2-y1, color, op);
    }

}