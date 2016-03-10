/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include "rand.h"


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
// Display initialization
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
//Game over and restart the game
void game_over(){
            int x, i;
    for (i = 0; i < 4; i++)
        for (x = 0; x < 128; x++){
           snake[i][x] = gameOverScreen[(i * 128) + x];
        }
            display_string(3, score);
    display_update(20000);
    
    char loop = 1;
    while(loop){
    if(getbtns())
        loop = 0;
    }
}

//Starts a countdown before the game begins
void countdown(){
    int i, j;
    char count[] = {0x2A, 0x033, 0x033, 0x2A};
    for(i = 0; i < 3 ; i++){
       display_string(2, count);
       for(j = 1; j < 3; j++)
            count[j] -= 1;
       display_update(0);
       quicksleep(10000000);
    }
    display_string(2, "*GO*");
}

//Activates a pxiel depending on X-axis and Y-axis
void set_pixel( int x, int y)
{
    int number = (snakeHead - (8 * ((lengthEnd + (128 * globalPage)))));
    if(number == 0){
        if(snake[x][y] & 0x01 && apple != snakeHead)
            gameOver = 1;
        else
        snake[x][y] |= 1;
    }
    
    if(number == 1){
        if(snake[x][y] & 0x02 && apple != snakeHead)
            gameOver = 1;
        else
        snake[x][y] |= 2;
    }
    
    if(number == 2){
        if(snake[x][y] & 0x04 && apple != snakeHead)
            gameOver = 1;
        else
        snake[x][y] |= 4;
    }
    
    if(number == 3){
        if(snake[x][y] & 0x08 && apple != snakeHead)
            gameOver = 1;
        else
        snake[x][y] |= 8;
    }
    
    if(number == 4){
        if(snake[x][y] & 0x10 && apple != snakeHead)
            gameOver = 1;
        else
        snake[x][y] |= 16;
    }
    
    if(number == 5){
        if(snake[x][y] & 0x20 && apple != snakeHead)
            gameOver = 1;
        else
        snake[x][y] |= 32;
    }
    
    if(number == 6){
        if(snake[x][y] & 0x40 && apple != snakeHead)
            gameOver = 1;
        else
        snake[x][y] |= 64;}
    
    if(number == 7){
        if(snake[x][y] & 0x80 && apple != snakeHead)
            gameOver = 1;
        else
        snake[x][y] |= 128;
    }
    
}

//Sets a apple on a random position on the screen
void set_apple(){
        int loop = 1;
        while (loop)
        {
            apple = rand(4096);
            while((apple >= 0 && apple <= 263) ||(apple >= 1024 && apple <= 1287) || (apple >= 2047 && apple <= 2311) || (apple >= 3071 && apple <= 3370))
            apple = rand(4096);
            
            column = (apple % (128*8)) / 8;
            page = apple / (128 * 8);
            pixel = apple - ((column * 8)  + (page * (128 * 8)));
            
            int x = page;
            int y = column;
            
            if(pixel == 0)
                if ((snake[x][y] & 1) != 1){
                    snake[x][y] |= 1;
                    loop = 0; 
                }
    
            if(pixel == 1)
                if ((snake[x][y] & 0x02) != 2){    
                    snake[x][y] |= 2;  
                    loop = 0; 
                }
            if(pixel == 2)
                if ((snake[x][y] & 4) != 4){
                    snake[x][y] |= 4;
                    loop = 0; 
                }
            if(pixel == 3)
                if ((snake[x][y] & 8) != 8){
                    snake[x][y] |= 8;
                    loop = 0; 
            }
            if(pixel == 4)
                if ((snake[x][y] & 16) != 16){
                    snake[x][y] |= 16;
                    loop = 0; 
            }
            if(pixel == 5)
                if ((snake[x][y] & 32) != 32){
                    snake[x][y] |= 32;
                    loop = 0; 
                }
            if(pixel == 6)
                if ((snake[x][y] & 64) != 64){
                    snake[x][y] |= 64;
                    loop = 0; 
            }
            if(pixel == 7)
                if ((snake[x][y] & 128) != 128){
                    snake[x][y] |= 128;
                    loop = 0; 
            }
        }  
}

//Delete a pixel on snake tails prev position 
void delete_pixel(){
    int i;
    
    page = snakeTail[0] / (128 * 8);
    column = (snakeTail[0] % (128 * 8)) / 8;
    pixel = snakeTail[0] - ((column * 8)  + (page * (128 * 8)));
    
    int x = page;
    int y = column;
    
    if(pixel == 0)
        snake[x][y] ^= 1;
    
    if(pixel == 1)
        snake[x][y] ^= 2;
    
    if(pixel == 2)
        snake[x][y] ^= 4;
    
    if(pixel == 3)
        snake[x][y] ^= 8;
    
    if(pixel == 4)
        snake[x][y] ^= 16;
    
    if(pixel == 5)
        snake[x][y] ^= 32;
    
    if(pixel == 6)
        snake[x][y] ^= 64;
    
    if(pixel == 7)
        snake[x][y] ^= 128;

    
    for(i = 0; i < (snakeLength - 1); i++)
        snakeTail[i] = snakeTail[i+1];
    snakeTail[snakeLength - 1] = snakeHead;
}
// Add a point to current score
void addPoint(){
    score[3] += 1;
    scoreLed += 1;
    int i;
    for(i = 3; i >= 0; i--){
    if(score[i] > 0x39)
    {
        score[i] = 0x030;
        score[i-1] = score[i-1] + 1;
    }
    }

}

//Snake moving to 4 positions
void snake_length()
{
    switch(buttonStatus){
        case 0: // ormen rör sig uppåt
              if (globalPage > 0 && (snakeHead % 8 == 0))
                {
                if (snakeHead == apple) {
                        addPoint();
                    snakeLength++;
                    set_apple();
                    snakeTail[snakeLength - 1] = snakeHead;
                }
                else
                    delete_pixel();
                    globalPage--;
                    snakeHead -= ((128 * 7) + 121);
                    set_pixel(globalPage, lengthEnd);
                    break;
                }
                if (snakeHead == apple) {
                        addPoint();
                    snakeLength++;
                    set_apple();
                    snakeTail[snakeLength - 1] = snakeHead;
                }
                else
                    delete_pixel();
                snakeHead--;
                set_pixel(globalPage, lengthEnd);
                break;
            
        case 1: // ormen rör sig åt höger
                if (snakeHead == apple) {
                        addPoint();
                    snakeLength++;
                    set_apple();
                    snakeTail[snakeLength - 1] = snakeHead;
                }
                else
                    delete_pixel();
            lengthEnd++;
            snakeHead += 8;
            set_pixel(globalPage, lengthEnd);
            break;
            
        case 2: // ormen rör sig nedåt
            if (globalPage < 3 && (snakeHead % 8 == 7))
            {
                if (snakeHead == apple) {
                        addPoint();
                    snakeLength++;
                    set_apple();
                    snakeTail[snakeLength - 1] = snakeHead;
                }
                else
                    delete_pixel();
                globalPage++;
                snakeHead += ((128 * 7) + 121);
                set_pixel(globalPage, lengthEnd);
                break;
            }
            if (snakeHead == apple) {
                    addPoint();
                    snakeLength++;
                    set_apple();
                    snakeTail[snakeLength - 1] = snakeHead;
                }
                else
                    delete_pixel();
            snakeHead++;
            set_pixel(globalPage, lengthEnd);
            break;
        case 3: // ormen rör sig åt vänster
            if (snakeHead == apple) {
                    addPoint();
                    snakeLength++;
                    set_apple();
                    snakeTail[snakeLength - 1] = snakeHead;
                }
                else
                    delete_pixel();
            lengthEnd--;
            snakeHead -= 8;
            set_pixel(globalPage, lengthEnd);
            break; 
    }
} 

//Update I/O shield screen
void display_update(int value) {
	int i, j;

	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x00);
		spi_send_recv(0x10);
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 128; j++){
			spi_send_recv(snake[i][j]);
                        quicksleep(value);
                         
		}
	}
}

//Display any string related value depending on page 1-4.
void display_string(int line, char *s) {
	int i, k, c;
	if(!s)
		return;
        
	for(i = 0; i < 4; i++){
		if(*s) {
			textbuffer[i] = *s;
			s++;
                  c = textbuffer[i];
			if(c & 0x80)
				continue;
			
			for(k = 0; k < 8; k++)
				snake[line][i*8 + k] = font[c*8 + k];
        }
}
}
