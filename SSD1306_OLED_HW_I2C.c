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

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "SSD1306_OLED_HW_I2C.h"

//  ASCII 6x8 font with leading zero bytes (character padding) removed
//  Each byte represents a column of 8 pixels
const uint8_t D_FONT6x8 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, // space
	0x00, 0x00, 0x2f, 0x00, 0x00, // !
	0x00, 0x07, 0x00, 0x07, 0x00, // "
	0x14, 0x7f, 0x14, 0x7f, 0x14, // #
	0x24, 0x2a, 0x7f, 0x2a, 0x12, // $
	0x62, 0x64, 0x08, 0x13, 0x23, // %
	0x36, 0x49, 0x55, 0x22, 0x50, // &
	0x00, 0x05, 0x03, 0x00, 0x00, // '
	0x00, 0x1c, 0x22, 0x41, 0x00, // (
	0x00, 0x41, 0x22, 0x1c, 0x00, // )
	0x14, 0x08, 0x3E, 0x08, 0x14, // *
	0x08, 0x08, 0x3E, 0x08, 0x08, // +
	0x00, 0x00, 0xA0, 0x60, 0x00, // ,
	0x08, 0x08, 0x08, 0x08, 0x08, // -
	0x00, 0x60, 0x60, 0x00, 0x00, // .
	0x20, 0x10, 0x08, 0x04, 0x02, // /
	0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
	0x00, 0x42, 0x7F, 0x40, 0x00, // 1
	0x42, 0x61, 0x51, 0x49, 0x46, // 2
	0x21, 0x41, 0x45, 0x4B, 0x31, // 3
	0x18, 0x14, 0x12, 0x7F, 0x10, // 4
	0x27, 0x45, 0x45, 0x45, 0x39, // 5
	0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
	0x01, 0x71, 0x09, 0x05, 0x03, // 7
	0x36, 0x49, 0x49, 0x49, 0x36, // 8
	0x06, 0x49, 0x49, 0x29, 0x1E, // 9
	0x00, 0x36, 0x36, 0x00, 0x00, // :
	0x00, 0x56, 0x36, 0x00, 0x00, // ;
	0x08, 0x14, 0x22, 0x41, 0x00, // <
	0x14, 0x14, 0x14, 0x14, 0x14, // =
	0x00, 0x41, 0x22, 0x14, 0x08, // >
	0x02, 0x01, 0x51, 0x09, 0x06, // ?
	0x32, 0x49, 0x59, 0x51, 0x3E, // @
	0x7C, 0x12, 0x11, 0x12, 0x7C, // A
	0x7F, 0x49, 0x49, 0x49, 0x36, // B
	0x3E, 0x41, 0x41, 0x41, 0x22, // C
	0x7F, 0x41, 0x41, 0x22, 0x1C, // D
	0x7F, 0x49, 0x49, 0x49, 0x41, // E
	0x7F, 0x09, 0x09, 0x09, 0x01, // F
	0x3E, 0x41, 0x49, 0x49, 0x7A, // G
	0x7F, 0x08, 0x08, 0x08, 0x7F, // H
	0x00, 0x41, 0x7F, 0x41, 0x00, // I
	0x20, 0x40, 0x41, 0x3F, 0x01, // J
	0x7F, 0x08, 0x14, 0x22, 0x41, // K
	0x7F, 0x40, 0x40, 0x40, 0x40, // L
	0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
	0x7F, 0x04, 0x08, 0x10, 0x7F, // N
	0x3E, 0x41, 0x41, 0x41, 0x3E, // O
	0x7F, 0x09, 0x09, 0x09, 0x06, // P
	0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
	0x7F, 0x09, 0x19, 0x29, 0x46, // R
	0x46, 0x49, 0x49, 0x49, 0x31, // S
	0x01, 0x01, 0x7F, 0x01, 0x01, // T
	0x3F, 0x40, 0x40, 0x40, 0x3F, // U
	0x1F, 0x20, 0x40, 0x20, 0x1F, // V
	0x3F, 0x40, 0x38, 0x40, 0x3F, // W
	0x63, 0x14, 0x08, 0x14, 0x63, // X
	0x07, 0x08, 0x70, 0x08, 0x07, // Y
	0x61, 0x51, 0x49, 0x45, 0x43, // Z
	0x00, 0x7F, 0x41, 0x41, 0x00, // [
	0x55, 0x2A, 0x55, 0x2A, 0x55, // 55
	0x00, 0x41, 0x41, 0x7F, 0x00, // ]
	0x04, 0x02, 0x01, 0x02, 0x04, // ^
	0x40, 0x40, 0x40, 0x40, 0x40, // _
	0x00, 0x01, 0x02, 0x04, 0x00, // '
	0x20, 0x54, 0x54, 0x54, 0x78, // a
	0x7F, 0x48, 0x44, 0x44, 0x38, // b
	0x38, 0x44, 0x44, 0x44, 0x20, // c
	0x38, 0x44, 0x44, 0x48, 0x7F, // d
	0x38, 0x54, 0x54, 0x54, 0x18, // e
	0x08, 0x7E, 0x09, 0x01, 0x02, // f
	0x18, 0xA4, 0xA4, 0xA4, 0x7C, // g
	0x7F, 0x08, 0x04, 0x04, 0x78, // h
	0x00, 0x44, 0x7D, 0x40, 0x00, // i
	0x40, 0x80, 0x84, 0x7D, 0x00, // j
	0x7F, 0x10, 0x28, 0x44, 0x00, // k
	0x00, 0x41, 0x7F, 0x40, 0x00, // l
	0x7C, 0x04, 0x18, 0x04, 0x78, // m
	0x7C, 0x08, 0x04, 0x04, 0x78, // n
	0x38, 0x44, 0x44, 0x44, 0x38, // o
	0xFC, 0x24, 0x24, 0x24, 0x18, // p
	0x18, 0x24, 0x24, 0x18, 0xFC, // q
	0x7C, 0x08, 0x04, 0x04, 0x08, // r
	0x48, 0x54, 0x54, 0x54, 0x20, // s
	0x04, 0x3F, 0x44, 0x40, 0x20, // t
	0x3C, 0x40, 0x40, 0x20, 0x7C, // u
	0x1C, 0x20, 0x40, 0x20, 0x1C, // v
	0x3C, 0x40, 0x30, 0x40, 0x3C, // w
	0x44, 0x28, 0x10, 0x28, 0x44, // x
	0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // y
	0x44, 0x64, 0x54, 0x4C, 0x44, // z
};


// Display initialization sequence
const uint8_t init_sequence [] PROGMEM = {
	0xAE,           // Display OFF (sleep mode)
	0x20, 0b00,     // Set Memory Addressing Mode
	                // 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
	                // 10=Page Addressing Mode (RESET); 11=Invalid
	0xB0,           // Set Page Start Address for Page Addressing Mode, 0-7
	0xC8,           // Set COM Output Scan Direction
	0x00,           // ---set low column address
	0x10,           // ---set high column address
	0x40,           // ---set start line address
	0x81, 0x00,     // Set contrast control register
	0xA1,           // Set Segment Re-map. A0=address mapped; A1=address 127 mapped. 
	0xA6,           // Set display mode. A6=Normal; A7=Inverse
	0xA8, 0x3F,     // Set multiplex ratio(1 to 64)
	0xA4,           // Output RAM to Display
	                // 0xA4=Output follows RAM content; 0xA5,Output ignores RAM content
	0xD3, 0x00,     // Set display offset. 00 = no offset
	0xD5,           // --set display clock divide ratio/oscillator frequency
	0xF0,           // --set divide ratio
	0xD9, 0x22,     // Set pre-charge period
	0xDA, 0x12,     // Set com pins hardware configuration		
	0xDB,           // --set vcomh
	0x20,           // 0x20,0.77xVcc
	0x8D, 0x14,     // Set DC-DC enable
	0xAF            // Display ON in normal mode
};


/*
// An alternative initialization sequence
const uint8_t init_sequence [] PROGMEM = {	// Initialization Sequence
<<<<<<< HEAD
	0xAE,           // Display OFF (sleep mode)
	0xA8, 0x3F,     // Set mux ratio tp select max number of rows - 64
	0xD3, 0x00,     // Set display offset. 00 = no offset
	0xA1,           // Set Segment Re-map. A0=address mapped; A1=address 127 mapped.
	0xC8,           // Set COM Output Scan Direction
	0xDA, 0x12,     // Default - alternate COM pin map
	0x81, 0x00,     // Set contrast control register
	0xA4,           // Set display to enable rendering from GDDRAM (Graphic Display Data RAM)
	0xA6,           // Set display mode. A6=Normal; A7=Inverse
	0xD5, 0x80,     // Default oscillator clock (alt 0xF0)
	0x8D, 0x14,     // Enable the charge pump
	0xD9, 0x22,     // Set pre-charge period
	0xDB, 0x30,     // Set the V_COMH deselect volatage to max (alt 0x20 for 0.77xVcc)
	0x20, 0b00,     // Set Memory Addressing Mode
	                // 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
	                // 10=Page Addressing Mode (RESET); 11=Invalid
	0xAF            // Display ON in normal mode
=======
	0xAE,			// Display OFF (sleep mode)
	0xA8, 0x3F,     // Set mux ratio tp select max number of rows - 64
	0xD3, 0x00,		// Set display offset. 00 = no offset
	0xA1,			// Set Segment Re-map. A0=address mapped; A1=address 127 mapped.
	0xC8,			// Set COM Output Scan Direction
	0xDA, 0x12,     // Default - alternate COM pin map
	0x81, 0x00,		// Set contrast control register
	0xA4,			// Set display to enable rendering from GDDRAM (Graphic Display Data RAM)
	0xA6,			// Set display mode. A6=Normal; A7=Inverse
	0xD5, 0x80,     // Default oscillator clock (alt 0xF0)
	0x8D, 0x14,     // Enable the charge pump
	0xD9, 0x22,		// Set pre-charge period
	0xDB, 0x30,     // Set the V_COMH deselect volatage to max (alt 0x20 for 0.77xVcc)
	0x20, 0b00,		// Set Memory Addressing Mode
                    // 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
                    // 10=Page Addressing Mode (RESET); 11=Invalid
	0xAF			// Display ON in normal mode
>>>>>>> 4ef57e6be2e27bc7e805cee18292f05865cace8f
};
*/

char ssd1306_numdec_buffer[USINT2DECASCII_MAX_DIGITS + 1];


/*
void clk_div_1(void) {                  // Set clock divider to 1 (fast operation)
	cli();
	CLKPR = (1<<CLKPCE);
	CLKPR = 0x00;                       // div 1
	sei();
}

void clk_div_8(void) {                  // Set clock divider to 8 (slow operation)
	cli();
	CLKPR = (1<<CLKPCE);
	CLKPR = (1<<CLKPS1)|(1<<CLKPS0);    // div 8
	sei();
}
*/


uint8_t usint2decascii(uint16_t num, char *buffer)      // convert integer to string
{
// @author	Neven Boyanov
// NOTE: This implementation is borrowed from the LCDDDD library.
// Original source code at: https://bitbucket.org/boyanov/avr/src/default/lcdddd/src/lcdddd/lcdddd.h

	const unsigned short powers[] = { 10000u, 1000u, 100u, 10u, 1u }; // The "const unsigned short" combination gives shortest code.
	char digit; // "digit" is stored in a char array, so it should be of type char.
	uint8_t digits = USINT2DECASCII_MAX_DIGITS - 1;
	for (uint8_t pos = 0; pos < 5; pos++) // "pos" is index in array, so should be of type int.
	{
		digit = 0;
		while (num >= powers[pos])
		{
			digit++;
			num -= powers[pos];
		}
		// ---- CHOOSE (1), (2) or (3) ----
		// CHOICE (1) Fixed width, zero padded result.
		/*
		//buffer[pos] = digit + '0';	// Convert to ASCII
		*/
		// CHOICE (2) Fixed width, zero padded result, digits offset.
		/*
		buffer[pos] = digit + '0';	// Convert to ASCII
		// Note: Determines the offset of the first significant digit.
		if (digits == -1 && digit != 0) digits = pos;
		// Note: Could be used for variable width, not padded, left aligned result.
		*/
		// CHOICE (3) Fixed width, space (or anything else) padded result, digits offset.
		// Note: Determines the offset of the first significant digit.
		// Note: Could be used for variable width, not padded, left aligned result.
		if (digits == USINT2DECASCII_MAX_DIGITS - 1)
		{
			if (digit == 0)
			{
				if (pos < USINT2DECASCII_MAX_DIGITS - 1)	// Check position, so single "0" will be handled properly.
					digit = -16;	// Use: "-16" for space (' '), "-3" for dash/minus ('-'), "0" for zero ('0'), etc. ...
			}
			else
			{
				digits = pos;
			}
		}
		buffer[pos] = digit + '0';	// Convert to ASCII
	}
	// NOTE: The resulting ascii text should not be terminated with '\0' here.
	//       The provided buffer maybe part of a larger text in both directions.
	return digits;
}


void tw_error(void) {                            // I2C comm error handler. Blinks ERROR_PIN in PORTD
	for (uint8_t i = 0; i < 10; i++) {
		ERROR_LED_PORT ^= 1 << ERROR_LED_PIN;
		_delay_ms(300);
	}
}


void tw_start(uint8_t address) {                 // start I2C and tell the display to await commands
	//cli();                                     // disable interrupts for the time being
	//clk_div_1();                               // increase clock speed to max
<<<<<<< HEAD

	PORTC = (1<<PC5)|(1<<PC4);                   // internal pull-ups on SDA and SCL

	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);      // start I2C
	while (!(TWCR&(1<<TWINT)));                  // wait
	if ((TWSR & 0xF8) != 0x08) tw_error();       // success or error
=======
>>>>>>> 4ef57e6be2e27bc7e805cee18292f05865cace8f

	PORTC = (1<<PC5)|(1<<PC4);                   // internal pull-ups on SDA and SCL

<<<<<<< HEAD
=======
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);      // start I2C
	while (!(TWCR&(1<<TWINT)));                  // wait
	if ((TWSR & 0xF8) != 0x08) tw_error();       // success or error


>>>>>>> 4ef57e6be2e27bc7e805cee18292f05865cace8f
	TWDR = address;                              // I2C slave address + write
	TWCR = (1<<TWINT) |(1<<TWEN);                // transmit
	while (!(TWCR & (1<<TWINT)));                // wait for transmission
	if ((TWSR & 0xF8) != 0x18) tw_error();       // success or error
}

void tw_tx(uint8_t data) {                       // transmit 1 byte
	TWDR = data;                                 // data to transmit
	TWCR = (1<<TWINT) |(1<<TWEN);                // transmit
	while (!(TWCR & (1<<TWINT)));                // wait for transmission
	if ((TWSR & 0xF8) != 0x28) tw_error();       // success or error
}




void tw_stop (void) {                            // stop I2C communication
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);      // stop
	//clk_div_8();                               // decrease CLK speed
	//sei();                                     // re-enable interrupts

	PORTC &= ~(1 << PC5);                        // disable internal pull-up
	PORTC &= ~(1 << PC4);                        // disable internal pull-up
}

void d_start_cmd(void) {                         // start I2C and tell the display to await commands
	tw_start(D_ADDRESS_PLUS_W_BIT);
	tw_tx(0x00);                                 // prep command stream: C0=0 D/C#=0, followed by 6 zeros (datasheet 8.1.5.2)
}

void d_start_dat(void) {                         // Start I2C and tell the display to await data (pixels)
	tw_start(D_ADDRESS_PLUS_W_BIT);
	tw_tx(0x40);                                 // prep for data stream: C0 = 0 D/C#=1, followed by 6 zeros (datasheet 8.1.5.2)
}




void d_init(void) {                               // initialize display
	d_start_cmd();
	for (uint8_t i = 0; i < sizeof (init_sequence); i++) { // read init sequence from progmem
		tw_tx(pgm_read_byte(&init_sequence[i]));
	}
	tw_tx(OLED_CMD_SET_COLUMN_RANGE);
	tw_tx(0x00);
	tw_tx(0x7F);
	tw_tx(OLED_CMD_SET_PAGE_RANGE);
	tw_tx(0);
	tw_tx(0x07);
	tw_stop();
}


void d_set_pos(uint8_t x, uint8_t row) {        // set cursor position
	d_start_cmd();
	tw_tx(0xB0 + row);
	tw_tx(((x & 0xF0) >> 4) | 0x10);
	tw_tx((x & 0x0f));
	tw_stop();
}

void d_clear(void) {                            // clear display
	d_set_pos(0, 0);
	d_start_dat();
	for (uint16_t i = 0; i < 128 * 8; i++) {
		tw_tx(0);
	}
	tw_stop();

}

void d_on(void) {                               // turn on display (wake up)
	d_start_cmd();
	tw_tx(0xAF);
	tw_stop();
}

void d_off(void) {                              // turn off display (sleep)
	d_start_cmd();
	tw_tx(0xAE);
	tw_stop();
}

void d_contrast (uint8_t contrast) {            // change contrast (brightness)
	d_start_cmd();
	tw_tx(0x81);                                // set contrast control register
	tw_tx(contrast);                            // contrast 0-255
	tw_stop();
}

void d_print_char(uint16_t i, char ch, const uint8_t bmp[]) {   // print 1 character
	uint16_t c = (ch - 32)*5;                            // character table index
	d_start_dat();

	if (!bmp) {                                          // if NULL bitmap pointer, overwrite background
		tw_tx(0x00);                                     // send leading 1 px space
		for (uint8_t j = 0; j < 5; j++) {
			tw_tx(pgm_read_byte(&D_FONT6x8[c + j]));     // send character bytes
		}
	}
	else {                                               // if a bitmap pointer is given, preserver background
		tw_tx(pgm_read_byte(&bmp[i]));                   // send background bitmap byte
		for (uint8_t j = 0; j < 5; j++) {                // send background bitmap + character bytes
			tw_tx(pgm_read_byte(&bmp[i + j + 1]) | pgm_read_byte(&D_FONT6x8[c + j]));
		}
	}
	tw_stop();
}

void d_print_str(uint8_t x, uint8_t row, char *s, const uint8_t bmp[]) { // print string (char array)
	d_set_pos(x,row);
	uint16_t i = row*128 + x;                     // background bitmap byte offset
	while (*s) {
		d_print_char(i, *s++, bmp);
		i +=6;                                    // increase bitmap byte offset by the width of one character
	}
}

void d_print_int(uint8_t x, uint8_t row, uint16_t num, const uint8_t bmp[]) {       // print integer variable
	ssd1306_numdec_buffer[USINT2DECASCII_MAX_DIGITS] = '\0';                        // Terminate the string
	uint8_t digits = usint2decascii(num, ssd1306_numdec_buffer);
	d_print_str(x, row, ssd1306_numdec_buffer + digits, bmp);
}

void d_draw_bmp(const uint8_t bmp[]) {
	d_set_pos(0,0);
	d_start_dat();

	for (uint16_t i = 0; i < 128*8; i++) {      // send background bitmap byte by byte
		tw_tx(pgm_read_byte(&bmp[i]));
	}
	tw_stop();
}