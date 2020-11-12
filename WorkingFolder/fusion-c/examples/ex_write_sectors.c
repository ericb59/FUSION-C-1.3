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
// Example : WARNING THIS PROGRAM WRITE ON DISK SECTOR.
// Load a SC8 image by classic function, then save the image data directly to sector, then reload the images from sectors
// Be carefull
//  !!!!!! Use a free floppy disk to test this example, because it will erase some data on the disk by writing directly to sectors
// 
//
//. need external files :
//    supergir.SC8
//
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_graph2.h"
#include "fusion-c/header/io.h"
#include <stdio.h>
#include <string.h>


static FCB file;                        // Used by MSXDOS loading routines

unsigned char LDbuffer[6120];           // Load Buffer to store  data


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

/* ---------------------------------
          FT_LoadSc8Image

    Load a SC8 Picture and put datas
  on screen, begining at start_Y line
-----------------------------------*/ 
int FT_LoadSc8Image(char *file_name, unsigned int start_Y, char *buffer)
    {
        int rd=5120;
        int nbl=0;
        InitPSG();
        FT_SetName( &file, file_name );
        if(fcb_open( &file ) != FCB_SUCCESS) 
        {
          FT_errorHandler(1, file_name);
          return (0);
        }
        fcb_read( &file, buffer, 7 );  // Skip 7 first bytes of the file
        while(rd!=0)
        {
            SetColors(15,0,buffer[192]);
            rd = fcb_read( &file, buffer, 5120 );
                if (rd!=0)
                {
                  SetColors(15,0,0);
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

     int i;
     unsigned int t1,t2,t3;
     
    Screen(8);
    SetRealTimer(0);
   
    FT_LoadSc8Image("teenage1.SC8",0,LDbuffer);  // Load a SC8 image to screen

    t1=RealTimer();

    SetDiskTrAddress(LDbuffer);              // Set Transfer Disk Adress to Buffer
    SetRealTimer(0);
    for ( i = 0; i < 11; ++i)
    { 
        LMCM8( &LDbuffer, 0, i*20, 256, 20, 8);  
    
        SectorWrite(1100+i*10, 0, 10);                    // Write Ram Buffer to sectors. Starting at sector 1320. 1 sectore store 512Bytes, thus 2 image's lines
        HMMV( 0, i*20, 256, 20, 0);
        Beep();
    }

    t2=RealTimer();
    Beep();

    Cls();

    SetRealTimer(0);
    for ( i = 0; i < 11; ++i)
    { 
        SectorRead(1100+i*10, 0, 10);                     // Read  sectors to Buffer
        HMMC( &LDbuffer, 0, i*20, 256, 20);           // transfer Buffer to VRAM
    }
    t3=RealTimer();
    Beep();Beep();Beep();
    WaitForKey();
    Screen(0);
    printf("\n\r Time used for Classic Read : %d",t1);       // Show time needed for each load/write operation
    printf("\n\r Time used for Sector write : %d",t2);
    printf("\n\r Time used for Sector Read : %d",t3);
    Exit(0);
}