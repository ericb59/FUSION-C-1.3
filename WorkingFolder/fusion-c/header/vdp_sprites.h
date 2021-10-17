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
|                   V1.0 - 09-10-11 2018                    |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|   vdp_spites.h : Managing MSX sprites                     |
|                                                           |
|                                                           |
|                                                           |
\___________________________________________________________/
*                         (°□°)
*	Eric Boez 2020
*	
*	
*/

#ifndef __VDP_SPRITES__
#define __VDP_SPRITES__ 

typedef struct {
    char spr;        // Sprite ID
    char y;     	 // X destination of the Sprite 
    char x;     	 // Y destination of the sprite
    char pat;        // Pattern number to use 
    char col;        // Color to use (Not usable with MS2's sprites)
} FastSPRITE;


void 		Sprite8(void);							// Actiate 8x8 Sprite pattern size
void 		Sprite16(void);							// Activate 16x16 Sprite pattern size 
void 		SpriteSmall(void);						// Activate Normal Pixel Size sprite
void 		SpriteDouble(void);						// Activate Double Pixel Size sprite
void 		SpriteOff(void);						// disable on screen sprites
void 		SpriteOn(void);							// enable on screen sprites
void 		SpriteReset(void);						// Reset all sprite patterns and attributs
int 		SpriteCollisionX(void);					// Return the X position of last sprite collision (Only MSX2)
int 		SpriteCollisionY(void);					// Return the Y position of last sprite collision (Only MSX2)
void 		PutSprite( char sprite_no,  char pattern_no, char x,  char y,  char ec_color );		// Put A sprite on Screen
void 		SetSpritePattern(  char pattern_no,  char* p_pattern,  char s_size );				// Set a Sprite Pattern
void 		SetSpriteColors(char spriteNumber, char *data);										// MSX2 Sprite color setting
unsigned int	*Sprite32Bytes( unsigned int *bindata );										// Convert a The 32 Bytes online 16x16 pattern to the MSX VRAM format

void 		Pattern8RotationRam(char pattern, char *SrcPattern, signed int rotation);			// Rotate a 8x8 Sprite pattern from RAM
void 		Pattern16RotationRam(char pattern, char *SrcPattern, signed int rotation);			// Rotate a 16x16 Sprite pattern from RAM
void 		Pattern16RotationVram(char pattern, signed char rotation, char DestPattern); 		// Rotate a 16x16 Sprite pattern from VRAM to VRAM
void 		Pattern8RotationVram(char pattern, signed char rotation, char DestPattern);			// Rotate a 8x8 Sprite pattern from VRAM
void 		Pattern16FlipRam(char pattern, char *SrcPattern, char direction);					// Flip a 16x16 sprite pattern from RAM, Horizontally :0 or Vertically : 1
void 		Pattern8FlipRam(char pattern, char *SrcPattern, char direction);					// Flip a 8x8 sprite pattern from RAM, Horizontally :0 or Vertically : 1
void 		Pattern16FlipVram(char pattern, char direction, char DestPattern);					// Flip a 16x16 sprite pattern from VRAM, Horizontally :0 or Vertically : 1 to VRAM
void 		Pattern8FlipVram(char pattern, char direction, char DestPattern);					// Flip a 8x8 sprite pattern from VRAM, Horizontally :0 or Vertically : 1 to VRAM
void 		SpriteFollow(void *SpriteStruct) __naked __z88dk_fastcall;							// Decode and set sprite coordinates to follow a sprite path made with SPRITE PATH TOOL
void  		fPutSprite(void *parameters)  __z88dk_fastcall;										// Fast PutSprite. USed the FastSprite Structure
#define  	SpriteOverlap()		(((*(char *)0xF3E7) >> 6) & 0x01) 								// Check is there are sprite overlapping on screen 4 sprite on line on MSX1 , 8 sprite on the same line on MSX2
#define	 	SpriteOverlapId() 	((*(char *)0xF3E7) & 0b00011111)								// Return the ID of the first overlapping sprite 
#define     SpriteCollision()   (((*(char *)0xF3E7) >> 5) & 0x01)      							// Check Sprite colllision Return 1 when 2 spites collide      


/*
Sprite color palette in screen mode 8

		R  G  B         Name         .                  
00		0  0   0		Black
01 		0  0   2   		Dark Blue
02 		3  0   0 		Dark Red
03		3  0   2 		Dark Purple
04		0  3   0 		Dark Green
05		0  3   2 		Turquoise Blue
06 		3  3   0 		Green Olive
07		3  3   2 		Grey
08 		4  4   2 		Ligh Orange
09 		0  0   7 		Blue
10 		7  0   0 		Red
11		7  0   7 		Purple
12 		0  7   0 		Green
13		0  7   7 		Light Blue
14 		7  7   0 		Yellow
15      7  7   7		White
 
*/

// Rotation of a 8x8 pattern stored in RAM and already defined. The new pattern will replace the pattern stored in VRAM
// pattern : N° of the sprite pattern 
// *SrcPattern : address where are stored pattern in RAM
// rotation : -90 for a left rotation or 90 for a right rotation



#endif
