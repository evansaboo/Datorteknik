

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int getsw(void){
    int * filter = (int *) PORTD;
    int sw = (*filter & 0x0f00) >> 8;
    return sw & 0x0f;
}

int getbtns(void){
   int * filter = (int *) PORTD;
   int btns =(*filter & 0x00f0) >> 5;
   return btns & 0x0f;
}