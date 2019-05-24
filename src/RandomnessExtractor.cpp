// Randomness extractor pulls 256-bits of random data from
// an input pool of 256-bits of entropy and a 32-bit key using HMAC-SHA256.
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

#include "RandomnessExtractor.h"

/**
 * Collect entropy to be used for the key.
 */
void RandomnessExtractor::collectKeyEntropy(uint8_t randomNumber)
{
    static uint8_t keyIndex = 0;

    this->secretKeySwap[keyIndex] = randomNumber;
    keyIndex++;

    if (keyIndex == 32)
    {
        memcpy(this->secretKey, this->secretKeySwap, 32);
        keyIndex = 0;
        this->secretKeyValid = true;
    }
}

/**
 * Returns true if enough entropy has been generated to generate a secret key.
 */
bool RandomnessExtractor::isKeyValid()
{
    return this->secretKeyValid;
}

/**
 * Collect entropy to be used to generate the random values.
 */
void RandomnessExtractor::collectEntropy(uint8_t randomNumber)
{
    static uint8_t collectedBytes = 0;

    if (!this->secretKeyValid)
    {
        return;
    }

    if (collectedBytes == 0)
    {
        Sha256.initHmac(this->secretKey, 32);
    }

    Sha256.write(randomNumber);
    collectedBytes++;

    if (collectedBytes != 32)
    {
        return;
    }

    memcpy(this->randomData, Sha256.resultHmac(), 32);

    this->randomDataReady = true;

    collectedBytes = 0;
}

bool RandomnessExtractor::isRandomDataReady()
{
    return this->randomDataReady;
}

uint8_t *RandomnessExtractor::getRandomData()
{
    this->randomDataReady = false;

    return this->randomData;
}