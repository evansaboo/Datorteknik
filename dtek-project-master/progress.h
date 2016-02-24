/*
 * Functions needed for handling the progress indicator.
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg
 */

#ifndef _PROGRESS_H
#define _PROGRESS_H

/*
 * Constants
 */

#define PROGRESS_LEDS 8

/*
 * Variables
 */
double progress; // Current progress between 0 and 1.

/*
 * Functions
 */

void progress_init();
void progress_set(double progress);

#endif
