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
|                                            FUSION-C v1.3  |
\___________________________________________________________/
*/
// Example : Fast Painting on MSX2
// 
// Works on MSX2 and upper

// 
//
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_graph2.h"
#include "fusion-c/header/vdp_paint.h"
#include "fusion-c/header/vdp_circle.h"

#include <stdlib.h>





void main (void)
{
    unsigned char *PaintBuffer;                 // Declaring the PaintBuffer
    int i; 

    SetColors(15,1,3);
    Screen(5);

     
    Paint_vars.MaxRam=MAXPAINT_BUFFER;        // Setting the function varaibles
    PaintBuffer=MMalloc(Paint_vars.MaxRam);   // allocate Memory for the Paint Buffer

    SetPaintBuffer(PaintBuffer);              // Initialising the Paint buffer

     
     Circle(100, 100, 30, 14,0);
     Paint(100, 100, 7);                      // paint a zone
     Circle(30,30, 10, 11,0);
     Paint(100, 1, 2);                        // paint a zone

    Beep();
    WaitKey()
    
    Cls();
    for ( i = 0; i < 255; i=i+15)
    {
      Line(i,0,i,i/4,4,0);
    }

     for ( i = 0; i < 255; i=i+5)
    {
      Line(i,210,i,(210-i/2),9,0);
    }
    BoxLine(0,0,255,211,14,0);
    Paint(1, 1, 8);                       // paint a zone
    free(PaintBuffer);                    // Free the allocated memory used by the Paint Buffer

    Beep();
    WaitKey();

    Screen(0);

    Exit(0);


}