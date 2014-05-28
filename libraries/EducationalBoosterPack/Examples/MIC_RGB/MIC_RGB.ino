///
/// @file	EducationalBoosterPack_main.ino
/// @brief	Main sketch
///
/// @details	Examples 
/// @n @a	Developed with [embedXcode](http://embedXcode.weebly.com)
///
/// @author	Rei VILO
/// @author	embedXcode.weebly.com
/// @date	Feb 11, 2013 20:22
/// @version	<#version#>
///
/// @copyright	© Rei VILO, 2013
/// @copyright	CC = BY NC SA
///
/// @see	EBP_RGB.h for references
///


// Core library for code-sense
#include "Energia.h"

#if defined(__MSP430G2553__) || defined(__MSP430G2452__) // LaunchPad specific
#else // error
#error Platform not defined
#endif

// Include application, user and local libraries
#include "EducationalBoosterPack.h"

// Define variables and constants
uint8_t i;
char buffer[32];

ebpMIC myMIC;
ebpPOT myPOT;
ebpRGB myRGB;
ebpLCD myLCD;
uint32_t wmin = 1023;
uint32_t wmax = 0;

///
/// @brief	Setup
/// @details	Setup code
///
void setup() {
    
    myLCD.begin();
    myLCD.print(" MIC");
    
    myMIC.begin();
    myRGB.begin();
    myPOT.begin();

    myRGB.set(0, 0, 0);

    // Beeper
    //    pinMode(P2_6, OUTPUT);
    //    analogWrite(P2_6, 55);
}



///
/// @brief	Loop
/// @details Loop code
///
void loop() {
    uint32_t v, w;
    uint8_t r, g, b;
    
    myPOT.get(v);
    myMIC.get(w);
    if (w > wmax) wmax = w;
    if (w < wmin) wmin = w;
    
    myLCD.setRowLine(8, 0);
    sprintf(buffer, "%7d", w);
    myLCD.print(buffer);
    
    myLCD.setRowLine(0, 1);
    sprintf(buffer, "min%4d", wmin);
    myLCD.print(buffer);
    
    myLCD.setRowLine(8, 1);
    sprintf(buffer, "max%4d", wmax);
    myLCD.print(buffer);
    
    w = map(w, wmin, wmax, 0, 1023);

    if (w>v) { // red zone
        r = map(w, v, 1023, 0xff, 0xff);
        g = map(w, v, 1023, 0x00, 0xff);
        b = map(w, v, 1023, 0x00, 0xff);
    } else if (w>v*60/100) { // yellow zone
        r = map(w, v*60/100, v, 0xff, 0xff);
        g = map(w, v*60/100, v, 0xff, 0x00);
        b = map(w, v*60/100, v, 0x00, 0x00);
    } else { // green zone
        r = map(w, 0, v*60/100, 0x00, 0xff);
        g = map(w, 0, v*60/100, 0xff, 0xff);
        b = map(w, 0, v*60/100, 0x00, 0x00);
    }
    myRGB.set(r, g, b);
    
    delay(10);
}



