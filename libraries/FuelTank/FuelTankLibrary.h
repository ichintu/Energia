///
/// @mainpage FuelTankLibrary
///
/// @details Libray for the Fuel Tank BoosterPack
/// @n   Library
/// @n
/// @n @a  Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author  Rei Vilo
/// @author  http://embeddedcomputing.weebly.com
///
/// @date  Dec 20, 2013
/// @version 101
///
/// @copyright (c) Rei Vilo, 2013
/// @copyright CC = BY SA NC
///
/// @see  ReadMe.txt for references
/// * Fuel Tank BoosterPack
/// * Datasheet http://www.ti.com/lit/gpn/bq27520-g3
/// * White paper http://www.ti.com/lit/wp/slpy002/slpy002.pdf
/// * Reference http://www.ti.com/lit/pdf/sluua35
/// * Comparison BQ27520-G3 to -G4 http://www.ti.com/lit/pdf/slua658
///
#if defined(MPIDE)
#include "WProgram.h"
#elif defined(DIGISPARK)
#include "Arduino.h"
#elif defined(ENERGIA)
#include "Energia.h"
#elif defined(MAPLE_IDE)
#include "WProgram.h"
#elif defined(CORE_TEENSY)
#include "WProgram.h"
#elif defined(WIRING)
#include "Wiring.h"
#elif defined(ARDUINO) && (ARDUINO >= 100)
#include "Arduino.h"
#elif defined(ARDUINO) && (ARDUINO < 100)
#include "WProgram.h"
#endif
#ifndef FuelTankLibrary_RELEASE
#define FuelTankLibrary_RELEASE 101
#define BQ27510_RELEASE 3
class FuelTank
{
public:
    FuelTank();
    void        begin();
    String      WhoIAm();
    void        get();
    uint16_t temperature_oCx10();
    uint16_t voltage_mV();
    uint16_t flags();
    uint16_t nominalAvailableCapacity_mAh();
    uint16_t fullAvailableCapacity_mAh();
    uint16_t remainingCapacity_mAh();
    uint16_t fullChargeCapacity_mAh();
    int16_t     averageCurrent_mA();
    uint16_t timeToEmpty_mn();
#if (BQ27510_RELEASE == 3)
    int16_t     standbyCurrent_mA();
    uint16_t standbyTimeToEmpty_mn();
    uint16_t stateOfHealth_Index();
    uint16_t cycleCount();
    uint16_t stateOfCharge_Percent();
    int16_t     instantaneousCurrent_mA();
    uint16_t internalTemperature_oCx10();
    uint16_t resistanceScale();
    uint16_t operationConfiguration();
    uint16_t designCapacity_mAh();
#elif (BQ27510_RELEASE == 2)
    uint16_t timeToFull_mn();
    int16_t     standbyCurrent_mA();
    uint16_t standbyTimeToEmpty_mn();
    uint16_t maxLoadCurrent_mA();
    uint16_t maxLoadTimeToEmpty_mn();
    uint16_t availableEnergy_mWhx10();
    uint16_t averagePower_mW();
    uint16_t timeToEmptyAtConstantPower_mn();
    uint16_t cycleCount();
    uint16_t stateOfCharge_Percent();
#endif
private:
    uint16_t    _read16(uint8_t reg);
    int16_t     ui2i(uint16_t ui16);
    uint16_t _temperature_oCx10;
    uint16_t _voltage_mV;
    uint16_t _flags;
    uint16_t _nominalAvailableCapacity_mAh;
    uint16_t _fullAvailableCapacity_mAh;
    uint16_t _remainingCapacity_mAh;
    uint16_t _fullChargeCapacity_mAh;
    int16_t     _averageCurrent_mA;
    uint16_t _timeToEmpty_mn;
#if (BQ27510_RELEASE == 3)
    int16_t     _standbyCurrent_mA;
    uint16_t _standbyTimeToEmpty_mn;
    uint16_t _stateOfHealth_Index;
    uint16_t _cycleCount;
    uint16_t _stateOfCharge_Percent;
    int16_t     _instantaneousCurrent_mA;
    uint16_t _internalTemperature_oCx10;
    uint16_t _resistanceScale;
    uint16_t _operationConfiguration;
    uint16_t _designCapacity_mAh;
#elif (BQ27510_RELEASE == 2)
    uint16_t _timeToFull_mn;
    int16_t     _standbyCurrent_mA;
    uint16_t _standbyTimeToEmpty_mn;
    uint16_t _maxLoadCurrent_mA;
    uint16_t _maxLoadTimeToEmpty_mn;
    uint16_t _availableEnergy_mWhx10;
    uint16_t _averagePower_mW;
    uint16_t _timeToEmptyAtConstantPower_mn;
    uint16_t _cycleCount;
    uint16_t _stateOfCharge_Percent;
#endif
};
#endif
