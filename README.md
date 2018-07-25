# SSD1306_OLED_HW_I2C 
## A minimalistic adaptation of Neven Boyanov’s SSD1306 library (http://tinusaur.org) for ATmega328P-based boards

## Description

This library is designed to control a 128x64 OLED display with an SSD1306 controller over I2C. In essence, it is a minimalistic adaptation of a library written for ATTiny85 and similar micro-controllers by Neven Boyanov (http://tinusaur.org). The purpose of this adaptation is to reduce the memory footprint, and add hardware support for I2C communication on ATmega328P-based boards. The library can be used with Arduino IDE or in a plain C environment. I have tested it on a Chinese "Arduino Nano" clone and on a bare ATmega328P chip (running with an internal 8 MHz oscillator).

## Installation

`git clone https://github.com/ex-punctis/SSD1306_OLED_HW_I2C` 
or download the repository as a zip file.

### Arduino IDE

Create a folder for your project and move `SSD1306_OLED_HW_I2C.c`, `SSD1306_OLED_HW_I2C.h` and `demo.ino` to your folder. Rename `demo.ino` such that it agrees with the folder name. Rename `SSD1306_OLED_HW_I2C.c` to `SSD1306_OLED_HW_I2C.cpp`

Modify the .ino file to your liking and upload as usual.

### AVR-GCC environment (advanced)

You'll need the following files in your project folder: `SSD1306_OLED_HW_I2C.c`, `SSD1306_OLED_HW_I2C.h`, `main.c` and `Makefile`. `main.c` contains demo code which you can replace with your own.

Assuming the avr-gcc toolchain has been set up properly, you can compile with `make all` in terminal. If you have a usbasp programmer, the firmware will be automatically uploaded (tested on Mac OS Sierra). If you have a different programmer you will need to either modify the programmer descriptor in the makefile or use `avrdude` with your custom options.

## Reference

The following functions have been implemented in v2.0:

* initialize display `d_init();`
* clear display `d_clear();`
* turn off (sleep) `d_off();`
* turn on (wake up) `d_on();`
* change brightness (same as contrast) `d_contrast (0-255 or 0x00-0xFF);`
* display 128x64 bitmap `d_draw_bmp (bitmap_array);`
	* declare the bitmap_array as `const uint8_t bitmap_array [] PROGMEM = {  }`
	* to obtain a bitmap byte array, use gimp or another editor to make a 128x64 monochrome image, then use http://en.radzio.dxp.pl/bitmap_converter/ to get a byte array
* print string (8x6 ascii font)	`d_print_str(x coordinate, character row, “string”, bitmap_array or NO_BACKGROUND);`
	* x coordinate 0-127
	* character row 0-7
	* if you want the background image to be visible behind the text, specify the name of the bitmap array as the last argument; otherwise use `NO_BACKGROUND`.
* print variable (integers only)	`d_print_int(x coordinate, character row, integer or int variable, bitmap_array or NO_BACKGROUND);`
	* x coordinate 0-127
	* character row 0-7
	* if you want the background image to be visible behind the text, specify the name of the bitmap array as the last argument; otherwise use `NO_BACKGROUND`.

## List of changes between v1 and v2.0

* made function names lowercase
* moved demonstration code into a separate file
* added ability to display bitmaps
* removed functions for horizontal and vertical lines
* adapted d_print_int and d_print_str to have the ability to preserve the background
 
If you are interested in v1 of the library, I no longer have it, but you can find an improved version at https://github.com/greenonline/SSD1306_OLED_HW_I2C_LIB

## Credits from the original SSD1306 library:

Copyright (c) 2016 Neven Boyanov, Tinusaur Team. All Rights Reserved.
Distributed as open source software under MIT License, see LICENSE.txt file.
Please, as a favor, retain the link http://tinusaur.org to The Tinusaur Project.
Source code available at: https://bitbucket.org/tinusaur/ssd1306xled

NUM2STR - Function to handle the conversion of numeric vales to strings.
@created	2014-12-18
@author	Neven Boyanov
@version	2016-04-17 (last modified)
NOTE: This implementation is borrowed from the LCDDDD library.
Original source code at: https://bitbucket.org/boyanov/avr/src/default/lcdddd/src/lcdddd/lcdddd.h