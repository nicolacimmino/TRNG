// TRNG wires together the primary and secondary noise sources into the randomness extractor
// and generates random data.
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

#ifndef __TRNG_H__
#define __TRNG_H__

#include <Arduino.h>
#include "PrimaryNoiseSource.h"
#include "SecondaryNoiseSource.h"
#include "RandomnessExtractor.h"

class TRNG
{
public:
    TRNG();
    void begin(uint8_t chargePumpPin0, uint8_t chargePumpPin1, uint8_t chargePumpPin2, uint8_t chargepPumPin3, uint8_t chargepPumPinSense, uint8_t chargepPumPinNoise);
    void loop();
    bool isRandomDataReady();
    uint8_t getRandomByte();

private:
    PrimaryNoiseSource *pPrimaryNoiseSource;
    SecondaryNoiseSource *pSecondaryNoiseSource;
    RandomnessExtractor *pRandomnessExtractor;    
    uint8_t randomData[32];
    bool randomDataReady = false;
    uint8_t randomDataReadIndex = 0;
};

#endif