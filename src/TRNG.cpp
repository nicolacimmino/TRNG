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

#include "TRNG.h"

TRNG::TRNG()
{
    this->pPrimaryNoiseSource = new PrimaryNoiseSource();
    this->pSecondaryNoiseSource = SecondaryNoiseSource::instance();
    this->pRandomnessExtractor = new RandomnessExtractor();
}

void TRNG::begin(uint8_t chargePumpPin0, uint8_t chargePumpPin1, uint8_t chargePumpPin2, uint8_t chargepPumPin3, uint8_t chargepPumPinSense, uint8_t chargepPumPinNoise)
{
    this->pPrimaryNoiseSource->begin(chargePumpPin0, chargePumpPin1, chargePumpPin2, chargepPumPin3, chargepPumPinSense, chargepPumPinNoise);
}

void TRNG::loop()
{
    if (this->pSecondaryNoiseSource->isRandomDataReady())
    {        
        uint8_t *randomData = this->pSecondaryNoiseSource->getRandomData();
        for (int ix = 0; ix < 4; ix++)
        {
            this->pRandomnessExtractor->collectKeyEntropy(randomData[ix]);
        }
    }
    
    if (!this->pRandomnessExtractor->isKeyValid())
    {
        return;
    }

    uint8_t randomByte = this->pPrimaryNoiseSource->getRandomByte();

    if (!this->pPrimaryNoiseSource->sourceGood)
    {
        return;
    }

    this->pRandomnessExtractor->collectEntropy(randomByte);

    if (this->pRandomnessExtractor->isRandomDataReady())
    {
        memcpy(this->randomData, this->pRandomnessExtractor->getRandomData(), 32);
        this->randomDataReadIndex = 0;
        this->randomDataReady = true;
    }
}

bool TRNG::isRandomDataReady()
{
    return this->randomDataReady;
}

uint8_t TRNG::getRandomByte()
{
    uint8_t data = this->randomData[this->randomDataReadIndex];

    this->randomDataReadIndex++;

    if (this->randomDataReadIndex == sizeof(this->randomData) / sizeof(uint8_t))
    {
        this->randomDataReady = false;
    }

    return data;
}
