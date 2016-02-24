/*
 * Functions needed for drawing.
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg
 */

#ifndef _DRAW_H
#define _DRAW_H

/*
 * Draws a 1px wide line between two points.
 */
void draw_line(char x1, char y1, char x2, char y2);

/*
 * Draws the outline of a square.
 */
void draw_rectangle(char x1, char y1, char x2, char y2);

/*
 * Draws a filled square.
 */
void draw_fill_rectangle(char x1, char y1, char x2, char y2);

/*
 * Draws the outline of a circle.
 */
void draw_circle(char x, char y, char radius);

/*
 * Draws a filled circle.
 */
void draw_fill_circle(char x, char y, char radius);

/*
 * Draws a sprite (2d array) starting at (x, y).
 */
void draw_sprite(char x, char y, char sprite[8][8]);

#endif