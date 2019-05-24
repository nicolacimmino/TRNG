// Primary noise source.
// Here we drive the external charge pump and the zener noise source to get random data.
//
//  Copyright (C) 2019 Nicola Cimmino
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef _TRNG_PRIMARY_NOISE_SOURCE_H_
#define _TRNG_PRIMARY_NOISE_SOURCE_H_

#define CHG_PUMP_LIMIT_HI 300
#define CHG_PUMP_LIMIT_LO 280
#define CHG_PUMP_ALARM_DELAY_MS 10000

#include <Arduino.h>

class PrimaryNoiseSource
{
public:
    void begin(uint8_t chargePumpPin0, uint8_t chargePumpPin1, uint8_t chargePumpPin2, uint8_t chargepPumPin3, uint8_t chargepPumpPinSense, uint8_t noiseInPin);    
    uint8_t getRandomByte();
    bool isHighVoltageReseviourAboveMin();
    bool sourceGood = false;        

private:
    uint8_t chargePumpPin0;
    uint8_t chargePumpPin1;
    uint8_t chargePumpPin2;
    uint8_t chargePumpPin3;
    uint8_t chargepPumpPinSense;
    uint8_t noiseInPin;
    void chargeHighVoltageReserviour();
    void setChargePumpOutputsHiZ(bool on);
    uint8_t sample8BitsWhitenedNoise();
    uint8_t sampleNBitsOfNoise(uint8_t bits);    
};

#endif