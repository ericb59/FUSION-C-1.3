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
|                                            FUSION-C v1.0  |
\___________________________________________________________/
*/
// Example : Calling a Dos Program with arguments
// 
// Call the program with command line arguments
// >argument test1 test2 test3
//
// You must compil with crt0_msxdos_advanced.rel Option


#include <stdio.h>

int main(char *argv[], int argc)
{
  char i;

  if (argc>1)
  {
    for ( i = 0; i < argc; ++i)
    {
      printf("Argument Numb %d passed : %s \n\r",i,argv[i]);
    }

  }

  return(0);
}