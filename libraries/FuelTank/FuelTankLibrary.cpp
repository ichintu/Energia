//
// FuelTankLibrary.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode+
// http://embedXcode.weebly.com
//
// Project   FuelTankLibrary
//
// Created by  Rei Vilo, 20/12/2013 16:49
//     http://embeddedcomputing.weebly.com
//
// Copyright  © Rei Vilo, 2013
// License  CC = BY SA NC
//
// See    FuelTankLibrary.h and ReadMe.txt for references
//
#include "FuelTankLibrary.h"
#include "Wire.h"
#define BQ27510_I2C_Address                 0x55
#define BQ27510_Control                     0x00
#define BQ27510_Temperature                 0x06
#define BQ27510_Voltage                     0x08
#define BQ27510_Flags                       0x0a
#define BQ27510_NominalAvailableCapacity 0x0c
#define BQ27510_FullAvailableCapacity       0x0e
#define BQ27510_RemainingCapacity           0x10
#define BQ27510_FullChargeCapacity          0x12
#define BQ27510_AverageCurrent              0x14
#define BQ27510_TimeToEmpty                 0x16
#if (BQ27510_RELEASE == 3)
#define BQ27510_G3_StandbyCurrent              0x18
#define BQ27510_G3_StandbyTimeToEmpty          0x1a
#define BQ27510_G3_StateOfHealth               0x1c
#define BQ27510_G3_CycleCount                  0x1e
#define BQ27510_G3_StateOfCharge               0x20
#define BQ27510_G3_InstantaneousCurrent        0x22
#define BQ27510_G3_InternalTemperature         0x28
#define BQ27510_G3_ResistanceScale             0x2a
#define BQ27510_G3_OperationConfiguration      0x2c
#define BQ27510_G3_DesignCapacity              0x2e
#elif (BQ27510_RELEASE == 2)
#define BQ27510_G2_TimeToFull                  0x18
#define BQ27510_G2_StandbyCurrent              0x1a
#define BQ27510_G2_StandbyTimeToEmpty          0x1c
#define BQ27510_G2_MaxLoadCurrent              0x1e
#define BQ27510_G2_MaxLoadTimeToEmpty          0x20
#define BQ27510_G2_AvailableEnergy             0x22
#define BQ27510_G2_AveragePower                0x24
#define BQ27510_G2_TTEatConstantPower          0x26
#define BQ27510_G2_Reserved                    0x28
#define BQ27510_G2_CycleCount                  0x2a
#define BQ27510_G2_StateOfCharge               0x2c
#endif
FuelTank::FuelTank()
{
    ;
}
void FuelTank::begin()
{
    ;
}
String FuelTank::WhoIAm()
{
    return "Fuel Tank BoosterPack";
}
uint16_t FuelTank::_read16(uint8_t reg)
{
    Wire.beginTransmission(BQ27510_I2C_Address);
    Wire.write(reg);
    Wire.endTransmission();
    delay(5);
    Wire.requestFrom(BQ27510_I2C_Address, 2);
    return (uint16_t)(Wire.read() + ((Wire.read() << 8) & 0xff00));
}
int16_t FuelTank::ui2i(uint16_t ui16)
{
    if (ui16 > (uint16_t)0x7fff) {
        ui16 = 0xffff - ui16;
        return -ui16;
    } else {
        return ui16;
    }
}
void FuelTank::get()
{
    _temperature_oCx10              = _read16(BQ27510_Temperature) -2730;
    _voltage_mV                     = _read16(BQ27510_Voltage);
    _flags                          = _read16(BQ27510_Flags);
    _nominalAvailableCapacity_mAh   = _read16(BQ27510_NominalAvailableCapacity);
    _fullAvailableCapacity_mAh      = _read16(BQ27510_FullAvailableCapacity);
    _remainingCapacity_mAh          = _read16(BQ27510_RemainingCapacity);
    _fullChargeCapacity_mAh         = _read16(BQ27510_FullChargeCapacity);
    _averageCurrent_mA              = ui2i(_read16(BQ27510_AverageCurrent));
    _timeToEmpty_mn                 = _read16(BQ27510_TimeToEmpty);
#if (BQ27510_RELEASE == 3)
    _standbyCurrent_mA              = ui2i(_read16(BQ27510_G3_StandbyCurrent));
    _standbyTimeToEmpty_mn          = _read16(BQ27510_G3_StandbyTimeToEmpty);
    _stateOfHealth_Index            = lowByte(_read16(BQ27510_G3_StateOfHealth));
    _cycleCount                     = _read16(BQ27510_G3_CycleCount);
    _stateOfCharge_Percent          = _read16(BQ27510_G3_StateOfCharge);
    _instantaneousCurrent_mA        = ui2i(_read16(BQ27510_G3_InstantaneousCurrent));
    _internalTemperature_oCx10      = _read16(BQ27510_G3_InternalTemperature) -2730;
    _resistanceScale                = _read16(BQ27510_G3_ResistanceScale);
    _operationConfiguration         = _read16(BQ27510_G3_OperationConfiguration);
    _designCapacity_mAh             = _read16(BQ27510_G3_DesignCapacity);
#elif (BQ27510_RELEASE == 2)
    _timeToFull_mn                  = _read16(BQ27510_TimeToFull);
    _standbyCurrent_mA              = ui2i(_read16(BQ27510_StandbyCurrent));
    _standbyTimeToEmpty_mn          = _read16(BQ27510_StandbyTimeToEmpty);
    _maxLoadCurrent_mA              = _read16(BQ27510_MaxLoadCurrent);
    _maxLoadTimeToEmpty_mn          = _read16(BQ27510_MaxLoadTimeToEmpty);
    _availableEnergy_mWhx10         = _read16(BQ27510_AvailableEnergy);
    _averagePower_mW                = _read16(BQ27510_AveragePower);
    _timeToEmptyAtConstantPower_mn  = _read16(BQ27510_TTEatConstantPower);
    _cycleCount                     = _read16(BQ27510_CycleCount);
    _stateOfCharge_Percent          = _read16(BQ27510_StateOfCharge);
#endif
}
uint16_t FuelTank::temperature_oCx10()
{
    return _temperature_oCx10;
}
uint16_t FuelTank::voltage_mV()
{
    return _voltage_mV;
}
uint16_t FuelTank::flags()
{
    return _flags;
}
uint16_t FuelTank::nominalAvailableCapacity_mAh()
{
    return _nominalAvailableCapacity_mAh;
}
uint16_t FuelTank::fullAvailableCapacity_mAh()
{
    return _fullAvailableCapacity_mAh;
}
uint16_t FuelTank::remainingCapacity_mAh()
{
    return _remainingCapacity_mAh;
}
uint16_t FuelTank::fullChargeCapacity_mAh()
{
    return _fullChargeCapacity_mAh;
}
int16_t FuelTank::averageCurrent_mA()
{
    return _averageCurrent_mA;
}
uint16_t FuelTank::timeToEmpty_mn()
{
    return _timeToEmpty_mn;
}
#if (BQ27510_RELEASE == 3)
int16_t FuelTank::standbyCurrent_mA()
{
    return _standbyCurrent_mA;
}
uint16_t FuelTank::standbyTimeToEmpty_mn()
{
    return _standbyTimeToEmpty_mn;
}
uint16_t FuelTank::stateOfHealth_Index()
{
    return _stateOfHealth_Index;
}
uint16_t FuelTank::cycleCount()
{
    return _cycleCount;
}
uint16_t FuelTank::stateOfCharge_Percent()
{
    return _stateOfCharge_Percent;
}
int16_t FuelTank::instantaneousCurrent_mA()
{
    return _instantaneousCurrent_mA;
}
uint16_t FuelTank::internalTemperature_oCx10()
{
    return _internalTemperature_oCx10;
}
uint16_t FuelTank::resistanceScale()
{
    return _resistanceScale;
}
uint16_t FuelTank::operationConfiguration()
{
    return _operationConfiguration;
}
uint16_t FuelTank::designCapacity_mAh()
{
    return _designCapacity_mAh;
}
#elif (BQ27510_RELEASE == 2)
uint16_t FuelTank::timeToFull_mn()
{
    return _timeToFull_mn;
}
uint16_t FuelTank::standbyCurrent_mA()
{
    return _standbyCurrent_mA;
}
uint16_t FuelTank::standbyTimeToEmpty_mn()
{
    return _standbyTimeToEmpty_mn;
}
uint16_t FuelTank::maxLoadCurrent_mA()
{
    return _maxLoadCurrent_mA;
}
uint16_t FuelTank::maxLoadTimeToEmpty_mn()
{
    return _maxLoadTimeToEmpty_mn;
}
uint16_t FuelTank::availableEnergy_mWhx10()
{
    return _availableEnergy_mWhx10;
}
uint16_t FuelTank::averagePower_mW()
{
    return _averagePower_mW;
}
uint16_t FuelTank::timeToEmptyAtConstantPower_mn()
{
    return _timeToEmptyAtConstantPower_mn;
}
uint16_t FuelTank::cycleCount()
{
    return _cycleCount;
}
uint16_t FuelTank::stateOfCharge_Percent()
{
    return _stateOfCharge_Percent;
}
#endif
