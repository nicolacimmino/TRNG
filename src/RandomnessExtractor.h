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

#ifndef __RANDOMNESS_EXTRACTOR_H__
#define __RANDOMNESS_EXTRACTOR_H__

#include <sha256.h> // https://github.com/daknuett/cryptosuite2

class RandomnessExtractor
{
public:
    void collectKeyEntropy(uint8_t randomNumber);
    void collectEntropy(uint8_t randomNumber);
    bool isKeyValid();
    bool isRandomDataReady();
    uint8_t *getRandomData();

private:
    // The 256-bit key currently used by the HMAC-256 to extract randomness.
    uint8_t secretKey[32];

    // The swap 256-bit where the next key is being collected.
    uint8_t secretKeySwap[32];

    // If false it signals secretKey is not yet valid.
    bool secretKeyValid = false;

    // If true random data that has not been fetched yet is available.
    bool randomDataReady = false;

    // Generated random data.
    uint8_t randomData[32];
};

#endif
