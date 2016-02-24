/*
 * Timer functions.
 *
 * All timer functions should start with the prefix "timer".
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg
 */

#include "pic32mx.h"

/*
 * Initiates a timer using timer 2.
 */
timer_init() {
    T2CON = 0x0000; // Stop timer and clear control register,
    TMR2 = 0x0000; // Clear timer register
    T2CONSET = 0x0038; // Set scale Fq: 80MHz Scale: 1:8
    PR2 = 1000000; // Load period register. Counts to 8e6 every second.
    IPCSET(0) = 0x0000000C; // Set priority level = 3
    IPCSET(0) = 0x00000001; // Set sub-priority level = 1
    // Could have also done this in single operation by assigning
    IFSCLR(0) = 0x00000100; // Clear timer interrupt status flag
    IECSET(0) = 0x00000100; // Enable timer interrupts
    T2CONSET = 0x8000;
}

/*
 * Waits for a timer to reach a certain count.
 */
timer_wait(int duration) {
    timer_init();
    while (duration > 0) {
        while (IFS(0) == 0);
        IFS(0) = 0;
        duration--;
    }
}
