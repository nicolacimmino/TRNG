// Randomness extractor pulls 256-bits of random data from
// an input pool of 256-bits of entropy using HMAC-SHA256.
//  Copyright (C) 2018 Nicola Cimmino
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

// https://github.com/daknuett/cryptosuite2
#include <sha256.h>

// The 256-bit key currently used by the HMAC-256 to extract randoness.
static uint8_t randomnessExtractorSecretKey[32];

// The swap 256-bit where the next key is being collected..
static uint8_t randomnessExtractorSecretKeySwap[32];

// If false it signals randomnessExtractorSecretKey is not yet valid.
bool randomnessExtractorSecretKeyValid = false;

/**
 * Collect entropy to be used for the key.
 */
void randomnessExtractorCollectKeyEntropy(uint8_t randomNumber)
{
    static uint8_t keyIndex = 0;

    randomnessExtractorSecretKeySwap[keyIndex] = randomNumber;
    keyIndex++;

    if (keyIndex == 31)
    {
        memcpy(randomnessExtractorSecretKey, randomnessExtractorSecretKeySwap, 32);
        keyIndex = 0;
        randomnessExtractorSecretKeyValid = true;
    }
}

/**
 * Collect entropy to be used to geneare the random data.
 */
void randomnessExtractorCollectEntropy(uint8_t randomNumber)
{
    static uint8_t collectedBytes = 0;

    if (!randomnessExtractorSecretKeyValid)
    {
        return;
    }

    if (collectedBytes == 0)
    {
        Sha256.initHmac(randomnessExtractorSecretKey, 32);
    }

    Sha256.write(randomNumber);
    collectedBytes++;

    if (collectedBytes != 32)
    {
        return;
    }

    dispatchExtractedRandomness();

    collectedBytes = 0;
}

/**
 * Dispatches the extracted values byte by byte.
 */
void dispatchExtractedRandomness()
{
    uint8_t *hmac = Sha256.resultHmac();

    for (int ix = 0; ix < 32; ix++)
    {
        extractedRandomnessReady(hmac[ix]);
    }
}

/**
 * Callback invoked once 8 bits of extracted randomness are ready.
 */
extern void extractedRandomnessReady(uint8_t extractedRandomNumber);
