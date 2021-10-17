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
// Example : Play Sample thru Covox Module From RAM or from VRAM
//
// Works on MSX2 and upper  with a Covox module attached
//
// Need external file
//    sample.msx
// 
// Load Data to VRAM then Send Data to Covox Module
//
// Add covox module to OpenMSX Emulator
// open Command line interface of OpenMSX
// Press F10 (Windows) or CMD+L (MAC)
// in the new window enter : 
// plug printerport simpl
// <enter>
// Then close the command line  windows, as the same way you opened it
// Now Covox Module is active in OpenMSX Emulator
//
// Exporting 8 Bits PCM file with Audacity.
// File > Export > Export to Wav
// In the File Type, Choose Other uncompressed format
// Then, choose Unsigned 8-Bit PCM in the Encoding field
// And Raw-Hader Less as Header
//
//
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_graph2.h"
#include <string.h>
#include <stdio.h>

static FCB file;                        // Used by MSXDOS loading routines
MMMtask  t;

unsigned char LDbuffer[14085];


// File Error Handler
void FT_errorHandler(char n, char *name)
{
  InitPSG();
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
          Print("\n\rStop Kidding, run me on MSX2 !");
      break; 
  }
Exit(0);
}

// Set File Name 
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

// Load Data To RAM
int FT_LoadRam(char *file_name, unsigned int size, char *buffer)
    {
        
        FT_SetName( &file, file_name );
        if(fcb_open( &file ) != FCB_SUCCESS) 
        {
          FT_errorHandler(1, file_name);
          return (0);
        }
        fcb_read( &file, buffer, size );  // Skip 7 first bytes of the file
       
      

return(1);
}


void main(void)
{
    char n=0;
    SetColors(0,5,255);
    Screen(8);
    Cls();
    SetColor(255);
    PutText(0,150,". now Loading Sample To RAM. ",0);
    FT_LoadRam("sample.msx",14085,LDbuffer);              // Load Sample to Ram
    
    PutText(0,160,". Copying Data TO VRAM. ",0);
    CopyRamToVram(LDbuffer, 2550, 14085);                 // Copy Ram Sample to Screen 8 Page 0, line 10

    while (n<10){
        PutText(0,180,". Playing from RAM   ",0);
        CovoxPlayRam(LDbuffer, 14085, 15);                // Play Sample from RAM
      
        PutText(0,180,"PRESS A KEY ..................",0);
         WaitKey();
        PutText(0,180,". Playing from VRAM",0);
        CovoxPlayVram(0,2550, 14085, 15);                 // Play Sample from VRAM

        n++;
      }
Screen(0);

    Exit(0);
}