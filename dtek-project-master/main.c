/*
 * Main file for the project.
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg 
 */
#include "pic32mx.h"
#include "gamefuncs.h"
#include "timer.h"
#include "progress.h"
#include "inputs.h"
#include "draw.h"
#include "player.h"
#include "obst.h"

int cycles = 0;

void update_temp();

/*
 * Runs the game loop one tick.
 * This is where the game logic happens.
 */
int gameLoop() {
    timer_wait(1);
    char inCollision = 0;
    int i;
    char player_x = 16;

    int test = cycles % 127; // Test progress
    // Draw border for debugging
    if (switch_enabled(1))
        draw_rectangle(0, 0, 126, 31);

    // Pause
    while(switch_enabled(4));

    progress_set((double) test / 127);

    int player_y = player_update(); // Update the player
    obstacle_update(0); // Update obstacles

    obstacle_draw();
    player_draw(player_x); // Draw the player

    // Check collisions
    for (i = -PLAYER_WIDTH; i < PLAYER_WIDTH; i++) {
        inCollision += obstacle_collision(player_x + i, player_y);
    }

    // Player death
    if (inCollision) {
        draw_fill_rectangle(0, 0, 126, 31);
        while(!button_pressed(4));
        obstacle_init();
        return 0;
    }

    cycles++;
    return 1;
}

/*
 * Initializes the game.
 */
void init() {
    inputs_init();
    display_init();
    progress_init();
    obstacle_init();
}

/*
 * The starting point of the project.
 * Warning, this function should never finish.
 */
int main() {

    init(); // Initialize everything.   

    while(1) {

        int running = 1;
        player_init();
        timer_wait(1);

        // Run the game indefinately.
        while(running) {
            display_reset(); // Clear all display data.

            running = gameLoop();

            display_update(); // Update the display.
        }

        timer_wait(1);
        display_reset();
        timer_wait(1);
    }

    return 0; // This should never be reached.
}