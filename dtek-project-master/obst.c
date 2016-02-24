#include "obst.h"
#include "displ.h"
#include "pic32mx.h"
#include "player.h"
#include "rand.h"

unsigned char terrain[DISPLAY_WIDTH];
unsigned char width = 8;
unsigned char height = 20;
unsigned short maxDistance = 3;

/*
 * Variables for terrain generation.
 */
char currentWidth;
char currentOffset;
int difficulty;
char border = 1;

/*
 * Initializes obstacles.
 */
void obstacle_init(void) {
    // Reset variables.
    currentWidth = 0;
    currentOffset = border + (DISPLAY_HEIGHT - height - border * 2) / 2; // Center
    difficulty = 0;

    // Generate initial terrain.
    unsigned char i;
    for (i = 0; i < DISPLAY_WIDTH; i++) {
        terrain[i] = currentOffset;
    }
}

/*
 * Updates obstacles.
 */
void obstacle_update(int cycle) {
    // Shift terrain to the left.
    char i;
    for (i = 0; i < DISPLAY_WIDTH - 1; i++) {
        terrain[i] = terrain[i + 1];
    }

    // Randomize new terrain y-offset.
    if (currentWidth++ >= width) {
        currentWidth = 0;
        char iter = 100; // Limit iterations
        do {
            currentOffset = border + rand(DISPLAY_HEIGHT - height - border * 2);
        } while ((currentOffset - terrain[DISPLAY_WIDTH - 2]) *
         (currentOffset - terrain[DISPLAY_WIDTH - 2]) > (maxDistance * maxDistance)
         && --iter);
    }

    // Update terrain.
    terrain[DISPLAY_WIDTH - 1] = currentOffset;
}

/*
 * Draws obstacles on the display.
 */
void obstacle_draw(void) {
    unsigned char i, j;
    for (i = 0; i < DISPLAY_WIDTH; i++) {
        // Top
        for (j = 0; j <= terrain[i]; j++) {
            display_paint(i, j);
        }

        // Bottom
        for (j = terrain[i] + height; j < DISPLAY_HEIGHT; j++) {
            display_paint(i, j);
        }
    }
}

/*
 * Checks for a collision between the player and
 * the terrain at a given altitude/height and x-position.
 * Returns 1 if there is a collision or 0 otherwise.
 */
char obstacle_collision(char x, char altitude) {
    if (altitude - PLAYER_HEIGHT / 2 < terrain[x] - 1) // Top
        return 1;

    if (altitude + PLAYER_HEIGHT / 2 > terrain[x] + height) // Bottom
        return 1;

    return 0; // No collision
}

