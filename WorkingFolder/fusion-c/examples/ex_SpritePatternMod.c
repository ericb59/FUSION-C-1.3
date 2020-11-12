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
// Sprites Pattern modification example
// Rotation, Flip Horizontally, flip vertically, of 8x8 or 16x16 patterns
//
// Works on MSX1 and Upper 
//
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"


static const unsigned char enemigo1c[] = {
    0x00,0x00,0x78,0x48,0x3F,0x23,0x2A,0x3E,0x1C,0x9F,0x5F,0x34,0x1F,0x1F,0x06,0x00,0x00,0x00,0x1E,0x1A,0xFC,0xC4,0x54,0x7C,0x38,0xF9,0xFA,0x4C,0xF8,0xF8,0x60,0x00
};

static const unsigned char enemigo3c[] = {
    0x20,0x21,0x36,0x08,0x14,0x1E,0x11,0xF5,0x9F,0x95,0xBF,0x54,0x94,0x24,0x48,0x90,0x04,0x84,0x6C,0x10,0x28,0x79,0x89,0xAF,0xF8,0xA8,0xFC,0x2A,0x29,0x24,0x12,0x09
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

static const  char color1[] = {13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14};
static const  char color2[] = {5 ,5,5,5,5,5,5,5,7,7,7,7,7,7,7,7};



void Wait(unsigned int cicles) {
  unsigned int i;

  for(i=0;i<cicles;i++) 
  {
   
      while(Vsynch()==0)
        {}
    }

}






void main(void)
{

    
    KeySound(0);
    SetColors(15,1,7);
    Screen(5);

    SpriteReset();
    Sprite16();
    SpriteDouble();  
   

    SetSpritePattern(0,enemigo3c,32);
    SetSpritePattern(4,enemigo1c,32);
    SetSpritePattern(8,Sprite32Bytes(p3),32);

    SetSpriteColors(0,color1);
    SetSpriteColors(1,color2);
    
    

      PutSprite(0,0,100,100,7);
      PutSprite(1,4,190,160,7);
      PutSprite(2,8,10,50,6);
    
    Cls();PutText(10,10,"Sprite 0 : 16x16 Rotation VRAM - Push a Key",0);Beep();WaitKey();
    
    Pattern16RotationVram(0,90,0);WaitKey();
    Pattern16RotationVram(0,90,0);WaitKey();
    Pattern16RotationVram(0,90,0);WaitKey();
    Pattern16RotationVram(0,90,0);WaitKey();

    Cls();PutText(10,10,"Sprite 1 : 16x16 Rotation 180° RAM - Push a Key",0);Beep();WaitKey();
    Pattern16RotationRam(4,enemigo3c,180);WaitKey();

    Cls();PutText(10,10,"Sprite 2 : 16x16 Flip Horizontally VRAM - Push a Key",0);Beep();WaitKey();
    Pattern16FlipVram(8,0,8);WaitKey();
    Pattern16FlipVram(8,0,8);WaitKey();
    Pattern16FlipVram(8,0,8);WaitKey();

    Cls();PutText(10,10,"Sprite 0 : 16x16 Flip Vertically VRAM - Push a Key",0);Beep();WaitKey();
    Pattern16FlipVram(0,1,0);WaitKey();
    Pattern16FlipVram(0,1,0);WaitKey();
    Pattern16FlipVram(0,1,0);WaitKey();

    Cls();PutText(10,10,"Sprite 0 : 8x8 Rotation VRAM - Push a Key",0);Beep();WaitKey();
    
    Pattern8RotationVram(0,90,0);WaitKey();
    Pattern8RotationVram(0,90,0);WaitKey();
    Pattern8RotationVram(0,90,0);WaitKey();
    Pattern8RotationVram(0,90,0);WaitKey();

    Cls();PutText(10,10,"Sprite 2 : 8x8 Flip Horizontally VRAM - Push a Key",0);Beep();WaitKey();
    Pattern8FlipVram(10,0,10);WaitKey();
    Pattern8FlipVram(10,0,10);WaitKey();
    Pattern8FlipVram(10,0,10);WaitKey();

    Cls();PutText(10,10,"Sprite 2 : 8x8 Flip Vertically VRAM - Push a Key",0);Beep();WaitKey();
    Pattern8FlipVram(10,1,10);WaitKey();
    Pattern8FlipVram(10,1,10);WaitKey();
    Pattern8FlipVram(10,1,10);WaitKey();


    WaitKey();  
         

    KeySound(1);
    Screen(0);
    Exit(0);
}