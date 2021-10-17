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
|                   V1.1b - August 2019                     |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           | 
|   vdp_graph2.h : Drawing and graphic functions for MSX2   |
|                                                           |
|                                                           |
|                                                           |
\___________________________________________________________/
*                         (°□°)
*	Some original code from SOLID MSX C - (c) 1997 
*	SDCC port 2015  by ?	
*   Some optimisation by BitVision (2019) for FUSION V1
*   New functions and commands implementation Sylvain Cregut & Eric Boez for Fusion-c 1.1b
*	
*	----------------------------------------------------------------------------
*	| SCREEN 5	256 (horizontal) x 212 (vertical) dots  	       |
*	|			16 colours can be displayed at the same time	   |
*	|			each of 16 colours can be selected from 512 colours|
*	| Command:	high speed graphic by VDP command available	       |
*	| Memory requirements:	32kB for screen - 6A00H bytes		   |
*	|			  (4 bits x 256 x 212)				               |
*	---------------------------------------------------------------------------- 
*
*	----------------------------------------------------------------------------
*	| SCREEN 8	256 (horizontal) x 256 (vertical) dots             |
*   |            (Only 212 high are displayes) 	                   |
*	|			256 colours can be displayed at the same time	   |
*	|			each color is unique and can't be changed (0 to 255|
*	| Command:	high speed graphic by VDP command available	       |
*	| Memory requirements: 64K from 0H to FFFFH for                |
*   |                      each of the 2 available pages       	   |
*	|			    (8 bits x 256 x 256)				           |
*	---------------------------------------------------------------------------- 
*	
*/
/* 
VDP High speed commands are using the global system coordonates to adress the full 128KB of VRAM

	  (SCREEN 5)                       				  (SCREEN 6)
------------------------------    00000H    ------------------------------
| (0,0)              (255,0) |      |       | (0,0)              (511,0) |
|           Page 0           |      |       |           Page 0           |
| (0,255)          (255,255) |      |       | (0,255)          (511,255) |
|----------------------------|    08000H    |----------------------------|
| (0,256)          (255,256) |      |       | (0,256)          (511,256) |
|           Page 1           |      |       |           Page 1           |
| (0,511)          (255,511) |      |       | (0,511)          (511,511) |
|----------------------------|    10000H    |----------------------------|
| (0,512)          (255,512) |      |       | (0,512)          (511,512) |
|           Page 2           |      |       |           Page 2           |
| (0,767)          (255,767) |      |       | (0,767)          (511,767) |
|----------------------------|    18000H    |----------------------------|
| (0,768)          (255,768) |      |       | (0,768)          (511,768) |
|           Page 3           |      |       |           Page 3           |
| (0,1023)        (255,1023) |      |       | (0,1023)        (511,1023) |
------------------------------    1FFFFH    ------------------------------

    	  (SCREEN 8)                       			  (SCREEN 7)
------------------------------    00000H    ------------------------------
| (0,0)              (255,0) |      |       | (0,0)              (511,0) |
|           Page 0           |      |       |           Page 0           |
| (0,255)          (255,255) |      |       | (0,255)          (511,255) |
|----------------------------|    10000H    |----------------------------|
| (0,256)          (255,256) |      |       | (0,256)          (511,256) |
|           Page 1           |      |       |           Page 1           |
| (0,511)          (255,511) |      |       | (0,511)          (511,511) |
------------------------------    1FFFFH    ------------------------------
*/

#ifndef __VDP_GRAPH2__
#define __VDP_GRAPH2__



// VDP Commande code
#define opHMMC 	0xF0
#define opYMMM 	0xE0
#define opHMMM 	0xD0
#define opHMMV 	0xC0
#define opLMMC 	0xB0
#define opLMCM 	0xA0
#define opLMMM 	0x90
#define opLMMV 	0x80
#define opLINE 	0x70
#define opSRCH	0x60
#define opPSET 	0x50
#define opPOINT 0x40
#define opSTOP	0x00


// VDP Commande parameters
#define opRIGHT 0b00000000
#define opDOWN  0b00000000
#define opLEFT  0b00000100
#define opUP    0b00001000


//  fLMMM and fVDP Struture

typedef struct {
	unsigned int X;		// source X (0 to 511)
	unsigned int Y;		// source Y (0 to 1023)
	unsigned int X2;	// destination X (0 to 511)
	unsigned int Y2;	// destination Y (0 to 1023)
	unsigned int DX; 	// width (0 to 511)
	unsigned int DY; 	// height (0 to 511)
	unsigned char s0;	// set to 0, dummy 1st empty byte sent to chip
	unsigned char DI;	// set to 0 (b), works well from left to right
	unsigned char LOP;	// 0 to copy (a), Logical+Operation ("or"| definitions)	
} MMMtask;


typedef struct {

	unsigned int sx;		// source X (0 to 511)			R32 & 	R33
	unsigned int sy;		// source Y (0 to 1023)			R34	&	R34
	unsigned int dx;		// destination X (0 to 511)		R36	&	R37
	unsigned int dy;		// destination Y (0 to 1023) 	R38	&	R39
	unsigned int nx; 		// width (0 to 511)				R40	&	R41
	unsigned int ny; 		// height (0 to 511)			R42	&	R43
	unsigned char col;		// color used by some commands. R44	
	unsigned char param;	// Parameters set the direction. Example opDOWN | opRIGHT 		R45
	unsigned char cmd;		// VDP Command + Logical Operator : Like opLMMM | LOGICAL_XOR	R46
} FastVDP;


typedef struct {

	unsigned int dx;		// destination X (0 to 511)		R36	&	R37
	unsigned int dy;		// destination Y (0 to 1023) 	R38	&	R39
	unsigned int nx; 		// width (0 to 511)				R40	&	R41
	unsigned int ny; 		// height (0 to 511)			R42	&	R43
	unsigned char col;		// color used by some commands. R44	
	unsigned char param;	// Parameters set the direction. Example opDOWN | opRIGHT 		R45
	unsigned char cmd;		// VDP Command + Logical Operator : Like opLMMM | LOGICAL_XOR	R46
	unsigned int address;
} FastCOPY;



extern int		vMSX( void );																									// 1-MSX1 , 2-MSX2  */

extern	void	Pset( unsigned int X,  unsigned int Y,  char colour, char OP);													// puts pixel in (X,Y), logical OP=0 (just copy)  sends data to VDP chip directly */
extern	char	Point( unsigned int X,  unsigned int Y); 																		// gets colour 0..15 of pixel at (X,Y)  */
extern	void	Line( unsigned int x1,  unsigned int y1,  unsigned int x2,  unsigned int y2, char color, char OP);  			/* draws line (X1,Y)1-(X2,Y2), with logical operation*/
extern  void 	BoxFill (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, char color, char op);				/* draws a filled rectangle (X1,Y1)-(X2,Y2), with logical operation and color */
extern	void	BoxLine( unsigned int x1,  unsigned int y1,  unsigned int x2, unsigned int y2, char color, char OP); 			/* draws rectangle (X1,Y1)-(X2,Y2), with logical operation */
extern  void 	Polygon(unsigned int num_vertices, unsigned int *vertices, char color, char OP);

/* VDP COMMANDS
   Hight speed graphic commands for the VDP.
*/
extern	void 	HMMC( void *pixeldata, unsigned int DX, unsigned int DY, unsigned int NX, unsigned int NY); 							// High speed copy from RAM buffer to VRAM (size = DX*DY), X=0..255,Y=0..211
extern	void 	LMMC( void *pixeldata, unsigned int DX, unsigned int DY, unsigned int NX, unsigned int NY, char OP);					// Logical copy from RAM buffer to VRAM (size = DX*DY), X=0..255,Y=0..211

extern	void 	LMMM( unsigned int SX, unsigned int SY, unsigned int DX, unsigned int DY, unsigned int NX, unsigned int NY, char OP);	// High speed copy rectangle image with logical OP from VRAM to VRAM at (Xt,Yt) position
extern	void 	HMMM( unsigned int SX, unsigned int SY, unsigned int DX, unsigned int DY, unsigned int NX, unsigned int NY);			// High speed copy rectangle image from VRAM to VRAM at (Xt,Yt) position
extern	void 	YMMM( unsigned int SX, unsigned int SY, unsigned int DY, unsigned int NY);												// High speed copy of a part of image to another Y position (DY) Block to move start at XS,YS, Block lenght on X axis is 255-XS pixels, and high is NY pixels 

extern	void 	HMMV( unsigned int DX, unsigned int DY, unsigned int NX, unsigned int NY, char COL);									// High speed fill of a reactangle box
extern	void 	LMMV( unsigned int DX, unsigned int DY, unsigned int NX, unsigned int NY, char COL, char OP);							// High speed fill of a reactangle box with logical operation

extern 	void 	LMCM8( void *buffer, unsigned int XS, unsigned int YS, unsigned int NX, unsigned int NY, char OP);						// Logical Move from VRAM to CPU Buffer (Made for screen modes 8 to 12)
extern 	void 	LMCM5( void *buffer, unsigned int XS, unsigned int YS, unsigned int NX, unsigned int NY, char OP);						// Logical Move from VRAM to CPU Buffer (Made for screen modes 5 and 7)

extern  void 	VDPLINE( unsigned int DX,  unsigned int DY, unsigned int NX,  unsigned int NY, char COL, char PARAM, char OP); 			// VDP Command to draw a line. Sub routine used by Line Fucntion

extern	void 	fLMMM( MMMtask *VDPtask ) __z88dk_fastcall __naked;							// fast copy by structure

extern void  	fVDP(void *Address)  __z88dk_fastcall  __naked;								// Fast VDP Command function by structure
                                          				
static void     VDPready() __naked															// Check if MSX2 VDP is ready (Internal Use)
{ 
__asm 
    checkIfReady:
    ld  a,#2
    out (#0x99),a           ; wait till previous VDP execution is over (CE)
    ld  a,#128+#15
    out (#0x99),a
    in  a,(#0x99)
   	rra						; check CE (bit#0)
    ld	a, #0				
    out (#0x99),a
    ld  a,#128+#15
    out (#0x99),a
    jp		c, checkIfReady
    ret
__endasm; 
}


#endif
