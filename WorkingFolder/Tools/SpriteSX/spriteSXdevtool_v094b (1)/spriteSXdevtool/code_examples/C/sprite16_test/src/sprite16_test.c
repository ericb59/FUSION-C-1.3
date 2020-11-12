/* =============================================================================
   sprite16_test.c
   v1.0 (27 February 2014)
   Description:
    test sprite 8x8 from spriteSX
============================================================================= */

#include "../include/newTypes.h"
#include "../include/VDP_TMS9918.h"
#include "../include/VDP_SPRITE.h"

#define _CHKRAM 0x0000
#define _CALSLT 0x001C
#define _CHGET  0x009F
#define _GTSTCK 0x00D5
#define _GTTRIG 0x00D8
#define _SNSMAT 0x0141
#define _KILBUF 0x0156

#define EXPTBL 0xFCC1


void setSprites();
void showSprites();
byte inkey();

void main(void) {
  
  color(15,1,1);    
  screen(2);
  setSpritesSize(1);//16x16
  setSpritesZoom(false);
  
  setSprites();
  
  showSprites();
  
  inkey();  
}


void showSprites()
{
  byte N=8;
  byte X=0,Y=0;
  byte i=0;
  
  for(i=0;i<N;i++)
  {
    putSprite(i, X*16, Y*16, i+2, i);
    X++;
    if(X==4)
    {
      X=0;
      Y++;
    }
  }

  return;
}

void setSprites()
{
// faces_x8

// SPRITE DATA
unsigned char SPRITE_DATA[]={
15,31,61,63,123,124,191,191,159,239,111,31,15,5,5,29,
192,224,96,192,64,128,128,132,134,222,192,192,128,0,0,192,
5,7,26,46,111,91,92,91,95,88,111,45,22,2,2,6,
64,192,184,212,212,106,234,106,234,106,212,212,248,64,64,96,
3,7,79,207,77,79,44,30,63,63,63,63,31,2,2,6,
192,226,230,226,162,244,56,124,254,254,254,252,248,64,64,96,
5,30,63,111,87,110,63,0,7,5,7,4,6,3,2,6,
96,248,244,234,118,190,124,0,224,96,224,32,96,192,64,96,
5,7,31,63,127,127,127,125,127,127,120,63,31,4,4,12,
64,192,240,248,252,252,252,124,252,252,60,248,240,64,64,96,
7,31,63,63,127,113,127,127,127,126,62,63,31,7,2,6,
224,248,252,252,254,142,254,254,254,126,124,252,248,224,64,96,
5,30,63,111,87,110,63,0,7,5,7,4,6,3,2,6,
96,248,244,234,118,190,124,0,224,96,224,32,96,192,64,96,
0,7,31,63,127,113,255,255,123,124,63,31,7,2,2,6,
0,224,248,252,254,142,255,255,222,62,252,248,224,64,64,96};


  copyToVRAM((uint) SPRITE_DATA,BASE14,256);
  
  return;
}


/* ===========================================================================
espera a que se pulse una tecla
One character input (waiting)
devuelve el valor de la tecla
=========================================================================== */
byte inkey(){
__asm   
   call    _CHGET
   
   ld l,a

__endasm;
}