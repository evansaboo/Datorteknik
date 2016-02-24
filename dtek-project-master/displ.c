/*
 * Display functions.
 *
 * All display functions should start with the prefix "display".
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg
 */
#include <stdint.h>
#include "pic32mx.h"
#include "displ.h"
#include "timer.h"

/*
 * Sends data to the display.
 */
uint8_t display_send(uint8_t data) {
    while(!(SPI2STAT & 0x08)); // Wait OK status.

    SPI2BUF = data; // Write data to buffer.

    while(!(SPI2STAT & 1)); // Wait for new status.

    return SPI2BUF; // Return buffer value.
}

/*
 * Paints a specified pixel on the screen.
 */
void display_paint(char x, char y) {
    if (x < 0 || x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT)
        return;

    display_matrix[x][y] = 1;
}

/*
 * Clears a specified pixel on the screen.
 */
void display_clear(char x, char y) {
    if (x < 0 || x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT)
        return;

    display_matrix[x][y] = 0;
}

/*
 * Sets a specified pixel to be either on or off.
 */
void display_set(char x, char y, char value) {
    if (x < 0 || x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT)
        return;

    display_matrix[x][y] = (value != 0);
}

/*
 * Gets if a specified pixel is on (1) or off (0).
 */
char display_get(char x, char y) {
    if (x < 0 || x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT)
        return;

    return display_matrix[x][y];
}

/*
 * Sleeps for a while.
 * This is very crude.
 */
void sleep(int cycles) {
    int i;
    for (i = cycles; i > 0; i--);
}

/*
 * Initializes the display.

 * The activation procedure can be found at:
 * https://digilentinc.com/Data/Products/CHIPKIT-BASIC-IO-SHIELD/chipKIT%20Basic%20IO%20Shield_rm.pdf
 * 
 * All commands can be found here:
 * https://www.adafruit.com/datasheets/SSD1306.pdf
 */
void display_init() {

    /*
     * Set up internal display resources
     */

    display_matrix[DISPLAY_WIDTH][DISPLAY_HEIGHT];

    /*
     * Enable display outputs
     */

    PORTF = 0xFFFF;
    PORTG = (1 << 9);
    ODCF = 0x0;
    ODCG = 0x0;
    TRISFCLR = 0x70;
    TRISGCLR = 0x200;

    /*
     * Enable SPI
     * Set as master
     */

    SPI2CON = 0;
    SPI2BRG = 4;
    SPI2STATCLR = 0x40;
    SPI2CONSET = 0x40;
    SPI2CONSET = 0x20;
    SPI2CONSET = 0x8000;

    /*
     * Display power on procedure
     */

    PORTFCLR = 0x10; // Display command mode
    PORTFCLR = 0x40; // Apply power to VDD

    display_send(0xAE); // Turn off display
    PORTGCLR = 0x200; // Activate display reset
    sleep(10); // Wait 10 ms for command to execute
    PORTGSET = 0x200; // Don't reset display

    display_send(0x8D); // Enable charge
    display_send(0x14);

    display_send(0xD9);
    display_send(0xF1);

    PORTFCLR = 0x20; // Activate VBAT
    timer_wait(1); // Wait 100 ms

    display_send(0xA1);
    display_send(0xC8);

    display_send(0xDA);
    display_send(0x20);

    display_send(0xAF); // Turn on display
}

/*
 * Resets the display and clears all of its data.
 */
void display_reset() {
    int x;
    int y;

    for (x = 0; x < DISPLAY_WIDTH; x++) {
        for (y = 0; y < DISPLAY_HEIGHT; y++) {
            display_matrix[x][y] = 0;
        }
    }
}

/*
 * Updates the content of the display.
 * This writes the stored data to the actual display.
 */
void display_update() {
    short x, y, value;

    for (y = 0; y < DISPLAY_HEIGHT / 4; y++) {
        PORTFCLR = 0x10; // Display command mode
        display_send(0x22); // Set page start and end address
        display_send(y); // Column to use.

        display_send(0x00); // Set lower nibble of column start address
        display_send(0x10); // Set higher part of column start address

        PORTFSET = 0x10; // Set display to data mode

        // Load and send data for each segment
        for (x = 0; x < DISPLAY_WIDTH; x++) {
            value = (display_matrix[x][y * 8] & 0b01);
            value |= (display_matrix[x][y * 8 + 1] & 0b01) << 1;
            value |= (display_matrix[x][y * 8 + 2] & 0b01) << 2;
            value |= (display_matrix[x][y * 8 + 3] & 0b01) << 3;
            value |= (display_matrix[x][y * 8 + 4] & 0b01) << 4;
            value |= (display_matrix[x][y * 8 + 5] & 0b01) << 5;
            value |= (display_matrix[x][y * 8 + 6] & 0b01) << 6;
            value |= (display_matrix[x][y * 8 + 7] & 0b01) << 7;
            display_send(value); // Send value to the display
        }
    }
}
