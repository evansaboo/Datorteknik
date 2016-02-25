/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

/* Declare a helper function which is local to this file */

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

void display_init(void) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

void snake_length()
{
    int i;
    switch(buttonStatus){
        case 0: // ormen rör sig uppåt
            if (globalPage > 0 && (snakeHead % 8 == 0))
            {
                globalPage--;
                snake[globalPage][lengthEnd] |= 128;
                snakeHead -= 121;
                break;
            }
            snake[globalPage][lengthEnd] = snake[globalPage][lengthEnd] | (snake[globalPage][lengthEnd] >> 1);
            snakeHead--;
            break;
            
        case 1: // ormen rör sig åt höger
            lengthEnd++;
            snake[globalPage][lengthEnd] |= 1;
            snakeHead += 8;
            break;
            
        case 2: // ormen rör sig nedåt
            if (globalPage < 3 && (snakeHead % 8 == 7))
            {
                globalPage++;
                snake[globalPage][lengthEnd] |= 1;
                snakeHead += 121;
                break;
            }
            snake[globalPage][lengthEnd] = snake[globalPage][lengthEnd] | (snake[globalPage][lengthEnd] << 1);
            snakeHead++;
            break;
        case 3: // ormen rör sig åt vänster
            lengthEnd--;
            snake[globalPage][lengthEnd] |= 1;
            snakeHead -= 8;
            break; 
    }
        
}
void display_update() {
	int i, j;

	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x00);
		spi_send_recv(0x10);
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 128; j++)
			spi_send_recv(icon[i*128 + j]);
                         
		}
	}

void display_snake()
{
	int i, j;  
        
        for (i = 0; i < 4; i++)
        {
            for (j = 1; j < 127; j++)
            {
                if (i == 0)
                {
                    snake[i][j] = (snake[i][j] & 0xfe) + 1;
                    icon[i*128 + j] = snake[i][j];   
                }
            if (i == 3)
            {
                snake[i][j] = (snake[i][j] & 0x7F) + 0x80;
                icon[i*128 + j] = snake[i][j];
            }
            if (i == 2 || i == 1)
                icon[i*128 + j] = snake[i][j];
        }
        }
}
