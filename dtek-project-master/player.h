/*
 * Functions needed for handling the player.
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg
 */

#ifndef _PLAYER_H
#define _PLAYER_H

/*
 * Player width in pixels.
 */
#define PLAYER_WIDTH 8

/*
 * Player height in pixels.
 */
#define PLAYER_HEIGHT 6

/*
 * Updates the player.
 * Returns the players current y position
 */
int player_update(void);

/*
 * Draws the player at a specified x coordinate.
 */
void player_draw(char x);

void player_init();

#endif
