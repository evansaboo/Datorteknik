/* mipslabwork.c

   This file written 2015 by F Lundevall

   This file should be changed by YOU! So add something here:

   This file modified 2015-12-24 by Ture Teknolog 

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

volatile int* ledinit;
volatile int* ledoutput;


/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{

    int * dinit = (int *)PORTD;
    *dinit = 1;
    int * dinput = (int *)PORTD; 
    *dinput &= 0x0fe0;
    

    
    T2CON = 0x070;
    PR2 = (80000000 / 256);
    TMR2 = 0;
    int i;
                for (i = lengthStart; i <= lengthEnd; i++)
            {
                snake[globalPage][i] = 1;
            }

    T2CONSET = 0x8000;
    
    return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
   int btnpress = getbtns();
   if(IFS(0)){
       IFS(0) = 0;
            display_update();
            display_snake();
            snake_length();
   }
  
  if(btnpress & 0x01){
      buttonStatus++;
      if (buttonStatus > 3)
          buttonStatus = 0;
      quicksleep(10000000);
  }   
  else if(btnpress & 0x02)
  {
      buttonStatus--;
      if (buttonStatus < 0)
          buttonStatus = 3;
      quicksleep(10000000);
  }
  
  if(btnpress & 0x04){
    
  }
}
