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
// PSG TONE TEST
//
// Works on MSX1 and Upper 
//

#include <stdio.h>
#include "fusion-c/header/msx_fusion.h"

/* --------------------------------------------------------- */
static const unsigned int tone_freq[] = {

  /* C4     D4     E4     F4     G4     A4     B4     C5  end mark */
  0x1AC, 0x17D, 0x153, 0x140, 0x11D, 0x0FE, 0x0E3, 0x0D6, 0,
};

/* --------------------------------------------------------- */
static void wait( int j ) {
  volatile int i;

  for( i = 0; i < j; i++ ) {
  }
}

/* --------------------------------------------------------- */
static void psg_init( void ) {
  int i;

  for( i = 0; i < 16; i++ ) {
    PSGwrite( i, 0 );
  }
  PSGwrite( 7, 0x3F );
}

/* --------------------------------------------------------- */
int main( void ) {
  int i;

  psg_init();
  PSGwrite( 7, 0x3E ); /* mixer */

  for( i = 0; tone_freq[i] ; i++ ) {
    printf( "tone = %03x\n", tone_freq[i] );
    PSGwrite( 0, (unsigned char)tone_freq[i] );             /* freq. low */
    PSGwrite( 1, (unsigned char)(tone_freq[i] >> 8) );      /* freq. high */
    PSGwrite( 8, 15 );                                      /* volume */
    wait( 5000 );
    PSGwrite( 8, 0 );                                       /* volume */
    wait( 1000 );
  }

  puts( "end" );
  psg_init();
  return 0;
}
