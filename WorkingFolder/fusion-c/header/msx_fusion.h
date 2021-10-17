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
|                 V1.3 - November - 2020                    |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|                       msx_fusion.h                        |
|                                                           |
|                                                           |
|                                                           |
\___________________________________________________________/
*                         (°□°)
*   
*/ 
   
#ifndef	NULL
#define	NULL	(void *)0
#endif
 
/*_______/- Quick Reminder -\______________________________________________________________
|        
|   Logical operators:  |    or
|                       &    and
|                       ^    xor
|                       >>   Right Shifting
|                       << Left shifting 
|   Logical operators not implemented in C but must be programmed: 
|                       nor = ~(a|b);
|                       nand = ~(a&b);
|   SDCC Way to write Hexadecimal numbers:  0xFF
|   SDCC way to write binary numbers     :  0b11111001
|
|   MSX Memory pages adress under MSXDOS:
|                       page 0: #0000 - 3FFFF
|                       page 1: #4000 - 7FFFF
|                       page 2: #8000 - BFFFF
|                       page 3: #C000 - FFFFF
|
|   SDCC Interrupt Service Routines
|           void f(void) __interrupt                    : Interrupt handler can be interrupted by further interrupts
|           void f(void) __critical __interrupt(0)      : Interrupt handler can be interrupted by NMI only
|           void f(void) __critical __interrupt         : Interrupt handler can be interrupted by NMI only
|
|
|
|   Override Compilation directives with macros
|   #define __SDK_OPTIMIZATION__ 1           Compilation Priority. 0: Size of Final Program  1: Speed of the code
|   #define __SDK_ADDRCODE__ 0x106           Start Address of the Code (Default for MSX-DOS is 0x106)
|   #define __SDK_ADDRDATA__ 0x0             Start Address of the data area (Default for MSX-DOS is 0x0)
|   #define __SDK_CRT0__ crt0_msxdos.rel     CRT0 file to use for comilation. Can be any .REL file inside the folder "fusion-c/include". 
|   #define __SDK_MSXVERSION__ 2             Which pre-defined script to start with open MSX. Can be 1 to 7 (Scripts are in folder "openMSX/MSX_config/")
|   #define __SDK_AUTOEXEC__ 1               Define if an autoexec.bat file is writed to automaticaly start the compiled program when openMSX will boot
|   #define __SDK_EXT__ com                  File extension of the final compiled file program
|   #define __SDK_VERBOSE__ 2                Information printed to terminal while compile the program. 0: minimal information  1:Medium information  2: Full information
|   #define __SDK_DEST__ dsk/dska/           Destination folder where towrite the final compiled program
|
|_________________________________________________________________________________________*/   


#ifndef __MSX_FUSION__
#define __MSX_FUSION__

// Alias  replacing deleted or renamed functions's names by newest functions or equivalent functions. Trying to keep compatibility between older's versions of Fusion-c.
#define WaitForKey      WaitKey
#define KeyboardHit     Inkey
#define Getcon          InputChar
#define Getche          InputChar
#define EnableInterupt  EnableInterrupt
#define DisableInterupt DisableInterrupt
#define Rect            BoxLine
#define VpeekFirst      SetVDPread
#define VpokeFirst      SetVDPWrite
#define fcb_open        FcbOpen
#define fcb_create      FcbCreate
#define fcb_close       FcbClose
#define fcb_read        FcbRead
#define fcb_write       FcbWrite
#define fcb_find_first  FcbFindFirst
#define fcb_find_next   FcbFindNext
#define DosCLS          Cls
#define SetSC5ColorPalette   SetColorPalette 
#define SetSC5Palette        SetPalette
#define RestoreSC5Palette    RestorePalette 
#define SC5SpriteColors      SetSpriteColors 
#define SC8SpriteColors      SetSpriteColors
#define FillRam              MemFill
#define fcb_open             FcbOpen
#define fcb_create           FcbCreate
#define fcb_close            FcbClose
#define fcb_read             FcbRead
#define fcb_write            FcbWrite
#define fcb_find_first       FcbFindFirst
#define fcb_find_next        FcbFindNext
#define PSGread              PSGread
#define SetVDPWrite          SetVDPwrite 
#define PSGRead              PSGread 
#define PSGwrite             PSGwrite 
#define GetOSVersion         GetOSversion


//

// Fusion C ...
#define FCB_SUCCESS	0x00				/* return code */

/* FCB_DIR::attribute */
#define	FCB_ATTR_READONLY	0x01		/* MSX-DOS2 */
#define FCB_ATTR_HIDDEN		0x02
#define	FCB_ATTR_SYSTEM		0x04		/* MSX-DOS2 */
#define FCB_ATTR_VOLUME		0x08		/* MSX-DOS2 */
#define	FCB_ATTR_DIR		0x10		/* MSX-DOS2 */
#define	FCB_ATTR_ARCHIVE	0x20		/* MSX-DOS2 */

#define SCRMOD  			0xFCAF      /* current screen mode */
#define ACPAGE  			0xFAF6      /* active page number */
#define DPPAGE  			0xFAF5      /* display page number */
#define ATRBAS  			0xF928      /* sprite attribute table base address */
#define PATBAS 				0xF926      /* sprite pattern generator table base address */

#define  KB_RIGHT  			0x80
#define  KB_DOWN   			0x40
#define  KB_UP     			0x20
#define  KB_LEFT   			0x10
#define  KB_DEL    			0x08
#define  KB_INS    			0x04
#define  KB_HOME   			0x02
#define  KB_SPACE  			0x01 

#define CURSORKEYS     		0
#define JOYSTICK1      		1
#define JOYSTICK2     		2

#define SPACEBAR       		0
#define JOY1_BUTTONA   		1
#define JOY2_BUTTONA   		2
#define JOY1_BUTTONB   		3
#define JOY2_BUTTONB   		4

#define INACTIVE    		0
#define UP          		1
#define UP_RIGHT    		2
#define RIGHT       		3
#define DOWN_RIGHT  		4
#define DOWN        		5
#define DOWN_LEFT   		6
#define LEFT        		7
#define UP_LEFT     		8
#define UNPRESSED   		0
#define PRESSED    			255

#define MousePort1 			0x1310
#define MousePort2 			0x6C20

// Standard MSX color table number
#define TRANSPARENT   0
#define BLACK         1
#define GREEN         2
#define LIGHT_GREEN   3
#define DARK_BLUE     4
#define LIGHT_BLUE    5
#define DARK_RED      6
#define CYAN          7
#define RED           8
#define LIGHT_RED     9
#define DARK_YELLOW  10
#define LIGHT_YELLOW 11
#define DARK_GREEN   12
#define MAGENTA      13
#define GRAY         14
#define GREY         14
#define WHITE        15
 
// openMSX debug set_watchpoint read_io 0x2E
#define DEBUG_IN2E __asm__ ("in a,(0x2e)");

// Structure used with ReadMouseTo output data
typedef struct {
    signed char dx;
    signed char dy;
    char lbutton;
    char rbutton;
} MOUSE_DATA;


typedef struct {
    char joyport;           // Act as Input. Must be set to the joyport to read
    char up;
    char down;
    char left;
    char right;
    char button1;
    char button2;
    char global;
} JOY_DATA;

// Palette 
typedef struct {
    char colour;   // colour number 0..15
    char R;        // 0..7 red brightness
    char G;        // 0..7 green brightness
    char B;        // 0..7 blue brightness
} ColRGB;

typedef struct { 
    ColRGB rgb[16]; 
} Palette; 


// Logical operations (OP) for Graphic Function
#define	LOGICAL_IMP		0	// DC := SC	assign, set new colour
#define	LOGICAL_AND		1	// DC &= SC	assign with AND
#define	LOGICAL_OR		2	// DC |= SC	assign with OR
#define	LOGICAL_XOR		3	// DC ^= SC	assign with XOR
#define	LOGICAL_NOT		4	// DC = !SC	assign with NOT
// if transparent SC==0, 
#define	LOGICAL_TIMP	8	// if SC>0 then IMP
#define	LOGICAL_TAND	9	// if SC>0 then AND
#define	LOGICAL_TOR		10	// if SC>0 then OR
#define	LOGICAL_TXOR	11	// if SC>0 then XOR
#define	LOGICAL_TNOT	12	// if SC>0 then NOT


// fill logical for rectangle and circle
#define	FILL_ALL	0xFF
#define	NO_FILL		0x00

/// Globals vars
#define             _SpriteOn           (((*(char *)0xFFE7) >> 1) & 0x01)       // Returns 0 when sprites are activated, 1 when sprites are desactivated
#define             _SpriteSize         (((*(char *)0xF3E0) >> 1) & 0x01)       // Returns 0 when sprite size is 8x8, 1 when size is 16x16
#define             _SpriteMag          (((*(char *)0xF3E0)) & 0x01)            // Returns 0 when Mag is simple, 1 when sprite are double
#define             _ActivePage         (*(char *)0xFAF6)                       // Returns the active VRAM Page (MSX2)
#define             _DisplayPage        (*(char *)0xFAF5)                       // Returns the displayed VRAM Page (MSX2)
#define             _VDPfreq            (((*(char *)0xFFE8) >> 1) & 0x01)       // Returns 1 for 50 Hz, 0 for 60 Hz (MSX2)
#define             _VDPlines           (((*(char *)0xFFE8) >> 7) & 0x01)       // Returns 1 for 212 lines, 0 for 192 lines (MSX2) 
#define             _ForegroundColor    (*(char *)0xF3E9)                                      // Returns the foreground color
#define             _BackgroundColor    (*(char *)0xF3EA)                                      // Returns the background color 
#define             _BorderColor        (*(char *)0xF3EB)                                      // Returns the border color 
#define             _ScreenMode         (*(char *)0xFCAF)                                      // Returns the actual Screen mode
#define             _SpritePatternAddr  (*( (volatile unsigned int*)(0xF926)))                 // Returns Default Sprite Pattern table Address in Vram for the current screen mode
#define             _SpriteAttribAddr   (*( (volatile unsigned int*)(0xF928)))                 // Returns Default Sprite attributs table Address in Vram for the current screen mode
#define             _SpriteColorAddr    ((*( (volatile unsigned int*)(0xF928)))-512)           // Returns Default Sprite colors table Address in Vram for the current screen mode (MSX2 & upper only)
#define             _WidthScreen0       (*(char *)0xF3AE)                                      // Returns the actual Screen width for screen mode 0
#define             _WidthScreen1       (*(char *)0xF3AF)                                      // Returns the actual Screen width for screen mode 1
#define             _Time               (*(unsigned int *)0xFC9E)                              // Returns Current MSX TImer 0..65535
#define             _FusionVer          (char)13                                               // Fusion-C Version (Divide by 10 to understand version number)
#define             _FusionRev          (unsigned int)11211                                    // Fusion-C last Revision Date First digit is number of year after 2019. 2 next digits is day of revision, 2 last digits are month of revision 
#define             _TPAAddress         (*(unsigned int *)0x0006)                              // Returns the high TPA address in MSX-DOS environement (Highest ram memory address available) 
#define             _HiAddress          (*(unsigned int *)0xFC4A)                              // Returns the Highest ram memory address available for ROM dev.

/* --------------------------------------------------------- */
/* console	functions										 */
void 				bchput(char value);                                             // Internal use
void 				num2Dec16(unsigned int Number, char *address, char emptyChar); // internal use
void 				Print(char *text);												// Print a string to Text screen mode
void 				PrintFNumber(unsigned int value, char emptyChar, char length);  // Print a  Number on Screen with formating parameters to Text screen mode
void 				PrintNumber(unsigned int num);								    // Print a number on Screen to Text screen mode
char				InputChar (void);												// read char from console 
char 				InputString (char *dest, int len); 								// String input from console. dest - pointer of buffer where to store entered string. len - [0..255] is length of buffer dest, user can enter (len-2) chars, max.length=253. Returns length of string 
void				PrintChar (char c);												// display char 
void				Locate (char x, char y); 										// set cursor to x,y 
void				PrintDec (int num);												// displays signed integer value  -32768 to 32767  (larges code) 
void 				PrintHex (unsigned int num);									// Print Hexadecimal representation of the Int variable passed
void				PrintString(char* str);											// Same as Print
void 				PutCharHex(char c);												// Print Hexadecimal representation of the char variable passed								
int					CheckBreak(void);												// Check CTRL-STOP. returns 0 if CTRL-STOP was not pressed, -1 otherwise


/* --------------------------------------------------------- */
/* miscellaneous functions									 */
#define 			KeySound( data )  Poke(0xF3DB, (data) );					    // Disable/Enable Key click Sound (0|1)
#define             RealTimer()  Peekw(0xFC9E)                                      // Return the Timer value (Timer is incemented 50 or 60 times / Seconds)
#define             SetRealTimer( data )  Pokew(0xFC9E, (data ) )                   // Set The Real Timer to a specific value
void 				FunctionKeys (char n);										    // Hide or Show Function Keys (0|1)
void 				Beep(void);													    // Emit a Beep
char 				ReadMSXtype(void);											    // Read and return the MSX type (0,1,2,3)
char                ReadKeyboardType(void);                                         // Read and return the Keyboard type (0:Japanese, 1:International, 2: French, 3: UK, 4:German)
void 				ChangeCap(char n);											    // Change Cap led State (0|1)
void 				Cls(void);													    // Clear Screen
void 				Screen(char mode );								                // Define activ screen mode
void 				CovoxPlayVram(char VramPage, unsigned int StartAddress, unsigned int Length, char Speed); // Play Wav Sample stored in Vram, to Covox Module
void                CovoxPlayRam(void *StartAddress, unsigned int Length, char Speed); // Play Wav Sample stored in Ram to Covox/Simpl module
void 				RleWBToVram(unsigned int *RamAddress, unsigned int VramAddress);// RLE Decompression data to VRAM
void 				RleWBToRam(unsigned int *RamSource, unsigned int *RamDest); 	// RLE Decompression data to RAM
void                PatternRotation(void *Pattern, void *buffer, char rotation);    // 8x8 Pattern rotation. Used for the Rotation sprite pattern's function (
void                PatternHFlip(void *Pattern, void *buffer);                      // Flip Horizontally a 8x8 pixels pattern
void                PatternVFlip(void *Pattern, void *buffer);                      // Flip Vertically a 8x8 pixels pattern
void                TurboMode(char mode);                                           // Activates the 5.37 MHz Mode Only works on Panasonic FS-A1WSX, FS-A1WX, FS-A1FX. 1: To activate  0: To desactivate
void                MSXinf(void *MSXdata);

char                GetOSversion(void);                                             //get OS version   1-> MSXDOS 1.X, 2-> MSXDOS2, 0-not initiated 
void                Exit(char n) __z88dk_fastcall;                                  //  Exit program, and come back to MSX DOS, or Reseting the MSX on ROM mode

/* --------------------------------------------------------- */
/* Joystick functions										 */
char 		        JoystickRead(char joyNumber) __z88dk_fastcall;				   // Read Joystick Port (joynumber)
char 		        TriggerRead(char TriggerNumber);    		                   // Read Button state (TriggerNumber) 0:Space Barre 1:Trigger1 of JoystickA 2:Trigger2 of Joystick A 3:Trigger 1 of Joystick B  4:Trigger2 of Joystick B
unsigned int 		MouseRead(int MousePort);									   // Read Mouse Offset x and y
void		 		MouseReadTo(char MousePort, MOUSE_DATA *md); 		           // Read Mouse Offset x and y, mouse button and return to the MOUSE_DATA Structure
void 				JoystickReadTo(JOY_DATA *jd) __z88dk_fastcall;                 // Direct Joystick Read. Faster than JoystickRead. Returns Directions and buttons at the same time. 

/* --------------------------------------------------------- */
/* I/O port functions										 */
void 				OutPort( char port, char data);                             // Send data to a port
char 		        InPort( char port );                                        // Read data from a port
void 				OutPorts( char port, char *p_data, char count );            // Send a data array to a port


/* --------------------------------------------------------- */
/*	VDP functions	
*/
#define 			IsVsync() ((VDPstatusNi( 0 ) & 0x80) != 0)
#define 			IsHsync() ((VDPstatusNi( 1 ) & 0x01) != 0)
#define 			VpokeNext( data ) OutPort( 0x98, (data) )
#define 			VpeekNext() InPort( 0x98 )                                
#define             Vsynch()  ((*(char *)0xF3E7) & 0x80)                        // VBLANK detection (((*(char *)0xF3E7) >> 7) & 0x01) 
#define             SetActivePage( data ) Poke(0xFAF6, (data) )                 // Set the active Page in MSX2 Screen Mode 5 to 12
#define             SetColor( color )   ( *( (volatile char*)( 0xF3E9 ) ) = ( (char)( color ) ) )
void                SetDisplayPage(  char page ) __z88dk_fastcall;              // Set the Display Page in MSX2 Screen Mode 5 to 12
void 				SetColors ( char foreground,  char background,  char border); // Set Colors
void 				SetBorderColor( char BorderCol) __z88dk_fastcall; 		    // Set Screen 's border color
void 				VDPwrite( char vdpreg, char data ); 	                    // write to VDP Register
char 		        VDPstatus( char vdpreg ) __z88dk_fastcall;  		        // Read VDP Status Register
void 				VDPwriteNi(  char vdpreg, char data ); 	                    // write to VDP Register 
char 		        VDPstatusNi( char vdpreg ) __z88dk_fastcall;	            // Read VDP Status Register
void 				Vpoke( unsigned int address, char data );                   // Write a byte in VRAM Memory
char 		        Vpeek( unsigned int address );                              // Read a Byte in VRAM memory				
void                SetScrollMask(char n) __z88dk_fastcall;                     // Active the Horizontal Scrolling mask (MSX2+ / Turbo-R)
void                SetScrollDouble(char n) __z88dk_fastcall;                   // Active the Horizontal Scrolling on 2 VRAM Screen (MSX2+ / Turbo-R)
void 				SetScrollH(unsigned int n)__z88dk_fastcall;					// Horizontal hardware scroll MSX2 	 MSX2+ and TR
void 				SetScrollV(char n) __z88dk_fastcall;  						// Vertical hardware scroll  MSX2+ and TR
void 				Width(char n);												// Screen Width in Text mode
void 				HideDisplay(void);											// Disable Video Display (Black Screen)
void 				ShowDisplay(void);											// Enable Video Display
void 				FillVram( unsigned int Startadress, char value,  unsigned int length);		// Fill the Vram from startadress, with Value, for Length bytes. Not using Bios
void 				PutText( int X, int Y,  char *str, char LogOp );			// Print Text string on Graphic screen
void				VDP50Hz(void);												// Switch MSX2 VDP to 50hz (PAL) Mode
void				VDP60Hz(void);												// Switch MSX2 VDP to 60Hz NTSC Mode
void 				VDPlineSwitch(void);										// Switch MSX2 VDP to 192 / 212 vertical lines
void 				CopyRamToVram(void *SrcRamAddress, unsigned int DestVramAddress, unsigned int Length); // Copy a Ram Block To VRAM memory
void                CopyRamToVram2(void *SrcRamAddress, unsigned int DestVramAddress, unsigned int Length); // Copy a Ram Block To VRAM memory MSX2 Optimised Version
void                CopyRamToVram2NI(void *SrcRamAddress, unsigned int DestVramAddress, unsigned int Length);
void 				CopyVramToRam(unsigned int SrcVramAddress, void *DestRamAddress, unsigned int Length); // Copy a Vram memory block to RAM
char 		        GetVramSize(void);                                          // Return the VRAM Size of the Computer / 16 / 64 or 128
void 				SetVDPwrite(unsigned int Address) __z88dk_fastcall;         // Set the VDP Ready for Writing in VRAM
void 				SetVDPread(unsigned int Address) __z88dk_fastcall;          // Set the VDP Ready for Reading in VRAM
void                SetPalette (Palette *palette);                              // Set colors defined in given table
void                RestorePalette ( void );                                    // Sets default MSX palette
void                SetColorPalette(char ColorNumber, char Red, char Green, char Blue); // Set R,G,B Parameters of One color
void                VDPinterlace(char oddpage) ;                                // Activating Interlace mode

void                initialize_intr(void);

void                VDPalternate(char oddpage, char OnTime, char Offtime);           // Activation Alternate mode
void                SetExpandVDPcmd(char n) __z88dk_fastcall;                   // Expande MSX2+ VDP command to Screen mode 0 to 4
void                SetScreen10(char n) __z88dk_fastcall;                       // Activating MSX2+ Screen mode 10 (Activate screeen(8) before use) 
void                SetScreen12(char n) __z88dk_fastcall;                       // Activating MSX2+ Screen mode 12 (Activate screeen(8) before use)
void                SetTransparent(char n) __z88dk_fastcall;                    // Disabel or Enable Color #0 transparent mode
void                SetAdjust(signed char x, signed char y);                    // Adjust and center the screen
signed char         ReadAdjust(char xy);                                        // Return the Adjust Screen Offset on X (xy=0) or Y (xy=1)
void                FillVRM(unsigned int adr, char data, unsigned int len);     // othet fill vram function, not using the BIOS. 
void                SaveScreenBoot(char Nb);                                    // Save the Screen Parameters to the MSX2 SRAM

/* --------------------------------------------------------- */
/*	Keyboard Control  functions								 */
#define             GetKeyMatrix( data )    (*(char *)((0xFBE5+ data))) 		// Get a range of Keys from Matrix keyboard (See at the end of file for desciption
char	            WaitKey( void );											// Wait for key-press, returns key code 
char		        Inkey( void );												// Checks key-press, returns key code, otherwise 0 
void         		KillKeyBuffer(void);                   						// Erase key buffer
char                Rkeys( void );       								        // Return status of key matrix line 8. Arrow keys
char                Fkeys( void );                                              // Return status of function keys


/* --------------------------------------------------------- */
/*	String functions										 */
char                CharToLower(char ch);                                       // Return the lower version of the char ch
char                CharToUpper(char ch);                                       // Return the upper version of the char ch
void				StrToLower	( char *c );									// convert  *c string to lowercase 
void				StrToUpper	( char *c );									// convert *c string to to uppercase 
void				StrCopy( char *dst, char *src ); 							// copy string from src to dst
void				NStrCopy( char *dst, char *src, int n ); 					// copy string from src to dst with no more than n characters 
void				StrConcat( char *dst, char *src ); 							// concatenate string from src to dst 
void				NStrConcat( char *dst, char *src, int n ); 					// concatenate string from src to dst with no more than n characters 
int					StrLen( char *adr ); 										//returns length of string
int					StrCompare( char *s1, char *s2 ); 							// compares two strings s1 and s2,  returns -1 (s1<s2), 0 (s1=s2), 1 (s1>s2)  	
int					NStrCompare( char *s1, char *s2, int n ); 					// compares two strings s1 and s2, no more than n characters,  returns -1 (s1<s2), 0 (s1=s2), 1 (s1>s2)
int					StrChr( char *adr, char c );  								// returns i, for which adr[i] = c, or -1 if not found
int					StrPosStr( char *s1, char *s2 ); 							// finds substring s2 in string s1 and returns position s1[i], returns -1 if not found 
int					StrSearch( char *s1, char *s2 ); 							// returns the the first occurrence in the string s1 of any character from the string s2, or -1 if not found 
int					StrPosChr( char *adr, char c ); 							// returns the last i, for which adr[i] = c, or -1 if not found
void				StrLeftTrim( char *adr ); 									// removes left spaces
void				StrRightTrim( char *adr ); 									// removes right spaces
void				StrReplaceChar( char *adr, char c, char nc );				// replaces all chars c to nc in string adr
char*				StrReverse(char *str);                                      // Reverse the characters inside the string
char* 				Itoa(int num, char* str, int base);                         // Return the string version of a integer 


/* --------------------------------------------------------- */
/*	Type  functions   										 */

char				IsAlphaNum	(char c );										// A-Za-z0-9 
char				IsAlpha	(char c);											// A-Za-z 
char				IsAscii	(char c);											// !..~ 
char				IsCtrl	(char c);											// unprintable control symbol 
char				IsDigit	(char c);											// 0..9 
char				IsGraph	(char c);											// has graphic representation 
char				IsLower	(char c);											// lowercase test 
char				IsPrintable	(char c);										// printable test 
char				IsPunctuation (char c);									    // punctuation sign test 
char				IsSpace	(char c);											// space test 
char				IsUpper	(char c);											// uppercase test 
char				IsHexDigit(char c);										    // hex digit test 
char 				IsPositive(int c);											// Check if positive (return 1) or Negative (return -1)
float 				IntToFloat(int c);											// Return Float version of the int
void 				IntSwap(int *a, int *b);									// Swap two Int Variables
 

/* --------------------------------------------------------- */
/*	Memory  functions										 */
#define 			Poke( address, data )	( *( (volatile char*)(address) ) = ( (char)(data) ) )
#define 			Pokew( address, data )	( *( (volatile unsigned int*)(address) ) = ( (unsigned int)(data) ) )
#define 			Peek( address )			( *( (volatile char*)(address) ) )
#define 			Peekw( address )		( *( (volatile unsigned int*)(address) ) )
#define             ReadTPA()   Peekw(0x0006)                                   // Read and return High TPA Adress
char				*MemChr( char *adr, char c, int n ); 						// returns pointer to char in n bytes of adr, or NULL if not found
void				MemFill( unsigned int *adr, char c, unsigned int n ); 		// FIll mem at *adr with n bytes of c 
void				MemCopy( unsigned int *dst, unsigned int *src, unsigned int n ); // copy n bytes from src to dst 
void				MemCopyReverse( char *dst, char *src, unsigned int n ); 	// copy n bytes from src to dst From end to the begining
int 				MemCompare( char *s1, char *s2, int n ); 					// compares n bytes of s1 and s2, returns -1 (s1<s2), 0 (s1=s2), 1 (s1>s2)
void   				*MMalloc(unsigned int size);								// Memory Allocation system Adapted for MSX
											
unsigned int 		ReadSP(void); 												// Read SP register. Return the adress of the stack
char                BitReturn(char nbit, char byte);                            // Return the bit number nbit from the byte
void                BitReset(char nbit, char *byte);                            // Reset the bit nbit inside the *byte

/* --------------------------------------------------------- */
/* Interrupt	functions										 */
inline void     EnableInterrupt() 
{ 
__asm 
    ei
__endasm; 
}
inline void     DisableInterrupt() \
{
__asm 
    di
__endasm; 
}
inline void     Halt() 
{
__asm
    halt
__endasm; 
}
inline void     Suspend() 
{
__asm
    ei
    halt
    ret
__endasm; 
}

void                InitInterruptHandler(unsigned int InterruptFunctionHandler);
void                EndInterruptHandler(void);
void                InitVDPInterruptHandler(unsigned int VdpInterruptFunctionHandler);
void                EndVDPInterruptHandler(void);

/* --------------------------------------------------------- */
/*	PSG functions											 */
char 		        PSGread( char psgreg );							           // Read a PSG Register
void 				PSGwrite( char psgreg, char data);		                   // Write to a PSG Register
void 				InitPSG(void);											   // init the PSG to all 0


/* --------------------------------------------------------- */
/*	File functions		Dos Functions						 */               // http://fms.komkon.org/MSX/Handbook/th-3.txt
typedef struct {
	char	          drive_no;                                               // 1..8 If 0= Default Drive
	char	          name[8];                                                 // File Name 8 characters
	char	          ext[3];                                                 // File Extension 3 characters
	unsigned int	  current_block;                                          // used and updated by sequential read and write
	unsigned int	  record_size;                                            //
	unsigned long	  file_size;                                              // File Size in Bytes
	unsigned int	  date;                                                   // Date DOS1 / VolumeID DOS2
	unsigned int	  time;                                                   // Time DOS1 / VOlumeID DOS2
	char	          device_id;
	char	          directory_location;                                     // Indicates the order of the directory entries of a file in the directory area
	unsigned int	  start_cluster_no;                                       // Indicates the top cluster of the file in the disk.
	unsigned int	  last_access_cluster_no;                                 // Indicates the last cluster accessed.
	unsigned int	  cluster_offset;                                         // Indicates the relative location from the top cluster of the last cluster accessed
	char	          current_record;                                         // Indicates the record currently being referred to by sequential access 
	unsigned long	 random_record;
} FCB;

typedef struct {
	char	          name[8];
	char	          ext[3];
	char	          attribute;
	char	          undel_char;			/* MSX-DOS2 */
	char	          reserve[9];
	unsigned int	  time;
	unsigned int	  date;
	unsigned int	  start_cluster_no;
	unsigned long	  file_size;
} FCB_DIR;

typedef struct {
	char	drive_no;
	FCB_DIR			dirinfo;
} FCB_FIND;

char 		         FcbOpen( FCB *p_fcb );
char 		         FcbCreate( FCB *p_fcb );
char 		         FcbClose( FCB *p_fcb );
unsigned int  		 FcbRead( FCB *p_fcb, void *p_buffer, int size );
char 		         FcbWrite( FCB *p_fcb, const void *p_buffer, int size );
char 		         FcbFindFirst( FCB *p_fcb, FCB_FIND *p_result );
char 		         FcbFindNext( FCB_FIND *p_result );
char                 FcbDelete( FCB *p_fcb );

/* --------------------------------------------------------- */
/*	other MSX DOS functions									 */

typedef struct {
	int hour;	/* Hours 0..23 */
	int min;	/* Minutes 0..59 */
	int sec;	/* Seconds 0..59 */
} TIME;

typedef struct {
	int year;	/* Year 1980...2079 */
	int month;	/* Month 1=Jan..12=Dec */
	int day;	/* Day of the month 1...31 */
	int dow;	/* On getdate() gets Day of week 0=Sun...6=Sat */
} DATE;

// Strucutre used by CallSub, CallDos, CallBioos to pass and recover registers
typedef struct {
  unsigned int IX,IY,AF,DE,BC,HL;
} REGDATA;


void				GetDate (DATE *date);  										// get date 
void				GetTime (TIME *time);										// get time 
char				SetDate (int Year, char month, char day);  					// set date, returns 0 if valid 
char				SetTime (TIME *time);										// set time, returns 0 if valid 
char                GetDisk(void);                                              // gets current drive number 
char                SetDisk(int diskno);                                        // sets drive number 
void                CallBios(void *registers) __z88dk_fastcall __naked;         // Call a MSX BIOS Function thru REGDATA Structure
void                CallDos(void *registers) __z88dk_fastcall __naked;          // Call a MSX DOS Function thru REGDATA Structure
void                CallSub(void *registers) __z88dk_fastcall __naked;          // Call a MSX2 SubRom Function thru REGDATA Structure
char                SetRamDisk(char NbSegments);                                // Create or destroy a RAM DISK (MSX-DOS2 Only)
/* --------------------------------------------------------- */
/* Turbo-R functions										 */
char 		        GetCPU (void);												// Returns the CPU mode of the MSX TURBO-R   :  0=Z80 mode    1=R800 Rom Mode    2=R800 DRAM Mode
void 				ChangeCPU (char n);											// Set the CPU mode of the MSX TURBO-R
void 				PCMPlay(int start, int lenght); 							// Play a PCM sound stored in the VRAM of the MSX TURBO-R  start VRAM Adress of the begining of the PCM sound , lenght  of the PCM sample

/*--------------------------------------------------------- */



/* =============================================================================
   GetKeyMatrix
   International Matrix
  
bit  7     6     5     4     3     2     1     0
----------------------------------------------------
  0  7 &   6 ^   5 %   4 $   3 #   2 @   1 !   0 )
  1  ; :   ] }   [ {   \ |   = +   - _   9 (   8 *
  2  B     A     acent / ?   . >   , <   `     ' "
  3  J     I     H     G     F     E     D     C
  4  R     Q     P     O     N     M     L     K
  5  Z     Y     X     W     V     U     T     S
  6  F3    F2    F1    CODE  CAPS  GRAPH CTRL  SHIFT
  7  RET   SEL   BS    STOP  TAB   ESC   F5    F4
  8  Right Down  Up    Left  DEL   INS   HOME  SPACE
  9  NUM4  NUM3  NUM2  NUM1  NUM0  NUM/  NUM+  NUM*
 10  NUM.  NUM,  NUM-  NUM9  NUM8  NUM7  NUM6  NUM5



 Print() ESCAPE sequences
 Supports escape sequences:
             \a (0x07) - Beep
             \b (0x08) - Backspace. Cursor left, wraps around to previous line, 
                         stop at top left of screen.
             \t (0x09) - Horizontal Tab. Tab, overwrites with spaces up to next 
                         8th column, wraps around to start of next line, scrolls
                         at bottom right of screen.
             \n (0x0A) - Newline > Line Feed and Carriage Return (CRLF) 
                         Note: CR added in this Lib.
             \v (0x0B) - Cursor home. Place the cursor at the top of the screen.
             \f (0x0C) - Formfeed. Clear screen and place the cursor at the top. 
             \r (0x0D) - CR (Carriage Return)
            
             \" (0x22) - Double quotation mark
             \' (0x27) - Single quotation mark
             \? (0x3F) - Question mark
             \\ (0x5C) - Backslash
============================================================================= */


#endif

#ifndef __FUSIONC
#define __FUSIONC  
/* --------------------------------------------------------------------------------------------------- */
/* FUSION-C Version tag                                                                                */
static const char Done_Version_tag[]="Made with FUSION-C 1.3 R21010 (c)EBSOFT:2021";      
#endif