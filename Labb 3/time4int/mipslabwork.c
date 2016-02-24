/* mipslabwork.c

   This file written 2015 by F Lundevall

   This file should be changed by YOU! So add something here:

   This file modified 2015-12-24 by Ture Teknolog 

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int prime = 1234567;
int mytime = 0x5957;
volatile int* ledinit;
volatile int* ledoutput;
int timecount = 0;


char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
    if(IFS(0) & 0x0100){

        timecount++;
        if(timecount >= 10){
            time2string( textstring, mytime );
            display_string( 3, textstring );
            display_update();       
            tick( &mytime );
            timecount = 0;

        }
    }
    if(IFS(0) & 0x08000){
                *ledoutput+= 1;
    }
            IFS(0) = 0;
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    ledinit = (volatile int*) 0xbf886100;
    *ledinit = 0;
    ledoutput = (volatile int*) 0xbf886110;
    *ledoutput &= 0xff;
    
    int * dinit = (int *)PORTD;
    *dinit = 1;
    int * dinput = (int *)PORTD; 
    *dinput &= 0x0fe0;
    
    T2CON = 0x070;
    PR2 = (80000000 / 256) / 10;
    TMR2 = 0;
    
    IPCSET(2) = 0x0000001f;
    IPCSET(2) = 0x1e000000;
    
    IFSCLR(0) = 0x0100;
    IECSET(0) = 0x0900;
    
    enable_interrupt();
    T2CONSET = 0x8000;
    
    return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
 prime = nextprime( prime );
 display_string( 0, itoaconv( prime ) );
 display_update();
 
   int btnpress = getbtns();
  
  if(btnpress & 0x01){
    mytime = mytime & 0xff0f;
    mytime = mytime | (getsw() << 4);
  }
      
  if(btnpress & 0x02){
    mytime = mytime & 0xf0ff;
    mytime = mytime | (getsw() << 8);
  }
  
  if(btnpress & 0x04){
    mytime = mytime & 0x0fff;
    mytime = mytime | (getsw() << 12);
  }
}
