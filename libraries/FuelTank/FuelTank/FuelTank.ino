///
/// @file		FuelTank.ino
/// @brief		Main sketch
///
/// @details	Example for the Fuel Tank BoosterPack libray
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
///
/// @date		Dec 20, 2013
/// @version	101
///
/// @copyright	(c) Rei Vilo, 2013
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
/// @n
///


// Core library for code-sense
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#elif defined(CORE_TEENSY) // Teensy specific
#include "WProgram.h"
#elif defined(ARDUINO) && (ARDUINO >= 100) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#elif defined(ARDUINO) && (ARDUINO < 100) // Arduino 23 specific
#include "WProgram.h"
#else // error
#error Platform not defined
#endif

// Include application, user and local libraries
#include "Wire.h"
#include "FuelTankLibrary.h"


// Prototypes


///
/// @brief	Fuel tank instantiation
///
FuelTank myFuelTank;




///
/// @brief	Display routine
/// @details	Based on integers to save memory!
/// @param	message message, string
/// @param	value actually value x unit
/// @param	unit 1=default, otherwise 10, 100, ...
/// @note   value=12, unit=10 means 12/10 = 1.2
///
void display(String message, int32_t value, int16_t unit = 1)

{
    Serial.print(message);
    Serial.print("\t");
    Serial.print(value / unit, DEC);
    if (unit > 1) {
        Serial.print(".");
        Serial.print(value % unit, DEC);
    }
    Serial.println();
}


///
/// @brief	Setup code
///
void setup()

{
    Serial.begin(9600);
    Serial.println("---");

    Wire.begin();
    myFuelTank.begin();
    
    Serial.println(myFuelTank.WhoIAm());
    Serial.println("---");
}

///
/// @brief	Loop code
///
void loop()

{
    myFuelTank.get();
    Serial.println();
    
    display("Temperature                     oC ", myFuelTank.temperature_oCx10(), 10);
    display("Voltage                         mV ", myFuelTank.voltage_mV());
//    display("Flags                              ", myFuelTank.flags());
    display("Nominal Available Capacity      mAh", myFuelTank.nominalAvailableCapacity_mAh());
    display("Full Available Capacity         mAh", myFuelTank.fullAvailableCapacity_mAh());
    display("Remaining Capacity              mAh", myFuelTank.remainingCapacity_mAh());
    display("Full Charge Capacity            mAh", myFuelTank.fullChargeCapacity_mAh());
    display("Average Current                 mA ", myFuelTank.averageCurrent_mA());
    display("Time To Empty                   mn ", myFuelTank.timeToEmpty_mn());

#if (RELEASE == 3)

    display("Standby Current                 mA ", myFuelTank.standbyCurrent_mA());
    display("Standby Time To Empty           mn ", myFuelTank.standbyTimeToEmpty_mn());
    display("State Of Health                 %/n", myFuelTank.stateOfHealth_Index());
    display("Cycle Count                     n  ", myFuelTank.cycleCount());
    display("State Of Charge                 %  ", myFuelTank.stateOfCharge_Percent());
    display("Instantaneous Current           mA ", myFuelTank.instantaneousCurrent_mA());
    display("Internal Temperature            oC ", myFuelTank.internalTemperature_oCx10(), 10);
//    display("Resistance Scale                   ", myFuelTank.resistanceScale());
//    display("Operation Configuration            ", myFuelTank.operationConfiguration());
    display("Design Capacity                 mAh", myFuelTank.designCapacity_mAh());

    
#elif (RELEASE == 2)
    
    display("Time To Full                    mn ", myFuelTank.timeToFull_mn());
    display("Standby Current                 mA ", myFuelTank.standbyCurrent_mA());
    display("Standby Time To Empty           mn ", myFuelTank.standbyTimeToEmpty_mn());
    display("Max Load Current                mA ", myFuelTank.maxLoadCurrent_mA());
    display("Max Load Time To Empty          mn ", myFuelTank.maxLoadTimeToEmpty_mn());
    display("Available Energy                mWh", myFuelTank.availableEnergy_mWhx10(), 10);
    display("Average Power                   mW ", myFuelTank.averagePower_mW());
    display("Time To Empty At Constant Power mn ", myFuelTank.timeToEmptyAtConstantPower_mn());
    display("Cycle Count                        ", myFuelTank.cycleCount());
    display("State Of Charge                 %  ", myFuelTank.stateOfCharge_Percent());

#else

    Serial.println(myFuelTank.WhoIAm());

#endif
    
    delay(1000);
}
