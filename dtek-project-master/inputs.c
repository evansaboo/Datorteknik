/*
 * User input functions.
 *
 * Copyright (C) 2015 Peter Jonsson <95jonpet.se>, Lucas Ljungberg
 */
#include "pic32mx.h"
#include "inputs.h"

void inputs_init(void) {

}

/*
 * Checks if a button is pressed.
 * Note that indexing is from right to left.
 */
char button_pressed(char button) {
    int buttons = (PORTD & 0x00f0) >> 4;

    switch (button) {
        case 1:
            return buttons & 0b0001;
        case 2:
            return (buttons & 0b0010) >> 1;
        case 3:
            return (buttons & 0b0100) >> 2;
        case 4:
            return (buttons & 0b1000) >> 3;
        default:
            return 0;
    }
}

/*
 * Checks if a switch is in the enabled position.
 * Note that indexing is from right to left.
 */
char switch_enabled(char switchIndex) {
    int switches = (PORTD & 0x0f00) >> 8;

    switch (switchIndex) {
        case 1:
            return switches & 0b0001;
        case 2:
            return (switches & 0b0010) >> 1;
        case 3:
            return (switches & 0b0100) >> 2;
        case 4:
            return (switches & 0b1000) >> 3;
        default:
            return 0;
    }
}
