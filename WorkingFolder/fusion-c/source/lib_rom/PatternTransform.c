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
|                   V1.3 -  04 - 2020                       |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|             A S M  &  C  S O U R C E   C O D E            |
|                                                           |
\___________________________________________________________/
*/
/*  Sprite Pattern Rotation & Sprite Pattern flip routines
|    
|     2020 Eric Boez
|    
|  Sprite16RotationRam
|  Sprite16RotationVram
|  Sprite8RotationVram
|  Sprite8RotationRam
|  Sprite8FlipRam
|  Sprite16FlipRam
|  Sprite16FlipVram
|  Sprite8FlipVram
*/ 


#include "../../header/msx_fusion.h"

const char shift[4][4]={{16,0,24,8},{8,24,0,16},{16,24,0,8},{8,0,24,16}};

unsigned char TempBuffer[32];
unsigned char DoBuffer[32];
unsigned char rot;
unsigned char i;

//-----------------------------------------------------------------------------
// Rotation of a 16x16 pattern stored in RAM and already defined. The new pattern will replace the pattern stored in VRAM
// pattern : N° of the sprite pattern 
// *SrcPattern : address where are stored pattern in RAM
// rotation : -90 for a left rotation or 90 for a right rotation. 180 or -180 for a double rotation
void Pattern16RotationRam(char pattern, char *SrcPattern, signed int rotation)   // Rotation 90 or -90 or 180 or -180
{
   

   
    rot=0;
    if (rotation==90 || rotation==-90 || rotation==180 || rotation==-180)
    {
          if (rotation<0)
              rot=1;
          for (int i = 0; i < 4; ++i)
          {
            
               PatternRotation (SrcPattern+i*8,    DoBuffer+shift[rot][i], rot);   // Rotate pattern 0
          }
        //  PatternRotation (SrcPattern+8,  DoBuffer+shift[rot][1], rot);   // Rotate pattern 1
        //  PatternRotation (SrcPattern+16, DoBuffer+shift[rot][2], rot);   // Rotate pattern 2
        //  PatternRotation (SrcPattern+24, DoBuffer+shift[rot][3], rot);   // Rotate pattern 3
      

          if (rotation==180 || rotation==-180)
          {
              MemCopy(TempBuffer,DoBuffer,32);
              for (int i = 0; i < 4; ++i)
              {
                PatternRotation (&TempBuffer+i*8,    &DoBuffer+shift[rot][i], rot);   // Rotate pattern 0
              }
              //PatternRotation (TempBuffer+8,  DoBuffer+shift[rot][1], rot);   // Rotate pattern 1
              //PatternRotation (TempBuffer+16, DoBuffer+shift[rot][2], rot);   // Rotate pattern 2
              //PatternRotation (TempBuffer+24, DoBuffer+shift[rot][3], rot);   // Rotate pattern 3
          }

          CopyRamToVram(DoBuffer, Peekw( 0xF926 ) + (pattern << 3), 32);     // Copy RotBuffer to VRAM
    }
}

//-----------------------------------------------------------------------------
// Rotation of a 16x16 pattern stored in VRAM and already defined. The rotated pattern will replace the old one.
// pattern : N° of the sprite pattern 
// rotation : -90 for a left rotation or 90 for a right rotation
// DestPattern : 0 copied over the same Pattern. Any other Number will copy the rotated pattern in another pattern slot

void Pattern16RotationVram(char pattern, signed char rotation, char DestPattern) 
{

  rot=1;
   if (rotation==90)
      rot=0;

        CopyVramToRam(Peekw( 0xF926 ) + (pattern << 3), TempBuffer, 32);    // Copy the 4 Patterns to TempBuffer
        for (int i = 0; i < 4; ++i)
        {
            PatternRotation (TempBuffer+i*8,    DoBuffer+shift[rot][i], rot);   // Rotate pattern 0
        }
      //  PatternRotation (TempBuffer+8,  DoBuffer+shift[rot][1], rot);   // Rotate pattern 1
      //  PatternRotation (TempBuffer+16, DoBuffer+shift[rot][2], rot);   // Rotate pattern 2
      //  PatternRotation (TempBuffer+24, DoBuffer+shift[rot][3], rot);   // Rotate pattern 3

        if (DestPattern!=0)
          pattern=DestPattern;
        CopyRamToVram(DoBuffer, Peekw( 0xF926 ) + (pattern << 3), 32);     // Copy RotBuffer to VRAM
}

//-----------------------------------------------------------------------------
// Rotation of a 8x8 pattern stored in VRAM and already defined. The rotated pattern will replace the old one.
// pattern : N° of the sprite pattern 
// rotation : -90 for a left rotation or 90 for a right rotation
// DestPattern : 0 copied over the same Pattern. Any other Number will copy the rotated pattern in another pattern slot

void Pattern8RotationVram(char pattern, signed char rotation, char DestPattern)  // Rotation : 90 or -90
{
    rot=1;


     if (rotation==90)
        rot=0;

      CopyVramToRam(Peekw( 0xF926 ) + (pattern << 3), TempBuffer, 8);
      PatternRotation (TempBuffer,    DoBuffer, rot);
      if (DestPattern!=0)
          pattern=DestPattern;
      CopyRamToVram(DoBuffer, Peekw( 0xF926 ) + (pattern << 3), 8); 
}

//-----------------------------------------------------------------------------
// Rotation of a 8x8 pattern stored in RAM and already defined. The new pattern will replace the pattern stored in VRAM
// pattern : N° of the sprite pattern 
// *SrcPattern : address where are stored pattern in RAM
// rotation : -90 for a left rotation or 90 for a right rotation. 180 or -180 for a double rotation
void Pattern8RotationRam(char pattern, char *SrcPattern, signed int rotation)  // Rotation 90 or -90 or 180 or -180
{
   rot=0;


   if (rotation==90 || rotation==-90 || rotation==180 || rotation==-180)
   {
        if (rotation<0)
            rot=1;

        PatternRotation (SrcPattern,    DoBuffer, rot);
   

        if (rotation==180 || rotation==-180)
        {
            MemCopy(TempBuffer,DoBuffer,8);
            PatternRotation (TempBuffer,    DoBuffer, rot);
        }
   
        CopyRamToVram(DoBuffer, Peekw( 0xF926 ) + (pattern << 3), 8);
  }
}


//-----------------------------------------------------------------------------
// Flip a 8x8 pattern stored in RAM and already defined. The new pattern will replace the pattern stored in VRAM
// pattern : N° of the sprite pattern 
// *SrcPattern : address where are stored pattern in RAM
// direction : 0 for Horizontal Flip.  1 for Vertical Flip
void Pattern8FlipRam(char pattern, char *SrcPattern, char direction)  
{

        if (direction==0)
        {
          PatternHFlip (SrcPattern + (pattern << 3),    DoBuffer);   
        }
        else
        {
          PatternVFlip (SrcPattern + (pattern << 3),    DoBuffer);   
        }
        
        CopyRamToVram(DoBuffer, Peekw( 0xF926 ) + (pattern << 3), 8);     // Copy FlipBuffer to VRAM
}

//-----------------------------------------------------------------------------
// Flip a 16x16 pattern stored in RAM and already defined. The new pattern will replace the pattern stored in VRAM
// pattern : N° of the sprite pattern 
// *SrcPattern : address where are stored pattern in RAM
// direction : 0 for Horizontal Flip.  1 for Vertical Flip
void Pattern16FlipRam(char pattern, char *SrcPattern, char direction)  
{

         if (direction==0)
        {
          for (int i = 0; i < 4; ++i)
          {
              PatternHFlip (SrcPattern+i*8,    DoBuffer+shift[2][i]);  
          } 
          //PatternHFlip (SrcPattern+8,  DoBuffer+24);   
          //PatternHFlip (SrcPattern+16, DoBuffer);   
          //PatternHFlip (SrcPattern+24, DoBuffer+8);  
        }
        else
        {
           for (int i = 0; i < 4; ++i)
          {
              PatternVFlip (SrcPattern+i*8,    DoBuffer+shift[3][i]);   
          }
        //  PatternVFlip (SrcPattern+8,  DoBuffer);   
        //  PatternVFlip (SrcPattern+16, DoBuffer+24);   
        //  PatternVFlip (SrcPattern+24, DoBuffer+16);  
        }

          CopyRamToVram(DoBuffer, Peekw( 0xF926 ) + (pattern << 3), 32);     // Copy FlipBuffer to VRAM
}

//-----------------------------------------------------------------------------
// Flip a 16x16 pattern stored in VRAM and already defined. The new pattern will replace the pattern stored in VRAM
// pattern : N° of the sprite pattern 
// *SrcPattern : address where are stored pattern in RAM
// direction : 0 for Horizontal Flip.  1 for Vertical Flip
void Pattern16FlipVram(char pattern, char direction, char DestPattern)  
{


          CopyVramToRam(Peekw( 0xF926 ) + (pattern << 3), TempBuffer, 32); 
          if (direction==0)
          {
            for (int i = 0; i < 4; ++i)
            {
                PatternHFlip (TempBuffer+i*8,    DoBuffer+shift[2][i]);   
            }
            // PatternHFlip (TempBuffer+8,  DoBuffer+24);   
            // PatternHFlip (TempBuffer+16, DoBuffer);   
            // PatternHFlip (TempBuffer+24, DoBuffer+8);  
          }
          else
          {
            for (int i = 0; i < 4; ++i)
            {
               PatternVFlip (TempBuffer+i*8,    DoBuffer+shift[3][i]);  
            }
            // PatternVFlip (TempBuffer+8,  DoBuffer);      
            // PatternVFlip (TempBuffer+16, DoBuffer+24);   
            // PatternVFlip (TempBuffer+24, DoBuffer+16);   
          }
          
          if (DestPattern!=0)
            pattern=DestPattern;

          CopyRamToVram(DoBuffer, Peekw( 0xF926 ) + (pattern << 3), 32);     // Copy FlipBuffer to VRAM
}

//-----------------------------------------------------------------------------
// Flip a 8x8 pattern stored in VRAM and already defined. The new pattern will replace the pattern stored in VRAM
// pattern : N° of the sprite pattern 
// direction : 0 for Horizontal Flip.  1 for Vertical Flip
void Pattern8FlipVram(char pattern, char direction, char DestPattern)  
{


      CopyVramToRam(Peekw( 0xF926 ) + (pattern << 3), TempBuffer, 8);
      if (direction==0)
      {
          PatternHFlip (TempBuffer,  DoBuffer);
      }
      else
      {
          PatternVFlip (TempBuffer,  DoBuffer);
      }

      if (DestPattern!=0)
            pattern=DestPattern;

      CopyRamToVram(DoBuffer, Peekw( 0xF926 ) + (pattern << 3), 8); 
}



