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
// Pattern Rotation demo
// & Sprites Movements
//
// Works on MSX1 and Upper 
// 
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"
#include <stdio.h>

static FastSPRITE sprite[32];

typedef struct {
    signed char DirX;        
    signed char DirY; 

} DirSPRITE;

static DirSPRITE Direction[32];


char TempBuffer[64*8];
char TempRotation[64*8];
char y[32];

void main(void)
{
    char i,j,x,my;
    unsigned int tilesAdr,SpriteAdr;

    Screen(1);

    Cls();

    for ( i = 65; i < 128; ++i)
    {
        printf ("%c",i);
    }

    tilesAdr=0x0;           // Characteres pattern adress
    SpriteAdr=0x3800;       // Sprite pattern address

    CopyVramToRam(tilesAdr+64*8, TempBuffer, 8*64);         // Copy Character pattern to TempBuffer

    for (j = 0; j < 4; ++j)
    {
            Beep();
            Locate (0,15);
            Print("Press A Key to continue");
            WaitKey();
            for ( i = 0; i < 64; ++i)
            {
                PatternRotation(TempBuffer+i*8,TempRotation+i*8,0); // Rotate each of the 8x8 pattern composing the charater to the right. And store all data inside TempRotation buffer
            }
            CopyRamToVram(TempRotation, tilesAdr+64*8, 64*8);       // Copy Rotated characters patterns to VRAMa
            MemCopy( TempBuffer, TempRotation, 64*8 );              // Copy the result to TempBuffer
    }

    //Cls();

    CopyRamToVram(TempBuffer, SpriteAdr, 64*8);                   // Copy Characters pattern to Sprite Pattern
   
    Beep();
    WaitKey();
    x=0;
    my=100;
    for ( i = 0; i < 32; ++i)
    {
        my+=2;
        y[i]=my;
        sprite[i].pat=i;
        sprite[i].spr=i;
        sprite[i].x=x+i*8;
        sprite[i].y=y[i];
        sprite[i].col=8;

        Direction[i].DirY=-1;


        fPutSprite(&sprite[i]);
    }
    Beep();
    WaitKey();
    Locate (0,15);
    Print("Press ESC Key to stop       ");
    while (Inkey()!=27)
    {
        for ( i = 0; i < 32; ++i)
        {

            sprite[i].y+= Direction[i].DirY;
            fPutSprite(&sprite[i]);

            if (sprite[i].y>190 || sprite[i].y<2)
            {
                Direction[i].DirY*=-1;
            }
        }
    }




 



    Exit(0);
}