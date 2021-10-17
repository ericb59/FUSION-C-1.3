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
// HSYNC and H.KEYI interrupt example :  Fusionc-C 1.3
//
//  Works on MSX2 and Upper 
//
 
#include "fusion-c/header/msx_fusion.h"


char cpt;
char Ystart=10;
char Yend=60;
char Y=0;
signed char d=-1;

// This routine is called when Hsync is detected
void HBlankHook(void)
{

	// First Hsync
	if (cpt==0)
	{
		
      	VDPwriteNi(19,Y+Ystart); // Set the second Hsync to another line
        SetColors(15,9,8);
        cpt++;

	} 
	else
	{
		// Second Hsync detected
      	VDPwriteNi(19,Y+Yend); // Set the next Hsync to another line (Here, the same as the first Hsync)
        SetColors(15,5,8);
        cpt=0;

	}

}

// Wait routine
void FT_Wait(int N_cycles) 
{
  unsigned int i;

  for(i=0;i<N_cycles;i++)
  {
	    while(Vsynch()==0)
	    {}

  }
}

// This routine is called at every H.KEYI interrupt. It verify if Vsynch is done or not.
// If yes, it call HBlankHook
void InterruptHook(void)
{
	if (IsHsync())
	{
		HBlankHook();
	}
}

// This routine init the VDP Hsync to line : line 
void InitHsyncHook(unsigned int line) __z88dk_fastcall   
{
	char IE1;

	VDPwriteNi(19,line);	// Write Line number to reg 19

	IE1=Peek(0xF3DF) | 0b00010000; // RG0SAVE
	Poke(0xF3DF,IE1); 				// Save New Value
	VDPwriteNi(0,IE1);		// Enable HSYNCH in REG0
	
}
void EndHsyncHook(void)  
{
	char IE1;

	IE1=Peek(0xF3DF) & 0b11101111; // Disable the Hsynch Hook
	Poke(0xF3DF,IE1); 				
	VDPwriteNi(0,IE1);				
}


void main (void)
{
	
	Screen(0);
	SetColors (15,2,8);
	Print("HELLO ");
	Print("\n\r Screen Mode 0");
	Print("\n\r Splits screen");
	Print("\n\r With Hsync & H.KEYI interrupt");
	Print("\n\r For Fusion-C 1.3");

	InitHsyncHook(50); // Init HsyncHook
	InitInterruptHandler((unsigned int) InterruptHook); // Init  H.KEYI interrupt

  while(Inkey()!=27)
  {  
  	FT_Wait(500);
  	Y=Y+d;
  	if (Y>50 || Y<0 )
  	{
  		d=d*-1;
  	}

  }
  EndHsyncHook();
  EndInterruptHandler(); 
  Screen(0);
  Exit(0); 

}