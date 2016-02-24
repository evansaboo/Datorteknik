/*
 * Player functions.
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg
 */

#include "player.h"
#include "draw.h"
#include "inputs.h"

char y = 15; // Y coordinate
char gravity = 2; // Gravity

char sprite[8][8] = {
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0}
};

/*
 * Limits y to stay in bounds.
 */
void limit_y(void) {
    y = (y < PLAYER_HEIGHT / 2 ? PLAYER_HEIGHT / 2 : y);
    y = (y > 31 - PLAYER_HEIGHT / 2 ? 31 - PLAYER_HEIGHT / 2 : y);
}

/*
 * Updates the player.
 */
 int player_update(void) {
    if (button_pressed(3)) {
        y -= gravity;
    } else {
        y += gravity;
    }

    limit_y();
    return y;
 }

/*
 * Draws the player at a specified x coordinate.
 */
 void player_draw(char x) {
    //draw_fill_rectangle(x - PLAYER_WIDTH / 2 , y - PLAYER_HEIGHT /2, x + PLAYER_WIDTH / 2 , y + PLAYER_HEIGHT /2);
    draw_sprite(x - PLAYER_WIDTH / 2, y - PLAYER_HEIGHT / 2, sprite);
 }

void player_init(){
    y = 15;
}
