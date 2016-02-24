/*
 * Progress LED indicator functions.
 *
 * All progress indicator functions should start with the prefix "progress".
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg
 */
#include "pic32mx.h"
#include "progress.h"

void progress_update(); // Define local function implemented below.

/*
 * Initiates the progress indicator.
 */
void progress_init() {
    progress = 0;

    TRISE = TRISE & 0xff00; // Clear LED status.
    progress_update(); // Update progress
}

/*
 * Sets the current progress to display.
 * This should be a number between 0 and 1.
 */
void progress_set(double current) {
    if (current < 0) current = 0;
    else if (current > 1) current = 1;

    progress = current;

    progress_update();
}

/*
 * Updates the progress indicator.
 * This enables/disables the correct number of LEDs.
 */
void progress_update() {
    char leds = (char) (progress * PROGRESS_LEDS + 0.5); // Get number of LEDs to enable.

    // Create a value for enabling the right LEDs.
    int value = 0;
    int i;
    for (i = leds; i >= 0; i--) {
        value |= (1 << (PROGRESS_LEDS - i));
    }

    PORTE = value & 0x00ff; // Enable/disable LEDs. 
}
