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
// Example : Some console functions
//
// Works on MSX1 and upper  
//
#include <stdio.h>
#include "fusion-c/header/msx_fusion.h"

 DATE mydate;


void main(void)
{
  char surname[20];
  char age[2];

 

  //Screen(0);
  Width(40);
  Cls();

  GetDate (&mydate);
  Locate (0,0);
  Print("Current Date : ");
  PrintDec(mydate.year);
  PrintChar('-');
  PrintDec(mydate.month);
  PrintChar('-');
  PrintDec(mydate.day);

  Print("\n\rHello ...");
  Locate (3,5);
  Print("What is you surname ? :");
  InputString(surname,19);


  Cls();
  Beep();
  Print("Nice to meet you ");
  Print(surname);

  Locate (3,5); 
  Print("How old are you ?:");
  InputString(age,5);
  Locate(3,6);
  PrintDec(95);
  Print("...");
  PrintChar('?');
  Print("\n\r You 're so Old !!");


  Exit(0);

}