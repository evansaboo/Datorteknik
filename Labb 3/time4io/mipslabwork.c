/* mipslabwork.c

   This file written 2015 by F Lundevall

   This file should be changed by YOU! So add something here:

   This file modified 2015-12-24 by Ture Teknolog 

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
volatile int* ledinit;
volatile int* ledoutput;


char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    ledinit = (volatile int*) 0xbf886100;
    *ledinit = 0;
    ledoutput = (volatile int*) 0xbf886110;
    
    int * dinit = (int *)PORTD;
    *dinit = 1;
    int * dinput = (int *)PORTD; 
    *dinput &= 0xfe0;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  delay( 2450 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  *ledoutput = *ledoutput + 1;
  display_image(96, icon);
  labinit();
  
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
