// Interrupt functions Test
// Fusion-c 1.3

#include "fusion-c/header/msx_fusion.h"
#include <stdio.h>





static unsigned int count = 0;

/* --------------------------------------------------------- */
void my_interrupt( void ) {
  count++;  
}

/* --------------------------------------------------------- */
int main( void ) {
  unsigned int prev_count;
  
  Cls();
  printf("Interrupt test, hold ESC to exit...\r\n");
  
  InitInterruptHandler((int)my_interrupt);

  prev_count = 0;
  while( prev_count < 600 ) {
    
   if (prev_count != count)
   {
      DisableInterrupt();
      prev_count = count;
      EnableInterrupt();
      Locate(10,2);
      printf( "%d\n\r", prev_count );     
   }
   if (Inkey()==0x1b)
         break;
  }
  EndInterruptHandler();
  Locate(1,3);
  printf("Done!\r\n");
  return 0;
}
