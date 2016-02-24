#ifndef OBST_H
#define OBST_H

/*
 * Initializes obstacles.
 */
void obstacle_init(void);

/*
 * Updates obstacles.
 */
void obstacle_update(int cycle);

/*
 * Draws obstacles on the display.
 */
void obstacle_draw(void);

/*
 * Checks for a collision between the player and
 * the terrain at a given altitude/height and x-position.
 * Returns 1 if there is a collision or 0 otherwise.
 */
char obstacle_collision(char x, char altitude);

#endif