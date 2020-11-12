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
// Different Way to input keybaoird and joystick
//
// Works on MSX1 and Upper 
//


#include "fusion-c/header/msx_fusion.h"
#include <stdio.h>



void Init(void);
void InputRead(void);
void Dispose(void);
char MenuInterrupt(void);

char joystick;
char buttonA;
char buttonB;
char FKEY;
char RKEY;

char matrix;

char ReadMSX(void);


void Init(void) {
	SetColors(15,0,0);
	KeySound(0);
}

char MenuInterrupt(void) {
	InputRead();
	Locate(12,0);
	PutCharHex(joystick);Print("   ");
	Locate(12,2);
	PutCharHex(buttonA);Print("   ");
	Locate(12,4);
	PutCharHex(buttonB);Print("   ");
	Locate(12,6);
	PutCharHex(matrix);Print("   ");
	Locate(12,8);
	PutCharHex(FKEY);Print("   ");
	Locate(12,10);
	PutCharHex(RKEY);Print("   ");
return 1;
}

void InputRead(void) {
	joystick = JoystickRead(0) | JoystickRead(1);
	buttonA = TriggerRead(0) | TriggerRead(1);
	buttonB = TriggerRead(3);
	matrix = GetKeyMatrix(6); // (b2)Graph, (b5)F1
	FKEY = Fkeys();
	RKEY = Rkeys();
}

void Dispose(void) {
	SetColors(15,4,4);
	Beep();
	KillKeyBuffer();
}

void main(void)
{
	char rd;
	Init();
	Cls();

	rd=ReadMSXtype();
	Locate (0,0);
	Print("Joytisck:");
	Locate(0,2);
	Print("Button 1:");
	Locate (0,4);
	Print("Button 2:");
	Locate (0,6);
	Print("Matrix l6:");
	Locate (0,8);
	Print("F-Keys:");
	Locate(0,10);
	Print("R-Keys:");
	Locate(0,11);
	printf("\n\rMSX ver : %d",rd);
	Locate(0,12);
	
	printf("\n\rKeyboard type : %d",ReadKeyboardType());
	do {
		MenuInterrupt();
	} while (Inkey()!=27);

	Dispose();
}