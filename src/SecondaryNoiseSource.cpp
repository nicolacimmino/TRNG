// Secondary noise source pulls 32 bits of entropy from the internal time jitter.
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

#include "SecondaryNoiseSource.h"

SecondaryNoiseSource::SecondaryNoiseSource()
{
    // Setup a watchdog interrupt every 64mS.
    cli();
    _WD_CONTROL_REG = (1 << WDCE) | (1 << WDE);
    _WD_CONTROL_REG = (1 << WDIE) | (1 << WDP1);
    sei();
}

SecondaryNoiseSource *SecondaryNoiseSource::theInstance = NULL;

SecondaryNoiseSource *SecondaryNoiseSource::instance()
{
    if (!theInstance)
    {
        theInstance = new SecondaryNoiseSource();
    }

    return theInstance;
}

/**
 * This is the Arduino Interrupt Service Routine, which will be 
 * called by the WDT interrupt every 64ms.
 */
ISR(WDT_vect)
{
    SecondaryNoiseSource::instance()->collectSecondaryNoise();
}

/**
 * This is called by an ISR driven by the timer and collects at every round
 * one bit of entropy. We sample here the current value of the LSB of Timer1 
 * counter. The jitter of the interrupt process makes this random. 
 */
void SecondaryNoiseSource::collectSecondaryNoise()
{
    static uint32_t noiseBuffer = 0;
    static uint8_t collectedBits = 0;

    noiseBuffer = (noiseBuffer << 1) | (TCNT1L & 1);
    collectedBits++;

    if (collectedBits == 32)
    {
        this->createSecondaryRandomNumber(noiseBuffer);
        collectedBits = 0;
    }
}

/**
 * We pass here the collected 32 bits into a CRC-32, note that this
 * CRC-32 is forever running so it acts as randomness extrector and
 * de-bias of the input source.
 */
void SecondaryNoiseSource::createSecondaryRandomNumber(uint32_t noiseBuffer)
{
    this->crc.update(noiseBuffer);
    this->randomWord = this->crc.finalize();
    this->randomWordReady = true;
}

bool SecondaryNoiseSource::isRandomWordReady()
{
    return this->randomWordReady;
}

uint32_t SecondaryNoiseSource::getRandomWord()
{
    this->randomWordReady = false;

    return this->randomWord;
}