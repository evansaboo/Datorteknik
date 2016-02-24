/*
 * Functions needed for handling the display.
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg
 */

#ifndef _DISPL_H
#define _DISPL_H

/*
 * Constants
 */

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32

/*
 * General functions
 */

char display_matrix[DISPLAY_WIDTH][DISPLAY_HEIGHT];

void display_init();
void display_reset();
void display_update();

/*
 * Painting functions
 */

void display_paint(char x, char y);
void display_clear(char x, char y);
void display_set(char x, char y, char value);
char display_get(char x, char y);

/*
 * Advanced drawing functions.
 */

void display_draw_line(char x1, char y1, char x2, char y2);
void display_draw_square(char x1, char y1, char x2, char y2);
void display_fill_square(char x1, char y1, char x2, char y2);
void display_draw_circle(char x, char y, char radius);
void display_fill_circle(char x, char y, char radius);

/*
 * Testing functions
 */

void display_test();

#endif
