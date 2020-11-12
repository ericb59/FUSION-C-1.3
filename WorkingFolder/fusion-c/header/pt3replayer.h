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
|                     V1.3 - 04-05 2020                     |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|                       pt3replayer.h                       |
|            PT3 Music Player + AyFX Sound  FX Player       |
|                                                           |
\___________________________________________________________/
*                         (°□°)
* PT3 Replayer based on SDCC Version done by Mvac7303 : https://github.com/mvac7/SDCC_PT3player
* AYFX Player based on SDCC VErsion done by Néstor Sancho : https://github.com/theNestruo/msx-msxlib/tree/master/libext
*/

#ifndef  __PT3_PLAYER_H__
#define  __PT3_PLAYER_H__

// AYFX Player Variables --------------------------------------------------------------------------------
extern char ayFX_PRIORITY;        // Current ayFX stream priotity
extern char ayFX_MODE;            // ayFX mode
extern char ayFX_NOISE;           // Current noise of the ayFX stream
extern char ayFX_VOLUME;          // Current volume of the ayFX stream
extern char ayFX_CHANNEL;         // PSG channel to play the ayFX stream
extern unsigned int ayFX_BANK;    // Current ayFX Bank
extern unsigned int ayFX_POINTER; // Pointer to the current ayFX stream
extern unsigned int ayFX_TONE;    // Current tone of the ayFX stream


// PT3player  Variables --------------------------------------------------------------------------------
extern char ChanA[29]; //CHNPRM_Size
extern char ChanB[29];
extern char ChanC[29];			


extern char DelyCnt;
extern unsigned int CurESld;		
extern char CurEDel;


//Ns_Base_AddToNs:
extern char Ns_Base;		
extern char AddToNs;		


extern char AYREGS[14];
extern unsigned int EnvBase;
extern char VAR0END[240];

/* --- Workarea --- (apunta a RAM que estaba antes en codigo automodificable)
 -El byte de estado en SETUP deberia ser algo asi (CH enable/disable no esta aun)
|EP|0|0|0|CH3|CH2|CH1|LP|
LP: Loop enable/disable. A 1 si queremos que el tema suene solo una vez. 
EP: End point. A 1 cada vez que el tema acaba. 
CH1-CH3: Channel enable/disable. A 1 si no queremos que suene el canal. (AUN  NO VA!!)
*/

extern char PT3_SETUP; /* set bit0 to 1, if you want to play without looping
				           bit7 is set each time, when loop point is passed           */
extern unsigned int PT3_MODADDR;	 //direccion datos canción
extern unsigned int PT3_CrPsPtr;  //POSICION CURSOR EN PATTERN
extern unsigned int PT3_SAMPTRS;  //sample info?
extern unsigned int PT3_OrnPtrs;  //Ornament pattern

extern unsigned int PT3_PDSP;     //pilasave
extern unsigned int PT3_CSP;      //pilsave2
extern unsigned int PT3_PSP;      //pilsave3
  
extern char PT3_PrNote;
extern unsigned int PT3_PrSlide;
  
extern unsigned int PT3_AdInPtA;  //play data pattern
extern unsigned int PT3_AdInPtB;  //play data
extern unsigned int PT3_AdInPtC;  //play data
  
extern unsigned int PT3_LPosPtr;  //Position Ptr?
extern unsigned int PT3_PatsPtr;  //Pat Ptr

extern char PT3_Delay;            //delay
extern char PT3_AddToEn;          //Envelope data (No cal ya que no usa Envs??)
extern char PT3_Env_Del;          //Envelope data (idem)
extern unsigned int PT3_ESldAdd;  //Envelope data (idem)


//extern char NoteTable[192];       //Note table



void PT3FXInit(void *BankAddr, char Channel);         			   // Init The SoundBank. *BankAddr: Address of the sound Bank 
void PT3FXPlay(char sound, char priority);            // Play a Sound from 0 to 255.   Priority from 0 to 15
void PT3FXRout(void);                                 // Rout the Sounds to the PSG. Must be part of your main routine, or Execute on each interruption of VBLANK
void PT3Init(void *SongAddr, char loop);              // Init the PT3 music.  *SongAddr : Address of the Song. Loop The music : 1=On  0=Off
void PT3Rout(void);                                   // Rout the Music notes to the PSG. Must be part of your main routine, or Execute on each interruption of VBLANK
void PT3Play(void);                                   // Play/Update The music. Must be Part of your Main routine
void PT3Mute(void);                                   // Mute the Music Sound. To mute the music, Execute MutePT3 and stop invoking PT3Play



#endif