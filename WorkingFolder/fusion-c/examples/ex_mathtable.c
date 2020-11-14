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
// Example : Use of precomputed math tables
//
// Works on MSX2 and upper  
//

// Include functions header
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_graph2.h"
#include "fusion-c/header/mathtable/macro.h"

// Include data
#include "fusion-c/header/fonts/font8x8_basic.h"
#include "fusion-c/header/mathtable/mt_trigo_360.inc"
#include "fusion-c/header/mathtable/mt_sqrt_1024.inc"

#define  __SDK_MSXVERSION__ 2

#define KEY_ESC   27
#define KEY_RIGTH 28
#define KEY_LEFT  29
#define KEY_UP    30
#define KEY_DOWN  31

// Convert Q8.8 fixed-point number to float string
void Q8_8toString(int val, char* dest, char size)
{
	size;
	char* str = dest;
	if(val < 0)
	{
		*str = '-';
		str++;
		val = -val;
	}

	int integer = QxGetInteger(8, 8, val);
	Itoa(integer, str, 10);
	str = dest + StrLen(dest);
	*str = '.';
	str++;
	
	int decimal = QxGetDecimal(8, 8, val);
	if(decimal < 10)
	{
		*str = '0';
		str++;		
	}		
	Itoa(decimal, str, 10);
}

// Convert Q4.12 fixed-point number to float string
void Q4_12toString(int val, char* dest, char size)
{
	size;
	char* str = dest;
	if(val < 0)
	{
		*str = '-';
		str++;
		val = -val;
	}

	int integer = QxGetInteger(4, 12, val);
	Itoa(integer, str, 10);
	str = dest + StrLen(dest);
	*str = '.';
	str++;
	
	int decimal = QxGetDecimal(4, 12, val);
	if(decimal < 10)
	{
		*str = '0';
		str++;		
	}		
	Itoa(decimal, str, 10);
}


// Program entry point
void main(void) 
{
	Screen(5);
	KeySound(0);

	// Setup some constants
	const unsigned char centerX = 180;
	const unsigned char centerY = 110;
	const int step = 90;
	const int scale = 360 / step;
	
	// Draw static text
	PutText(10, 10, "MathTable Example", 0);
	PutText(10, 30, "Angle:", 0);
	PutText(10, 40, "Sinus:", 0);
	PutText(10, 50, "Cosinus:", 0);
	PutText(10, 60, "Sq root:", 0);
	PutText(10, 180, "[<][>] Angle", 0);
	PutText(10, 200, "[ESC] Exit", 0);

	char x1, y1, x2, y2;
	int i;

	// Draw static circle
	x1 = (char)(g_Cosinus360[(step - 1) * scale] >> 6);
	y1 = (char)(g_Sinus360[(step - 1) * scale] >> 6);
	for(i = 0; i < step; i++)
	{
		x2 = (char)(g_Cosinus360[i * scale] >> 6);
		y2 = (char)(g_Sinus360[i * scale] >> 6);
		Line((unsigned char)(centerX + x1), (unsigned char)(centerY - y1), (unsigned char)(centerX + x2), (unsigned char)(centerY - y2), 15, 0);
		x1 = x2;
		y1 = y2;
	}
		
	int angle = 30, prevAngle = -1;
	char bContinue = 1;
	char strBuffer[16];
	char len, prevAngleLen = 0, prevSinLen = 0, prevCosLen = 0, prevSqrtLen = 0;

	x1 = (char)(g_Cosinus360[angle] >> 6);
	y1 = (char)(g_Sinus360[angle] >> 6);		

	// Main loop
    while(bContinue)
    {
		//while(!IsVsync()) {} // Wait v-sync

		// Handle user input
		char key = Inkey();
		switch(key)
		{
		case KEY_ESC:
			bContinue = 0;
			break;
		case KEY_RIGTH: 
			angle++;
			if(angle >= 360)
				angle = 0;
			break;
		case KEY_LEFT: 
			angle--;
			if(angle < 0)
				angle = 359;
			break;
		}
		
		if(angle == prevAngle) // Angle didn't change, skip the screen update
			continue;
		
		prevAngle = angle;

		// Clear previous frame
		Line(centerX, centerY, (unsigned char)(centerX + x1), (unsigned char)(centerY - y1), 0, 0);
		Pset((unsigned char)(centerX + x1), (unsigned char)(centerY - y1), 15, 0);

		// Draw line
		x1 = (char)(g_Cosinus360[angle] >> 6);
		y1 = (char)(g_Sinus360[angle] >> 6);		
		Line(centerX, centerY, (unsigned char)(centerX + x1), (unsigned char)(centerY - y1), 9, 0);
		
		// Draw angle value
		Itoa(angle, strBuffer, 10);
		PutText(58, 30, strBuffer, 0);
		len = StrLen(strBuffer);
		for(i = 0; len + i < prevAngleLen; i++)
			PutText(58 + 8 * (len + i), 30, "  ", 0);
		prevAngleLen = len;
		
		// Draw sinus value
		Q4_12toString(g_Sinus360[angle], strBuffer, 16);
		PutText(58, 40, strBuffer, 0);
		len = StrLen(strBuffer);
		for(i = 0; len + i < prevSinLen; i++)
			PutText(58 + 8 * (len + i), 40, "  ", 0);
		prevSinLen = len;
		
		// Draw cosinus value
		Q4_12toString(g_Cosinus360[angle], strBuffer, 16);
		PutText(74, 50, strBuffer, 0);
		len = StrLen(strBuffer);
		for(i = 0; len + i < prevCosLen; i++)
			PutText(74 + 8 * (len + i), 50, "  ", 0);
		prevCosLen = len;

		// Draw square-root value
		Q8_8toString(g_SquareRoot1024[angle], strBuffer, 16);
		PutText(74, 60, strBuffer, 0);
		len = StrLen(strBuffer);
		for(i = 0; len + i < prevSqrtLen; i++)
			PutText(74 + 8 * (len + i), 60, "  ", 0);
		prevSqrtLen = len;
	}

	Screen(0);
	Exit(0);
}
 