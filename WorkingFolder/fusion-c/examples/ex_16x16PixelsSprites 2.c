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
// How to set 16x16 Sprites
//
// Works on MSX1 and Upper 
//

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"

/* --------------------------------------------------------- */
/*  SPRITE test                        */
/* ========================================================= */

static const unsigned char enemigo1[] = {
    0x00,0x00,0x78,0x48,0x3F,0x23,0x2A,0x3E,0x1C,0x9F,0x5F,0x34,0x1F,0x1F,0x06,0x00,0x00,0x00,0x1E,0x1A,0xFC,0xC4,0x54,0x7C,0x38,0xF9,0xFA,0x4C,0xF8,0xF8,0x60,0x00
};

static const unsigned int p3[]={0b0000000000000000,
                        0b0000001111000000,
                        0b0000110011100000,
                        0b0001100011100000,
                        0b0011000011100000,
                        0b0000000011100000,
                        0b0000000011100000,
                        0b0000000011100000,
                        0b0000000011100000,
                        0b0000000011100000,
                        0b0000011100011100,
                        0b0000111000001110,
                        0b0001110000000111,
                        0b0001110000000111,
                        0b0000011100011100,
                        0b0000000011100000};

/* --------------------------------------------------------- */
void main( void ) {
    char x;
    char y;


    x=0;
    y=50;

  if(ReadMSXtype()==3)  // IF MSX is Turbo-R Switch CPU to Z80 Mode
    {
       ChangeCPU(0);
    }
  //
  Screen(1);
  
  SpriteReset();

  SpriteDouble();
  
  // The 16 x 16 pixels Sprite is made of 4 patterns

  SetSpritePattern( 0, enemigo1,32 );              // This will set in VRAM pattern 0, 1, 2 , 3


  SetSpritePattern( 4, Sprite32Bytes(p3),32 );    // This will set in VRAM pattern 4, 5, 6 , 7


  Sprite16();
  



  while (Inkey()!=27)
  {  
      x=(x+1)&255;
      EnableInterupt()
      Halt();
      PutSprite (1,0,x,y,8);
      PutSprite (2,4,x,y+40,10);
  }
  Screen(0);
  Exit(0);
}
