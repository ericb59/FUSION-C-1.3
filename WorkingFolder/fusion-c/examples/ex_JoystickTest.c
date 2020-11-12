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
// Example : Testing the Joystyick 0 (Arrow keys)
// use arrow key during the program is runing
//
// Works on MSX1 and upper  

#include <stdlib.h>
#include <stdio.h>
#include "fusion-c/header/msx_fusion.h"


// Generates a pause in the execution of n interruptions.
// PAL: 50=1second. ; NTSC: 60=1second. 
void wait(unsigned int cicles) {
  unsigned int i;

  for(i=0;i<cicles;i++) 
  {
      while(Vsynch()==0)
        {}
    }
}

void ft_UP(void)
{
    Locate (20,5);
    Print("O");
    Locate (20,6);
    Print("|");
}
void ft_DOWN(void)
{
    Locate (20,8);
    Print("|");
    Locate (20,9);
    Print("O");
}
void ft_RIGHT(void)
{
    Locate (22,7);
    Print("-");
    Locate (23,7);
    Print("O");
}
void ft_LEFT(void)
{
    Locate (18,7);
    Print("-");
    Locate (17,7);
    Print("O");
}

void ft_direction (char a)
{
       switch (a) 
        {
            case 0:
                Cls();
                break;
            case 1:
                ft_UP();
                break;
            case 2:
                ft_UP();
                ft_RIGHT();
                break;
            case 3:
                ft_RIGHT();
                break;
            case 4:
                ft_RIGHT();
                ft_DOWN();
            case 5:
                ft_DOWN();
                break;
            case 6:
                ft_DOWN();
                ft_LEFT();
                break;
            case 7:
                ft_LEFT();
                break;
            case 8:
                ft_LEFT();
                ft_UP();
                break;
            default:
                Cls();
        
        }
}

void main(void)
{ 

    
    int a;
    int b;
    int j=0; /// Joystick to Test    

     Cls();
    

    while(Inkey()!=27)
    {

        a = JoystickRead(j);
        b = TriggerRead(j);

        ft_direction(a);

        if (b!=0)
        {
         Locate (1,1);
            printf("\n\r -> FIRE");
        }

    }
    



}
