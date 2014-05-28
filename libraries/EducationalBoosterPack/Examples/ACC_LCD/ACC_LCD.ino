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

ebpACC myACC;
int32_t x, y, z;
ebpLCD myLCD;

///
/// @brief	Setup
/// @details	Setup code
///
void setup() {
    
    myLCD.begin();
    myLCD.print(" ACC xyz");
    
    myACC.begin();
    myACC.calibrate();

    // Beeper
    //    pinMode(P2_6, OUTPUT);
    //    analogWrite(P2_6, 55);
}



///
/// @brief	Loop
/// @details Loop code
///
void loop() {
    myACC.get();
    myACC.degreeX100(x, y, z);
    
    myLCD.setRowLine(0, 1);
    sprintf(buffer, "%+4d x", x/100);
    myLCD.print(buffer);
    
    myLCD.setRowLine(9, 1);
    sprintf(buffer, "%+4d y", y/100);
    myLCD.print(buffer);
    
    myLCD.setRowLine(9, 0);
    sprintf(buffer, "%+4d z", z/100);
    myLCD.print(buffer);
    
    delay(10);
}



