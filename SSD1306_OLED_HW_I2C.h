/*
** SSD1306_OLED_HW_I2C — a minimalistic adaptation of Neven Boyanov’s SSD1306 library (http://tinusaur.org)
** for ATmega328P-based boards
** Version 2.0
** Author: Ilya Perederiy
** Licence: open source (see LICENSE.txt for details)
** former repository: https://bitbucket.org/paraglider/ssd1306_oled_hw_i2c/
** current repository: https://github.com/ex-punctis/SSD1306_OLED_HW_I2C/

Credits from the original SSD1306 library:

  * Copyright (c) 2016 Neven Boyanov, Tinusaur Team. All Rights Reserved.
  * Distributed as open source software under MIT License, see LICENSE.txt file.
  * Please, as a favor, retain the link http://tinusaur.org to The Tinusaur Project.
  * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled

  * NUM2STR - Function to handle the conversion of numeric vales to strings.
  * @created	2014-12-18
  * @author	Neven Boyanov
  * @version	2016-04-17 (last modified)
  * NOTE: This implementation is borrowed from the LCDDDD library.
  * Original source code at: https://bitbucket.org/boyanov/avr/src/default/lcdddd/src/lcdddd/lcdddd.h
*/


#ifndef SSD1306_h
#define SSD1306_h

#define OLED_CMD_SET_COLUMN_RANGE       0x21        // can be used only in HORZ/VERT mode - follow with 0x00 and 0x7F = COL127
#define OLED_CMD_SET_PAGE_RANGE         0x22        // can be used only in HORZ/VERT mode - follow with 0x00 and 0x07 = PAGE7

#define D_ADDRESS_PLUS_W_BIT            0x78        // I2C slave address + 0 bit (write)
#define ERROR_LED_PIN                      4        // LED pin to indicate I2C error (2-7)
#define ERROR_LED_PORT					PORTD	 	// Port of error LED

#define USINT2DECASCII_MAX_DIGITS 5

#define NO_BACKGROUND 0


#include <stdint.h>

/*
void clk_div_1(void);
void clk_div_8(void); 
*/

uint8_t usint2decascii(uint16_t, char *);

void tw_error(void);
void tw_start(uint8_t address);
void tw_tx(uint8_t data);
void tw_stop(void);

void d_start_cmd(void);
void d_start_dat(void);

void d_init(void);
void d_set_pos(uint8_t x, uint8_t row);
void d_print_char(uint16_t i, char ch, const uint8_t bmp[]);

void d_clear(void);
void d_contrast (uint8_t contrast);
void d_on(void);
void d_off(void);

void d_draw_bmp(const uint8_t bmp[]);
void d_print_str(uint8_t x, uint8_t row, char *s, const uint8_t bmp[]);
void d_print_int(uint8_t x, uint8_t row, uint16_t num, const uint8_t bmp[]);



#endif
