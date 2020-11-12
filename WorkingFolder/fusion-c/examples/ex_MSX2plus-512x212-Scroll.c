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
// Example of 512 * 256 Hardware Scroll
//
// Works on MSX2 + / Turbo-R  
//
// Need external files : 
//      IMGF1.SC8
//      IMGF2.SC8
//      IMGF3.SC8
//      IMGF4.SC8
//
// Use arrow keys to move the scroll in the 4 directions

#include <string.h>
#include <stdio.h>
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_graph2.h"
#include "fusion-c/header/vdp_sprites.h"

static FCB file;                        // Init the FCB Structure variable

unsigned char LDbuffer[25000];           // Set A loading Buffer of 5000 Bytes
unsigned int x,y;


/* ---------------------------------
                FT_Wait

                Waiting 
-----------------------------------*/ 
void FT_Wait(int cicles)
{
  int i;
  for(i=0;i<cicles;i++) 
    {
      while (Vsynch()==0)
      {}
    }
}

void Wait_Vsynch(void)
{
   while (Vsynch()==0)
      {}
    SetScrollH(x);
    SetScrollV(y);

}
/* ---------------------------------
                FT_SetName

    Set the name of a file to load
                (MSX DOS)
-----------------------------------*/ 
void FT_SetName( FCB *p_fcb, const char *p_name ) 
{
  char i, j;
  memset( p_fcb, 0, sizeof(FCB) );
  for( i = 0; i < 11; i++ ) {
    p_fcb->name[i] = ' ';
  }
  for( i = 0; (i < 8) && (p_name[i] != 0) && (p_name[i] != '.'); i++ ) {
    p_fcb->name[i] =  p_name[i];
  }
  if( p_name[i] == '.' ) {
    i++;
    for( j = 0; (j < 3) && (p_name[i + j] != 0) && (p_name[i + j] != '.'); j++ ) {
      p_fcb->ext[j] =  p_name[i + j] ;
    }
  }
}

/* ---------------------------------
            FT_errorHandler

          In case of Error
-----------------------------------*/ 
void FT_errorHandler(char n, char *name)
{
  Screen(0);
  SetColors(15,6,6);
  switch (n)
  {
      case 1:
          Print("\n\rFAILED: fcb_open(): ");
          Print(name);
      break;

      case 2:
          Print("\n\rFAILED: fcb_close():");
          Print(name);
      break;  

      case 3:
          Print("\n\rStop Kidding, run me on MSX2+ !");
      break; 
  }
Exit(0);
}

/* ---------------------------------
          FT_LoadSc8Image

    Load a SC8 Picture and put datas
  on screen, begining at start_Y line
-----------------------------------*/ 
int FT_LoadSc8Image(char *file_name, unsigned int start_Y, char *buffer)
    {
        int rd=2304;
        int nbl=0;
      
        FT_SetName( &file, file_name );
        if(fcb_open( &file ) != FCB_SUCCESS) 
        {
          FT_errorHandler(1, file_name);
          return (0);
        }
        fcb_read( &file, buffer, 7 );  // Skip 7 first bytes of the file
        while(rd!=0)
        {
            SetBorderColor(buffer[192]);
            rd = fcb_read( &file, buffer, 4608 );
                if (rd!=0)
                {
                  nbl=rd/256;
                  HMMC(buffer, 0,start_Y,256,nbl ); // Move the buffer to VRAM. 17 lines x 256 pixels  from memory
                  start_Y=start_Y+nbl; 
               }
        }
      if( fcb_close( &file ) != FCB_SUCCESS ) 
      {
         FT_errorHandler(2, file_name);
          return (0);
      }

return(1);
}


void main(void) 
{
  int j;
  char rd;
  char nb[6];
  x=y=0;
  rd=ReadMSXtype();                   // Read MSX Type

  if (rd<2)                          // If not at least MSX2+
  {
    FT_errorHandler(3,"Need MSX2+ or better ");
  }
  KeySound(0);
  Screen(8);                          // Init Screen 8
  //FillVram(0,0,65535);                // Clear VRAM Pape 0 by Byte 0 (Black)
  SpriteOff();
  
  SetColors(255,0,0);
  PutText(10,190,"After the Beep",0);
  PutText(10,200,"Use Arrow Keys",0);

  FT_LoadSc8Image("IMGF1.SC8",0,LDbuffer);    // Loading Image To Page 0
  FT_LoadSc8Image("IMGF2.SC8",212,LDbuffer);  // Loading Image To Page 0 > 212
  FT_LoadSc8Image("IMGF3.SC8",256,LDbuffer);  // Loading Image To Page 1
  FT_LoadSc8Image("IMGF4.SC8",468,LDbuffer);  // Loading Image To Page 1 > 212

  
    SetScrollMask(1);                         // Activating the MSX2+ Horizontal Mask (8pixels at the right of the screen)
    SetScrollDouble(1);                       // Activaring the 2 screens Scroll Mode
    SpriteOff();
    Beep();
while (Inkey()!=27){                          // Push ESC to end the program
    
    j=JoystickRead(0);                        // Checking Arrow Keys

    switch (j)
    {
      case 1:
        if (y<44){
          y++;
          SetScrollV(y);
          FT_Wait(1);
        }
        break;

      case 3:
        x++;
        if (x>511)
            x=0;
         
        Wait_Vsynch();
        
       break;

      case 5:
        if (y>0){
          y--;  
         Wait_Vsynch();
        }
       break;

      case 7:
        x--;
        if (x<=0)
          x=511;
          
        Wait_Vsynch();
        
      break;

    }
    if (TriggerRead(0)){
      Wait_Vsynch();
    }
    
    Wait_Vsynch();
    
  }
  KeySound(1);
  Screen(0);
  Exit(0);

}
 
