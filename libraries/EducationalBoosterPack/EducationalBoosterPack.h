///
/// @mainpage	Educational BoosterPack Library
///
/// @details	Library for the Educational BoosterPack
/// @n
/// @n
/// @n @a	Developed with [embedXcode](http://embedXcode.weebly.com)
///
/// @author	Rei VILO
/// @author	embedXcode.weebly.com
/// @date	Feb 11, 2013
/// @version	106
///
/// @copyright	© Rei VILO, 2013
/// @copyright	CC = BY NC SA
///
/// @see
/// * Educational BoosterPack wiki
/// @n	http://boosterpackdepot.com/wiki/index.php?title=Educational_BoosterPack
/// * Library for LCD
/// @n	based on Arduino library for Dog character LCD's
/// @n	http://code.google.com/p/doglcd/
/// @n	Copyright: 2010 Eberhard Fahle e.fahle@wayoda.org
/// @n	License: GNU Lesser GPL
// Core library - IDE-based
#if defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(ENERGIA) // LaunchPad, FraunchPad and StellarPad specific
#include "Energia.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(CORE_TEENSY) // Teensy specific
#include "WProgram.h"
#elif defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(ARDUINO) && (ARDUINO >= 100) // Arduino 1.0x and 1.5x specific
#include "Arduino.h"
#elif defined(ARDUINO) && (ARDUINO < 100)  // Arduino 23 specific
#include "WProgram.h"
#endif // end IDE
#ifndef EducationalBoosterPack_Library_h
#define EducationalBoosterPack_Library_h
#define EBP_WHITE_LED P2_5
#define EBP_RED_LED P2_1
#define EBP_GREEN_LED P2_2
#define EBP_BLUE_LED P2_4
#define EBP_ACC_X A0
#define EBP_ACC_Y A3
#define EBP_ACC_Z A4
#define EBP_LCD_SCK P1_5
#define EBP_LCD_MOSI P1_7
#define EBP_LCD_RS P2_3
#define EBP_LCD_command 0
#define EBP_LCD_data 1
#define EBP_POT A3
#define EBP_MIC A4
#define EBP_BUZZER P2_6
#define EBP_GATOR P2_7
class ebpPOT {
public:
    ebpPOT();
void begin();
    void get(uint32_t &value);
private:
};
class ebpMIC {
public:
    ebpMIC();
void begin();
    void get(uint32_t &value);
private:
};
class ebpRGB {
public:
    ebpRGB();
    void begin();
    void set(uint8_t red, uint8_t green, uint8_t blue);
};
class ebpACC {
public:
    ebpACC();
    void begin();
    void calibrate();
    void get();
    void gravityX100(int32_t &x, int32_t &y, int32_t &z);
    void degreeX100(int32_t &x, int32_t &y, int32_t &z);
private:
    int32_t _x, _y, _z;
    int32_t _x0, _y0, _z0;
    int32_t _vRef;
};
class ebpLCD {
public:
    ebpLCD();
void begin();
    void clear();
    void setRowLine(uint8_t row, uint8_t line);
    void setContrast(uint8_t contrast);
    void setFont(uint8_t font);
    void print(String text);
    void scrollLeft();
    void scrollRight();
private:
    void write(uint8_t mode, uint8_t data);
    uint8_t _rows, _lines;
};
#endif
