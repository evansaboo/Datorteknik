#include <pic32mx.h>
#include <stdint.h>


#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

char snake[4][128];
int lengthp = 8;
int lengthm = 4;
char icon[] = {
    255, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 255,
    255, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 255,
    255, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 255,
    255, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 128, 
    128, 128, 128, 128, 128, 128, 128, 255,
};

void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void display_init() {
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

/*void snake_update(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	
	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;

}*/

/*void display_image(int x, const uint8_t *data) {
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;
		
		for(j = 0; j < 128; j++)
			spi_send_recv(data[i*128 + j]);
	}
}*/
void snake_length()
{
    int i;
            snake[2][lengthm-1] = 0;
        for (i = lengthm; i < lengthp; i++)
        {
            snake[2][i] = 1;
        }
    lengthp++;
    lengthm++;
}
void display_update() {
	int i, j, k;
	int c;
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

int main(void) {
	/* Set up peripheral bus clock */
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	
	/* Clear SPIROV*/
	SPI2STATCLR &= ~0x40;
	/* Set CKP = 1, MSTEN = 1; */
        SPI2CON |= 0x60;
	
	/* Turn on SPI */
	SPI2CONSET = 0x8000;
	
	display_init();
        while(gameOver == 0)
        {
            display_update();
            quicksleep(10000000);
            display_snake();
            snake_length();
	}
	for(;;) ;
	return 0;
}

