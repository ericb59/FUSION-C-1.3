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
// Write & Read File with FCB (COmpatible with MSX-DOS 1 & 2)
//
// Works on MSX1 and Upper 
//
#include "fusion-c/header/msx_fusion.h"
#include <string.h>
#include <stdio.h>

static FCB file; 

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



void main(void)
{

	char FileName[]={"test.txt"};
	char MaxToRead;
	char MaxToWrite;
	char buffer[17];

	FT_SetName( &file, FileName );

	// Create & Writing a file with FCB MSXDOS 1 & 2
	printf("Writing File %s \n\r",FileName);

    if(FcbCreate( &file ) != FCB_SUCCESS) 
    {
        FT_errorHandler(4, FileName);
    }      
     
    MaxToWrite=17;
    FcbWrite( &file, "Hello MSX World\n", MaxToWrite );        
    FcbClose(&file);

    // Reading a file FCB MSXDOS 1 & 2
    printf("Reading File %s \n\r",FileName);

    FT_SetName( &file, FileName );
    if(FcbOpen( &file ) != FCB_SUCCESS) 
    {
        FT_errorHandler(1, FileName);
    }
    
    MaxToRead=17;
    FcbRead( &file, buffer, MaxToRead);
    FcbClose(&file);

    printf("BUFFER CONTENT :\n\r %s",buffer);


    Exit(0);

}