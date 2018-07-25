#include "SSD1306_OLED_HW_I2C.h"

const uint8_t background [] PROGMEM = {    // 128x64 bitmap
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xE0,
0xE0, 0xF0, 0xF0, 0xF8, 0xF0, 0xF4, 0xF0, 0xF2, 0xF2, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF8,
0xF8, 0xF8, 0xFC, 0x64, 0x70, 0x78, 0x6C, 0xBC, 0x9C, 0x7E, 0xFE, 0x72, 0x22, 0x02, 0x06, 0xF6,
0xFE, 0xFE, 0x7E, 0x3E, 0x3E, 0x1E, 0x1E, 0x5E, 0x6E, 0x42, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
0xC2, 0xE6, 0x72, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE8, 0xEC, 0xE0, 0xE0, 0xF0, 0xF0,
0xF0, 0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0xF0, 0xF0,
0xF8, 0xF0, 0xF0, 0xF0, 0xF0, 0xF1, 0xF0, 0xE2, 0xF2, 0xF4, 0xF4, 0xE8, 0xE8, 0xF0, 0xF0, 0x60,
0x60, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x05, 0x02, 0x03, 0x03,
0x01, 0x01, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xFC, 0x7E, 0x3F, 0x7F, 0x2F, 0x1F, 0x3E, 0x10, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0xCE, 0xCF, 0xFF, 0x78, 0x79, 0x7F,
0x7F, 0xFF, 0xFC, 0xFE, 0xFF, 0xFF, 0xBF, 0xBF, 0xBF, 0xBF, 0xFF, 0xFF, 0x9F, 0x7F, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x7C, 0x39, 0x18, 0xE0, 0xC7, 0x0F, 0x0C, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0xE0, 0x18, 0x06, 0x03, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x07, 0x3F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x8F, 0x8F, 0x0F, 0x4F,
0xFF, 0xC7, 0x83, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xFD, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE,
0xFC, 0xF9, 0xF8, 0xF9, 0xF9, 0xF9, 0xF9, 0xF9, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF, 0xEE, 0xDF, 0xFF,
0xFF, 0x3F, 0x3F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x7C, 0x71, 0x03, 0x04, 0x0E, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x18, 0xE0, 0x00,
0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x07, 0x0F, 0x1E, 0x10,
0xF0, 0xF9, 0xF9, 0xF9, 0xF9, 0xF8, 0xF8, 0xF0, 0xE0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0x7B, 0x1B, 0x01,
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x1F, 0x3F, 0x31, 0x00, 0x00, 0x00, 0x01, 0x63, 0xFF,
0xE7, 0xCF, 0x0E, 0x84, 0xC0, 0xE0, 0xE3, 0x8F, 0xBC, 0xB0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06,
0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07,
0x0F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0x1C,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x01, 0xC0, 0xE0, 0x60, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x03, 0x07, 0x06, 0x0D, 0x0F, 0x0B, 0x09, 0x8B, 0xCB, 0xE9, 0xE3, 0xF3, 0xF3, 0x87, 0xEF, 0xEE,
0x0E, 0x1C, 0x16, 0x04, 0x0C, 0x98, 0x80, 0x60, 0x00, 0x00, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x70,
0x00, 0x07, 0x18, 0x70, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x03, 0x01, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x07, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x03, 0x07, 0x01, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x34, 0x3F, 0x3F, 0x3F, 0x1F, 0x1F, 0x1F, 0x3F, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F,
0x1F, 0x0E, 0x00, 0x00, 0x00, 0x01, 0xC1, 0xC0, 0x00, 0x00, 0x80, 0xC0, 0x70, 0x1C, 0x07, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x1F, 0x3F, 0x3F, 0x60, 0x20, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00,
0x00, 0x04, 0x86, 0x86, 0xC3, 0x61, 0x31, 0x18, 0x0C, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x06,
0x04, 0x0C, 0x08, 0x18, 0x10, 0x30, 0x20, 0x00, 0x40, 0x40, 0x60, 0x20, 0x20, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF8, 0xFE, 0xFF, 0x9B, 0x90, 0x80,
0x80, 0x80, 0xC0, 0xC0, 0x80, 0x80, 0xE0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8,
0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFE, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
0xFC, 0xBE, 0x3C, 0xBC, 0x9C, 0x18, 0x18, 0x58, 0x60, 0x20, 0x20, 0x10, 0x18, 0x08, 0x0C, 0x04,
0x06, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void setup(void) {
    // SCL bit rate = CLK / (16 + 2*TWBR*[TWSR prescaler])
    TWSR = 0x00;    // I2C prescaler 1
    TWBR = 2;       // I2C divider 2
    d_init();       // Initialize OLED
}


void loop() {
  d_clear();
  d_draw_bmp(background);                                   // display bitmap
  _delay_ms(500*3);
  d_print_str(10, 2, "Background hidden", NO_BACKGROUND);  // print text and overwrite background
  d_print_str(7, 4, "Background visible", background);     // print text with background visible
  _delay_ms(1000*3);
}

