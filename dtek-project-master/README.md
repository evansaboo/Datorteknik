# Game project for Dtek
This game project by Peter Jonsson and Lucas Ljungberg D-14 is written in C for the ChipKIT UNO32 processor with a basic I/O shield.

The game itself is based on the popular "chopper"/"copter" game in which you fly a ship through a narrow tunnel by controling its upward thrust. The tunnel itself is generated semirandomly in order to give the player a varied experience yet providing a manegable challenge that keeps getting harder as the player progresses.

## Using the display
This game project relies on utilizing the provided 128x32 pixels LCD display onboard the I/O shield. Interfacing it is done through the C code inside of the `displ.c` file, that implements the functions described by the C header file `displ.h`.

Pixels can be either on or off, and clearing the display is done automatically once every drawing cycle. This means that all pixels start as being off, and have to be enabled afterwards. There are, however, functions for turning off specific pixels, although it is recommended to just draw what is needed to begin with as this will increase performance.

Display data is stored in an array before being sent to the actual hardware using an SPI connection. 

## Other features

### LED progress indicator
Current progress is displayed using the eight LEDs on the ChipKIT UNO32 I/O shield. This is done by lighting up LEDs from the left to right.

### Inputs
The game uses the buttons and switches that are located on the basic I/O shield. They are easily interfaced from the files `inputs.h` and `inputs.c` in order to ensure optimal and consistent function throughout the application.

### Sprites
The game handles the drawing of 8 by 8 pixel sprites through the use of 2-dimentional arrays. The data is stored on the form of `sprite[x][y]` where `x` is the x coordinate within the sprite, `y` is the y coordinate within the sprite, and `sprite` is a 2D array. In order to create a sprite that is facing to the right on the display, the sprite should contain data so that it appears to be facing down in the code. This is due to the way x and y coordinates are represented inside the sprite. This is done to keep it consistent with the way that the display handles the data in its data array.

## Planned features
The game will feature randomly generated levels that are endless. There might however be an increase in general difficulty over time. 
