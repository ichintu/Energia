//
// EBP_RGB.cpp
// Class library C++ code
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project EducationalBoosterPack_main
//
// Created by Rei VILO, Feb 11, 2013
// embedXcode.weebly.com
//
//
// Copyright © Rei VILO, 2013
// Licence CC = BY NC SA
//
// See EBP_RGB.h for references
//


// Library header
#include "EducationalBoosterPack.h"


ebpPOT::ebpPOT() {
    pinMode(EBP_POT, INPUT);
}

void ebpPOT::begin() {
}

void ebpPOT::get(uint32_t &value) {
    value = analogRead(EBP_POT);
}

ebpMIC::ebpMIC() {
    pinMode(EBP_MIC, INPUT);
}

void ebpMIC::begin() {
}

void ebpMIC::get(uint32_t &value) {
    value = analogRead(EBP_MIC);
}

// Code
ebpRGB::ebpRGB() {
    pinMode(EBP_RED_LED, OUTPUT);
    pinMode(EBP_GREEN_LED, OUTPUT);
    pinMode(EBP_BLUE_LED, OUTPUT);
}

void ebpRGB::begin() {
    analogWrite(EBP_RED_LED, 0);
    analogWrite(EBP_GREEN_LED, 0);
    analogWrite(EBP_BLUE_LED, 0);
}

void ebpRGB::set(uint8_t red, uint8_t green, uint8_t blue) {
    analogWrite(EBP_RED_LED, red);
    analogWrite(EBP_GREEN_LED, green);
    analogWrite(EBP_BLUE_LED, blue);
    
}

// Utilities
int32_t asin_degX100(int32_t x) {
    int32_t sign = 1;
    int32_t angle;
    
    if (x<0) sign = -1;
    
    // input 1 g = 100
    x *= sign * 10; // base 1 g = 1000
    // output 1 degree = 100
    
    if      (x<259) angle = map(x,   0,  259,    0, 1500);
    else if (x<500) angle = map(x, 259,  500, 1500, 3000);
    else if (x<707) angle = map(x, 500,  707, 3000, 4500);
    else if (x<866) angle = map(x, 707,  866, 4500, 6000);
    else if (x<966) angle = map(x, 866,  966, 6000, 7500);
    else            angle = map(x, 966, 1000, 7500, 9000);
    
    return sign * angle;
}

///
/// @brief	Square root with integers only
/// @param	x number, unsigned 32-bit integer
/// @return	square root, unsigned 16-bit integer
/// @see	nightcracker answered Mar 14 '11 at 9:17
/// 	 	http://stackoverflow.com/a/5296669/1190049
///
uint32_t int_sqrt64(uint64_t x) {
    uint64_t hi = x;
    uint64_t lo = 0;
    uint64_t mid = ( hi + lo ) / 2;
    uint64_t mid2 = mid * mid;
    
    while ( (lo < hi-1) && (mid2 != x) ) {
        if ( mid2 < x )  lo = mid;
        else             hi = mid;
        
        mid = ( hi + lo ) / 2;
        mid2 = mid * mid;
    }
    
    return (uint16_t)mid;
}


// Code
ebpACC::ebpACC() {
    pinMode(EBP_ACC_X, INPUT);
    pinMode(EBP_ACC_Y, INPUT);
    pinMode(EBP_ACC_Z, INPUT);
}

void ebpACC::begin() {
    _x = 0;
    _y = 0;
    _z = 0;
    
    _vRef = 3000;
    
    _x0 = _vRef / 2;
    _y0 = _vRef / 2;
    _z0 = _vRef / 2;
}

void ebpACC::get() {
    _x = analogRead(EBP_ACC_X);
    _y = analogRead(EBP_ACC_Y);
    _z = analogRead(EBP_ACC_Z);
    
    _x = (_x * _vRef) / 1024;
    _y = (_y * _vRef) / 1024;
    _z = (_z * _vRef) / 1024;
}

void ebpACC::calibrate() {
    _x0 = 0;
    _y0 = 0;
    _z0 = 0;
    
    for (uint8_t i=0; i<8; i++) {
        get();
        _x0 += _x;
        _y0 += _y;
        _z0 += _z;
        delay(250);
    }
    _x0 /= 8;
    _y0 /= 8;
    _z0 /= 8;
    _z0 -= _vRef / 10; // z0 = +1 g
}

void ebpACC::gravityX100(int32_t &x, int32_t &y, int32_t &z) {
    x = _x - _x0;
    y = _y - _y0;
    z = _z - _z0;
    
    x = (x * 1000) / _vRef; // 1 g = 100
    y = (y * 1000) / _vRef;
    z = (z * 1000) / _vRef;
}

void ebpACC::degreeX100(int32_t &x, int32_t &y, int32_t &z) {
    x = _x - _x0;
    y = _y - _y0;
    z = _z - _z0;
    
    x = (x * 1000) / _vRef; // 1 g = 100
    y = (y * 1000) / _vRef;
    z = (z * 1000) / _vRef;
    
    int64_t k = (int64_t)(x*x + y*y + z*z);
    k = int_sqrt64(k);
    
    x = (x * 100) / k; // normalisation
    y = (y * 100) / k;
    z = (z * 100) / k;
    
    x = asin_degX100(x); // 90 degrees = 9000
    y = asin_degX100(y);
    z = asin_degX100(z);
}


ebpLCD::ebpLCD() {
    pinMode(EBP_LCD_SCK, OUTPUT);
    pinMode(EBP_LCD_MOSI, OUTPUT);
    pinMode(EBP_LCD_RS, OUTPUT);
}

void ebpLCD::begin() {
    write(EBP_LCD_command, 0x30); // wake-up
    delay(2);
    write(EBP_LCD_command, 0x30); // wake-up
    write(EBP_LCD_command, 0x30); // wake-up
    
    write(EBP_LCD_command, 0x14); // internal oscillator frequency
    
    write(EBP_LCD_command, 0x0c); // auto-indent
    write(EBP_LCD_command, 0x06); // left to right
    
    setFont(0);
    clear();
    setContrast(0x32);
}

void ebpLCD::setFont(uint8_t font) {
    if (font==1) {
        write(EBP_LCD_command, 0x35);
        _lines = 1;
    } else {
        write(EBP_LCD_command, 0x39);
        _lines = 2;
    }
    _rows = 40;
}

void ebpLCD::clear() {
    write(EBP_LCD_command, 0x01);
    delay(10);
    write(EBP_LCD_command, 0x02);
    delay(10);
}

void ebpLCD::setContrast(uint8_t contrast) {
    if (contrast < 0x40) {
        write(EBP_LCD_command, 0x54 | (contrast >>4 & 0x03));
        write(EBP_LCD_command, 0x6b);
        write(EBP_LCD_command, 0x70 | (contrast & 0x0f));
    }
    
}

void ebpLCD::setRowLine(uint8_t row, uint8_t line) {
    if ( (row<_rows) && (line<_lines) )
        write(EBP_LCD_command, 0x80 | (line*0x40) | row);
    delay(1);
}

void ebpLCD::scrollLeft() {
    write(EBP_LCD_command, 0x38);
    write(EBP_LCD_command, 0x18);
}

void ebpLCD::scrollRight() {
    write(EBP_LCD_command, 0x38);
    write(EBP_LCD_command, 0x1c);
}

void ebpLCD::print(String text) {
    for (uint8_t i=0; i<text.length(); i++) {
        write(EBP_LCD_data, text[i]);
        delay(1);
    }
}

void ebpLCD::write(uint8_t mode, uint8_t data) {
    digitalWrite(EBP_LCD_RS, mode);
    shiftOut(EBP_LCD_MOSI, EBP_LCD_SCK, MSBFIRST, data);
    delay(1);
}




