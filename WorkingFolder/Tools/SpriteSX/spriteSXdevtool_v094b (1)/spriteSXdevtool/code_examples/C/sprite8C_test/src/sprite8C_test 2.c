/* =============================================================================
   sprite8C_test.c
   v1.0 (27 February 2014)
   Description:
    test 8x8 color sprite from spriteSX
============================================================================= */

#include "../include/newTypes.h"


// BIOS
#define _CHKRAM 0x0000
#define _CALSLT 0x001C
#define _CHGET  0x009F
#define _GTSTCK 0x00D5
#define _GTTRIG 0x00D8
#define _SNSMAT 0x0141
#define _KILBUF 0x0156

// BIOS MSX2
#define _NRDVRM 0x0174 //Reads VRAM like in RDVRM.(with full 16 bits VRAM-address)
#define _NWRVRM 0x0177 //Writes to VRAM like in WRTVRM.(with full 16 bits VRAM-address)

// Ports  
#define VDPVRAM   0x98 //VRAM Data (Read/Write)
#define VDPSTATUS 0x99 //VDP Status Registers

// System Vars
#define EXPTBL  0xFCC1
#define RG0SAV	0xF3DF	//Content of VDP(0) register (R#0)
#define RG1SAV	0xF3E0	//Content of VDP(1) register (R#1)
#define RG2SAV	0xF3E1	//Content of VDP(2) register (R#2)
#define RG3SAV	0xF3E2	//Content of VDP(3) register (R#3)
#define RG4SAV	0xF3E3	//Content of VDP(4) register (R#4)
#define RG5SAV	0xF3E4	//Content of VDP(5) register (R#5)
#define RG6SAV	0xF3E5	//Content of VDP(6) register (R#6)
#define RG7SAV	0xF3E6	//Content of VDP(7) register (R#7)
#define BSATTR  0x1E00 // sprite attribute table 
#define BSDATA  0x3800 //  sprite pattern table 
#define BSCOLOR 0x1C00 // Sprite colours



void setSprites();
void showSprites();
void setSpritesColors();
void setPalette();

void screen(char mode);
void setSpritesSize(char size);
void setSpritesZoom(boolean zoom);
void vpoke(uint address, byte value);
byte vpeek(uint address);
void vpoke_block(uint address, char* block, uint size);
void putSprite(char plane, byte x, byte y, char color, byte pattern);
void setVDP(char VDPreg, byte value);
uint _CALATR(char plane);

byte inkey();


char SPRITESIZE;




void main(void) {
 
  //color(15,1);
    
  screen(4);
  setSpritesSize(0);//8x8
  setSpritesZoom(false);     
  setPalette();
    
  setSprites();
  //fillVRAM(BASE10, 768, 32);
  
  showSprites();
  
  setSpritesColors();  // apply line colors of sprites
  
  inkey();  
}


void showSprites()
{
  byte N=6;
  byte X=0,Y=0;
  byte i=0;
  
  for(i=0;i<N;i++)
  {
    putSprite(i, X*16, Y*16, 15, i);
    X++;
    if(X==8)
    {
      X=0;
      Y++;
    }
  }

  return;
}

void setSprites()
{
// Frutas 16x

// SPRITE DATA
unsigned char SPRITE_DATA[]={
0x00,0x7E,0x5A,0x5A,0x7E,0x42,0x66,0x00,
0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C,
0x78,0xFC,0xD4,0xD4,0xFF,0xBF,0xC4,0xFC,
0x3C,0x7E,0xDB,0xDB,0xFF,0xC3,0x66,0x3C,
0x3C,0x7E,0xDB,0xDB,0xFF,0xC3,0x66,0x3C,
0x3C,0x7E,0xDB,0xDB,0xFF,0xDB,0x42,0x3C};

  vpoke_block(BSDATA,SPRITE_DATA,48); 
  
  return;
}


void setSpritesColors()
{
// Frutas 16x

// SPRITE COLORS
unsigned char COLOR_DATA[]={
0x0F,0x03,0x03,0x03,0x02,0x02,0x0C,0x0F,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0C,0x4C,0x02,0x42,0x03,0x43,0x03,0x43,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x06,0x08,0x09,0x09,0x08,0x08,0x08,0x08,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x07,0x47,0x07,0x47,0x07,0x47,0x07,0x47,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0C,0x4C,0x02,0x42,0x03,0x43,0x03,0x43,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x4F,0x4F,0x4E,0x4E,0x4F,0x4F,0x4F,0x4F,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

  vpoke_block(BSCOLOR,COLOR_DATA,96); //129 = 8 sprites *16
  
  return;
}



void screen(char mode)
{
  mode;
__asm   
  ld a,4(ix)
  call 0x005F
__endasm;
}


/* =============================================================================
 setSpritesSize
 Function : set size of the sprites
 Input    : size (char)-> 0 = 8x8;    1 = 16x16                     
============================================================================= */
void setSpritesSize(char size){
  //char i;
  byte *ramaddr= (byte *) RG1SAV; //puntero a la variable de sistema RG1SAV (valor del primer registro del VDP)
  byte vdp1;
  
  vdp1 = *ramaddr;
  
  SPRITESIZE = size;  
  
  //bit 1 - SZ - Sprite size - (0=8x8, 1=16x16)  
  if(size==1) vdp1=vdp1|2;
  else vdp1=vdp1&0xFD;
  
  setVDP(1,vdp1);
    
  return;
}



/* =============================================================================
 setSpritesZoom
 Function : set zoom of the sprites
 Input    : zoom (boolean)-> false = x1; true = zoom x2
============================================================================= */
void setSpritesZoom(boolean zoom){
  byte *ramaddr= (byte *) RG1SAV; //puntero a la variable de sistema RG1SAV (valor del primer registro del VDP)
  byte vdp1;
  
  vdp1 = *ramaddr;  
 
  //bit 0 - MAG - Sprite zoom (0=x1, 1=x2)
  if(zoom) vdp1=vdp1|1;
  else vdp1=vdp1&0xFE;
  
  setVDP(1,vdp1);
  
  return;
}


void vpoke(uint address, byte value)
{
  address;
  value;
__asm
  ld l,4(ix)
  ld h,5(ix)
  ld a,6(ix)
  call _NWRVRM
__endasm;
}


byte vpeek(uint address)
{
  address;
__asm
  ld l,4(ix)
  ld h,5(ix)
  call _NRDVRM
  ld h,#0x00
  ld l,a
__endasm;
}


void vpoke_block(uint address, char* block, uint size)
{
  //size++;    
  while (size>0)
  { 
    vpoke(address++,*(block++));
    size--;
  }
  return;
}


/* =============================================================================
 putSprite
 Function : Displays the sprite pattern.
 Input    : 
            (char) sprite plane (0-31) 
            (byte) x 
            (byte) y
            (char) color (0-15)
            (byte) pattern        
============================================================================= */
void putSprite(char plane, byte x, byte y, char color, byte pattern){
  uint vaddr;
  
  vaddr = _CALATR(plane);

  vpoke (vaddr++,y);
  vpoke (vaddr++,x);
  
  if (SPRITESIZE==1) pattern=pattern*4;
  vpoke (vaddr++,pattern);
  
  vpoke (vaddr,color);
  
  return;
}



// Provides the VRAM address, of attributes from a sprite plane.
uint _CALATR(char plane){
  uint vaddr;
  
  vaddr = BSATTR + (plane<<2);
  
  return vaddr;
}



void  setVDP(char VDPreg, byte value)
{
VDPreg;
value;
__asm
  ld   C,4(IX) ;reg
  ld   B,5(IX) ;value
     
  ld   HL,#RG0SAV
  ld   E,C
  ld   D,#0
  add  HL,DE
  ld   (HL),B ;save copy of vdp value in system var
  
  ld   A,B
  di
	out	 (#VDPSTATUS),A
	ld   A,C
  or   #0x80            ;add  A,#0x80 ;add 128 to VDP reg value
  out	 (#VDPSTATUS),A
  ei
__endasm;
}




/* ===========================================================================
espera a que se pulse una tecla
One character input (waiting)
devuelve el valor de la tecla
=========================================================================== */
byte inkey(){
__asm   
 
   call    _CHGET
   ld l,a
   
__endasm;
}



void setPalette()
{
__asm

  ld hl,#PALETTE_DATA
  xor	a
	di
	out	(#VDPSTATUS),a
	ld	a,#144
	out	(#VDPSTATUS),a
	ld	bc,#0x209A
	otir
	ei
  ret

; MSX2_Palette
; RB,G
PALETTE_DATA:
.db 0x00,0x00
.db 0x00,0x00
.db 0x11,0x05
.db 0x33,0x06
.db 0x25,0x02
.db 0x37,0x03
.db 0x51,0x02
.db 0x27,0x06
.db 0x62,0x02
.db 0x70,0x00
.db 0x63,0x06
.db 0x70,0x07
.db 0x11,0x04
.db 0x70,0x03
.db 0x66,0x06
.db 0x77,0x07

__endasm;
}