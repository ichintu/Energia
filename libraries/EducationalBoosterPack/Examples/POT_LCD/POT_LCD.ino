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

ebpPOT myPOT;
ebpLCD myLCD;

///
/// @brief	Setup
/// @details	Setup code
///
void setup() {
    
    myPOT.begin();
    myLCD.begin();
    myLCD.print("Contrast ");

    
    myLCD.setRowLine(17, 0);
    myLCD.print(":)");
    delay(500);

    for (i=0; i<8; i++) {
          myLCD.scrollLeft();
        delay(100);
       }
    delay(500);
    for (i=0; i<8; i++) {
        myLCD.scrollRight();
        delay(100);
    }
    delay(500);

    // Beeper
    //    pinMode(P2_6, OUTPUT);
    //    analogWrite(P2_6, 55);
}



///
/// @brief	Loop
/// @details Loop code
///
void loop() {
    uint32_t w;

    myPOT.get(w);
    w = map(w, 0, 1023, 0x20, 0x40);
    myLCD.setContrast(w);
    
    myLCD.setRowLine(9, 0);
    myLCD.print(String(w) + "   ");
    delay(100);
    
    if (w>54) myLCD.setFont(1);
    if (w<48) myLCD.setFont(0);
    
    delay(10);
}



