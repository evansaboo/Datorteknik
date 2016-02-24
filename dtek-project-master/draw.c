/*
 * Drawing functions.
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg
 */
#include "draw.h"
#include "displ.h"

/*
 * Draws a 1px wide line between two points.
 */
void draw_line(char x1, char y1, char x2, char y2) {
    // TODO: Implement function using trigonometry and a loop
    // since this implementation will leave gaps in y.
    float x = x1;
    float y = y1;

    float delta = (y2 - y1) / (x2 - x1);

    while (x != x2 && y != y2) {
        display_paint(x, y);

        x += 1;
        y += 1 * delta;
    }
}

/*
 * Draws the outline of a square.
 */
void draw_rectangle(char x1, char y1, char x2, char y2) {
    char x;
    char y;

    char xMin = (x1 <= x2) ? x1 : x2;
    char xMax = (x2 >= x1) ? x2 : x1;
    char yMin = (y1 <= y2) ? y1 : y2;
    char yMax = (y2 >= y1) ? y2 : y1;

    // Horizontal lines.
    for (x = xMin; x <= xMax; x++) {
        display_paint(x, yMin);
        display_paint(x, yMax);
    }

    // Vertical lines.
    for (y = yMin; y <= yMax; y++) {
        display_paint(xMin, y);
        display_paint(xMax, y);
    }
}

/*
 * Draws a filled square.
 */
void draw_fill_rectangle(char x1, char y1, char x2, char y2) {
    char x;
    char y;

    char xMin = (x1 <= x2) ? x1 : x2;
    char xMax = (x2 >= x1) ? x2 : x1;
    char yMin = (y1 <= y2) ? y1 : y2;
    char yMax = (y2 >= y1) ? y2 : y1;

    xMin = (xMin < 0) ? 0 : xMin;
    xMax = (xMax >= DISPLAY_WIDTH) ? DISPLAY_WIDTH - 1 : xMax;
    yMin = (yMin < 0) ? 0 : yMin;
    yMax = (yMax >= DISPLAY_HEIGHT) ? DISPLAY_HEIGHT - 1 : yMax;

    for (x = xMin; x <= xMax; x++) {
        for (y = yMin; y <= yMax; y++) {
            display_paint(x, y);
        }
    }
}

/*
 * Draws the outline of a circle.
 */
void draw_circle(char x, char y, char radius) {
    // TODO: Implement method.
}

/*
 * Draws a filled circle.
 */
void draw_fill_circle(char x, char y, char radius) {
    char r = radius;

    // Repeatedly draw outline with smaller radius.
    while (r-- >= 0) {
        draw_circle(x, y, r);
    }
}

/*
 * Draws a sprite (2d array) starting at (x, y).
 */
void draw_sprite(char x, char y, char sprite[8][8]) {
    char xx, yy;
    for (xx = 0; xx < 8; xx++) {
        for (yy = 0; yy < 8; yy++) {
            if (sprite[xx][yy]) {
                display_paint(x + xx, y + yy);
            }
        }
    }
}
