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
|                   V1.0 - 09-10-11 2018                    |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|                C   S O U R C E   C O D E                  |
|                                                           |
|              CIRCLES FOR MSX1 Screen mode 2               |
\___________________________________________________________/
*/

#include "../../header/vdp_graph1.h"

void SC2Circle(int x0, int y0, int radius, int color)
{
    int x = radius;
    int y = 0;
    int err = 0;
 
    while (x >= y)
    {
        SC2Pset(x0 + x, y0 + y, color);
        SC2Pset(x0 + y, y0 + x, color);
        SC2Pset(x0 - y, y0 + x, color);
        SC2Pset(x0 - x, y0 + y, color);
        SC2Pset(x0 - x, y0 - y, color);
        SC2Pset(x0 - y, y0 - x, color);
        SC2Pset(x0 + y, y0 - x, color);
        SC2Pset(x0 + x, y0 - y, color);
     
        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
     
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

void SC2CircleFilled(int x0, int y0, int radius, int color)
{
    int x = radius;
    int y = 0;
    int xChange = 1 - (radius << 1);
    int yChange = 0;
    int radiusError = 0;
    int i;

    while (x >= y)
    {
        for ( i = x0 - x; i <= x0 + x; i++)
        {
            SC2Pset(i, y0 + y,color);
            SC2Pset(i, y0 - y,color);
        }
        for ( i = x0 - y; i <= x0 + y; i++)
        {
            SC2Pset(i, y0 + x,color);
            SC2Pset(i, y0 - x,color);
        }

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
}