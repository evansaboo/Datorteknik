/*
 * Functions needed for handling user inputs.
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg
 */

#ifndef _INPUTS_H
#define _INPUTS_H

/*
 * Initiates inputs.
 */
void inputs_init(void);

/*
 * Checks if a button is pressed.
 * Note that indexing is from right to left.
 */
char button_pressed(char button);

/*
 * Checks if a switch is in the enabled position.
 * Note that indexing is from right to left.
 */
char switch_enabled(char switchIndex);

#endif
