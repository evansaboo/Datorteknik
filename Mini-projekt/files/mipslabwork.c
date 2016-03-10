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
/* Game-specific initialization goes here */
void labinit( void )
{   
    ledinit = (volatile int*) 0xbf886100;
    *ledinit = 0;
    ledoutput = (volatile int*) 0xbf886110;
    
    int * dinit = (int *)PORTD;
    *dinit = 1;
    int * dinput = (int *)PORTD; 
    *dinput &= 0x0fe0;
    
    T2CON = 0x070;
    PR2 = (80000000 / 256 / 10);
    TMR2 = 0;
    
    int x, i;
    
    /*initialize game track*/
    for (i = 0; i < 4; i++)
        for (x = 0; x < 128; x++)
           snake[i][x] = icon[(i * 128) + x]; 
    
    /*initialize snake*/
     for (i = lengthStart; i <= lengthEnd; i++)
        snake[globalPage][i] = 1;
    
    for(i = 0; i < (snakeLength); i++)
        snakeTail[i] = snakeHead - (8 * ((lengthEnd - lengthStart) - (i)));
    
    T2CONSET = 0x8000;
    /*Initialize apple*/
         set_apple();
     
   /*Display score on page 1*/
   display_string(0, score);
   
   /*Countdown before game begins*/
   countdown();
    return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
    int nextButton;
   int btnpress = getbtns();
   if(IFS(0)){
       IFS(0) = 0;
            snake_length();
            display_string(0, score);
            display_update(0);
            nextButton += 1;
            *ledoutput = scoreLed;
   }
               
   while(getsw() & 0x08); // Pause the game
   
   if(nextButton > 2){
    if((btnpress & 0x01) && (prevButtonStatus ^ (btnpress & 0x01))){    
      buttonStatus++;
      nextButton = 0;
      if (buttonStatus > 3)        
          buttonStatus = 0;
  }   
    else if((btnpress & 0x02) && (prevButtonStatus1 ^ (btnpress & 0x02)))
    {
      buttonStatus--;
      nextButton = 0;
      if (buttonStatus < 0)
          buttonStatus = 3;
    }
   }
   prevButtonStatus = (btnpress & 0x01);
   prevButtonStatus1 = (btnpress & 0x02);
   
   }

