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
// Example : Interlace mode with a 16 color images
// 
// Works on MSX2 and upper  
//
// Need external file :
//    visage.pi7
//    visage.si7
//    visage.sj7

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_graph2.h"
#include <string.h>
#include <stdio.h>


 
static FCB file;                            // Initialisatio de la structure pour le systeme de fichiers
 
 
// Buffer definition for all Save and Load Functions
typedef struct {
    unsigned char LDbuffer[1024*4];
} BufferType;

BufferType Mybuffer;



char Mypalette[64];



void FT_SetName( FCB *p_fcb, const char *p_name )  // Routine servant à vérifier le format du nom de fichier
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
 
void FT_errorHandler(char n, char *name)            // Gère les erreurs
{
  Screen(0);
  SetColors(15,6,6);
  switch (n)
  {
      case 1:
          Print("\n\rFAILED: FcbOpen(): ");
          Print(name);
      break;
 
      case 2:
          Print("\n\rFAILED: FcbClose():");
          Print(name);
      break;  
 
      case 3:
          Print("\n\rStop Kidding, run me on MSX2 !");
      break; 

      case 4:
        Print("\n\rFAILED: fcb write: ");
        Print(name);
      break;
  }
Exit(0);
}


char FT_LoadBinPalette(char *file_name, char *org_palette)        
    {
        char n,c;
        char byte[7];
       
   
        FT_SetName( &file, file_name );
        if(FcbOpen( &file ) != FCB_SUCCESS) 
        {
              FT_errorHandler(1, file_name);
        }      
        
         n=0;
         c=0;
         FcbRead( &file, byte, 7 );                             // Bypass first 7 bytes
         
         while (c<16)                                           // 16 is the number of colors. Change it to 4 if you want to load a screen 6 Palette
         {
            org_palette[n]=c;
          
            n++;

            FcbRead( &file, byte, 2 );
     
            org_palette[n]=(byte[0]>>4) & 0b00000111;           // Red
            n++;

            org_palette[n]=(byte[1]);                           // green
            n++;

            org_palette[n]=(byte[0]) & 0b00000111;              // blue
            n++;
            
            c++;
         }
         FcbClose(&file);
        
         SetPalette((Palette *)Mypalette);                   

    return(1);
}

char FT_LoadImage(char *file_name, unsigned int start_Y, BufferType *Xbuffer)        // Charge les données d'un fichiers
    {
        unsigned int width_array[]={256,512,512,256,512,256,256,256};  // Wifth in pixel of each screen mode
        char pixels_byte[]={2,4,2,1,2,1,1,1};                          // Number of pixels color, coded in 1 byte 
        unsigned int nx,ny,rd,BytesPerLine;
        size_t BufferSize;
        
        nx=width_array[_ScreenMode-5];
        BytesPerLine=nx / pixels_byte[_ScreenMode-5];
        BufferSize=sizeof(Xbuffer->LDbuffer);
        ny=BufferSize / BytesPerLine;

        FT_SetName( &file, file_name );
        if(FcbOpen( &file ) != FCB_SUCCESS) 
        {
              FT_errorHandler(1, file_name);
        }

        rd=FcbRead( &file, Xbuffer->LDbuffer, 7 );                                           // Skip 7 first bytes of the file  
        while (rd!=0)
        {
             rd=FcbRead( &file, Xbuffer->LDbuffer, ny*BytesPerLine);                          // Read Read Data From Disc to RAM Buffer)
             HMMC(Xbuffer->LDbuffer, 0,start_Y, nx, ny);                                      // Move the buffer to VRAM. 
             start_Y=start_Y+ny;                                                              // Next Y position where to put data in VRAM
        }

        FcbClose(&file);
return(1);
}





void main(void)
{

    int i=1;
    char j=0;
    signed char x,y;
    x=0;
    y=0;

    Screen(7);
    SetTransparent(1);                            // Disable the color 0 as transparent
    FT_LoadBinPalette("visage.pi7",Mypalette);    // Load the binary Palette
    FT_LoadImage("visage.si7",0,&Mybuffer);       // Load even  16 color image
    VDPinterlace(1);                              // Activate the Interlace mode
    FT_LoadImage("visage.sj7",256,&Mybuffer);     // Load the odd 16 color image

    


  WaitKey();
  SetTransparent(0);
  Screen(0);
  Exit(0);
}