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
|                                            FUSION-C v1.1  |
\___________________________________________________________/
*/
// Example : Random Number generator with Real timer as Seed
// 
// Works on MSX1 and upper
// 
//
#include <stdlib.h>
#include <stdio.h>
#include "fusion-c/header/msx_fusion.h"


/* ---------------------------------
                FT_Random
           Return a Random Number 
             between a and b-1
-----------------------------------*/ 
char FT_RandomNumber (char a, char b)
{
    char random;
 
    random = rand()%(b-a)+a;  
    return(random);
}


void main(void) 
{
    char n,i;

    srand(RealTimer());              // use current clock seconds as seed in the random generator

    for(i=0;i < 10; i++)
    {
        n=FT_RandomNumber(1,101);     // Choose random number between 1 and 100 
        printf("%d,",n);
    }
 
    Exit(0);
}
 