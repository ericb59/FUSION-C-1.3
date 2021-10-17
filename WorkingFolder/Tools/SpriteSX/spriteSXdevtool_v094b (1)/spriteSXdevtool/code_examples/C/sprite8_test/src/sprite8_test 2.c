/* =============================================================================
   sprite8_test.c
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
  setSpritesSize(0);
  setSpritesZoom(false);
  
  setSprites();
  //fillVRAM(BASE10, 768, 32);
  
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
124,254,146,254,214,254,198,254,
124,254,146,254,214,254,198,254,
124,254,146,254,214,254,198,254,
126,129,129,149,129,141,129,129,
126,129,129,149,129,157,129,129,
129,126,126,116,126,112,126,126,
126,129,129,139,129,143,129,129,
131,1,109,1,41,1,57,1};

  //vpoke_block(BASE14,SPRITE_DATA,65); //64 = 8 sprites *8 + 1
  copyToVRAM((uint) SPRITE_DATA,BASE14,64);
  
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