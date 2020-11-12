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
|                     V1.3 - 02-2002 			            |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
| vdp_paint.h : FloodFill (paint) routine for MSX2 & upper  |
|       No recursivity but need a Rambuffer                 |
|                                                           |
|    Original code and routine by Dolphin_Soft 2020		    |
|                                                           |
\___________________________________________________________/
*                         (°□°)
*
*/

#ifndef __VDP_PAINT__
#define __VDP_PAINT__

// Max Paint Buffer
#define  MAXPAINT_BUFFER 250            // 250 Bytes assigned for the Paint Buffer

// Paint Structure used for Paint Buffer
typedef struct
{
  unsigned int  x1;
  unsigned int  x2;
  unsigned int  y;
} PData;

// Paint Structure use for internal use 
typedef struct 
{
  unsigned int    Pai_x1;
  unsigned int    Pai_y;
  char            Pai_BG;
  char            conditions;
  unsigned int    Pai_x2;
  char            Pai_index;
  unsigned int    MaxRam;       // Maximum allocated Ram to Paint Buffer
} PVars;

 static PData*  Paint_buf;		// Set the Paint buffer structure
 static PVars   Paint_vars;		// Set the Paint variable structure


void  		Paint(unsigned int  x, unsigned int y, char color);			// Paint Function (Mainn Routine)
int 		  PaintSearch(void *parameters)  __z88dk_fastcall __naked;			// VDP MSX2 SRCH's MSX2 Command
void   		SetPaint_Buf(char* BufAddr);								// Set the Paint Buffer
void  		PaintScan(void);													// PaintScan SubRoutine for Paint

//-----------------------------------------------------------
// MSX2 VDP Routine SRCH
//-----------------------------------------------------------
int PaintSearch(void *parameters)  __z88dk_fastcall __naked
{  parameters;
    __asm

      di
      ld a, #2
      out (#0x99), a
      ld a, #0x80+#15
      out (#0x99), a

      ld  a,  #32           
      out  (#0x99),  a      
      ld  a,  #0x80+#17  
      out  (#0x99),  a      
      ld  bc,  #0x049B            ; b=4 c=9B 

      otir                      ; out Pai_x1 and Pai_y
      
    GetPaintSearchReady:
      in  a,  (#0x99)
      and  #1
      jr  NZ,   GetPaintSearchReady    ;  Wait CE

      ld  a,  #44     
      out  (#0x99),  a     
      ld  a,  #0x80+#17   
      out  (#0x99),  a        
                 
      ld b,#2                    ; out Pai_BG & conditions
      otir

      ld  a,  #0b01100000       ;  PaintSearch
      out  (#0x9B),  a

      ld  hl,  #0xFFFF

      ld  a,  #0x80+#15  
      out  (#0x99),  a    
      ld  a,  #0x80+#17   
      out  (#0x99),  a         

    WaitPaintSearchDone:
      in  a,  (#0x99)
      and  #1
      jr  NZ, WaitPaintSearchDone    ;  Wait CE

      in  a,  (#0x99)
      and  #0x10
      jr Z,     PaintSearchDone

    ReadPaintSearchRes:
      ld  a,  #0x08      
      out  (#0x9B),  a

      in  a,  (#0x99)
      ld  l,  a

      ld  a,  #0x09      
      out  (#0x9B),  a

      in  a,  (#0x99)
      and  #1
      ld  h,  a

      ld  a,  #0x02      
      out  (#0x9B),  a
    PaintSearchDone:

      xor a
      out (#0x99), a
      ld a, #0x80+#15
      out (#0x99), a
      ei
      ret
    __endasm;
}

//-----------------------------------------------------------
// Set The Paint Buffer
//-----------------------------------------------------------
void   SetPaintBuffer(char* BufAddr)
{
  Paint_buf=(PData*)BufAddr;
  Paint_vars.Pai_index=0;
}

// Paint SubRoutine 
void  PaintScan(void)
{
      unsigned int x1=0;
      do{

        Paint_vars.conditions=0x00;
        Paint_vars.Pai_x1=PaintSearch( &Paint_vars );            // Right Dir    : Right_dir | Eq
        if(Paint_vars.Pai_x1>(Paint_vars.Pai_x2)) break;
        x1=Paint_vars.Pai_x1;
        Paint_vars.conditions=0x02;
        Paint_vars.Pai_x1=PaintSearch( &Paint_vars );            // Right Right_dir: Right_dir | NotEq
        Paint_buf[Paint_vars.Pai_index].x1=x1;
        Paint_buf[Paint_vars.Pai_index].x2=Paint_vars.Pai_x1;
        Paint_buf[Paint_vars.Pai_index++].y=Paint_vars.Pai_y;

        if (Paint_vars.Pai_index>=(Paint_vars.MaxRam-1)) Paint_vars.Pai_index--;    // Prevent Paint buffer overflow

      } while (Paint_vars.Pai_x1<Paint_vars.Pai_x2);
}

//-----------------------------------------------------------
// Main Paint routine
//-----------------------------------------------------------
void  Paint(unsigned int  x, unsigned int y, char color)
{
  unsigned int  xt=0;
  unsigned int  x1=0;
  unsigned int  x2=0;
  unsigned int  yt=0;
  unsigned int  Screen_Width=256;
  char          Pai_color=0;

  Paint_vars.Pai_index=0;
  

  Pai_color=color;
  Paint_vars.Pai_BG=Point(x,y);
  if ((*(char *)0xFCAF)==6 || (*(char *)0xFCAF)==7) Screen_Width=512;       // Set the Screen Width
  if (Pai_color==Paint_vars.Pai_BG) return;
  Paint_buf[Paint_vars.Pai_index].x1=x;
  Paint_buf[Paint_vars.Pai_index].x2=x;
  Paint_buf[Paint_vars.Pai_index++].y=y;
  do  {
          // color=(color +32) & 255; Color modification ?

          Paint_vars.Pai_x1=Paint_buf[--Paint_vars.Pai_index].x1;
          Paint_vars.Pai_x2=Paint_buf[Paint_vars.Pai_index  ].x2;
          Paint_vars.Pai_y =Paint_buf[Paint_vars.Pai_index  ].y;

         if (Point(Paint_vars.Pai_x1,Paint_vars.Pai_y)==Paint_vars.Pai_BG){
             Paint_vars.conditions=0x04  | 0x02;
             Paint_vars.Pai_x1    = PaintSearch( &Paint_vars )+1;       // PaintSearch Left Dir  : Left_dir  | NotEq
             if(Paint_vars.Pai_x1>=Screen_Width) Paint_vars.Pai_x1=0;
             Paint_vars.conditions=0x02;
             Paint_vars.Pai_x2= PaintSearch(  &Paint_vars )-1;           // Right Dir  Right_dir | NotEq
             if(Paint_vars.Pai_x2>=Screen_Width) Paint_vars.Pai_x2=Screen_Width-1;
             Line(Paint_vars.Pai_x1,  Paint_vars.Pai_y,  Paint_vars.Pai_x2,  Paint_vars.Pai_y, color, 0 );

             xt=Paint_vars.Pai_x1;
             yt=Paint_vars.Pai_y;
             Paint_vars.Pai_y=yt-1;
             PaintScan();

             Paint_vars.Pai_x1=xt;
             Paint_vars.Pai_y=yt+1;
             PaintScan();
            
       }

  } while (Paint_vars.Pai_index!=0);

}

#endif