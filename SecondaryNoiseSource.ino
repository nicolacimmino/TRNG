// Secondary noise source pulls 32 bits of entropy from the internal time jitter.
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
#include <Arduino.h>
#include <avr/wdt.h>
#include <CRC32.h>

#define PIN_YELLOW_LED_SECONDARY 6

CRC32 crc;

/**
 * Initialise the noise source.
 * This starts the WDT interrupts.
 */
void initSecondaryNoiseSource()
{
    pinMode(PIN_YELLOW_LED_SECONDARY, OUTPUT);
    
    // Setup a watchdog interrupt every 64mS.
    cli();
    _WD_CONTROL_REG = (1 << WDCE) | (1 << WDE);
    _WD_CONTROL_REG = (1 << WDIE) | (1 << WDP1);
    sei();
}

/**
 * This is the Arduino Interrup Service Routine, which will be 
 * called by the WDT interrupt every 64ms.
 */
ISR(WDT_vect)
{
    collectSecondaryNoise();
}

/**
 * This is called by an ISR driven by the timer and collects at every round
 * one bit of entropy. We sample here the current value of the LSB of Timer1 
 * counter. The jitter of the interrupt process makes this random. 
 */
void collectSecondaryNoise()
{
    static uint32_t noiseBuffer = 0;
    static uint8_t collectedBits = 0;
    
    noiseBuffer = (noiseBuffer << 1) | (TCNT1L & 1);
    collectedBits++;

    if(collectedBits == 32) 
    {
        createSecondaryRandomNumber(noiseBuffer);
        collectedBits = 0;       
    }

    digitalWrite(PIN_YELLOW_LED_SECONDARY, collectedBits < 4 ? HIGH : LOW);
}

/**
 * We pass here the collected 32 bits into a CRC-32, note that this
 * CRC-32 is forever running so it acts as randomness extrector and
 * de-bias of the input source.
 */
void createSecondaryRandomNumber(uint32_t noiseBuffer)
{
    crc.update(noiseBuffer);
    uint32_t randomNumber = crc.finalize();

    for(int ix=0; ix<4; ix++) {
        secondaryRandomNumberReady(randomNumber & 0xFF);
        randomNumber = randomNumber >> 8;
    }
}

/**
 * Callback invoked once 8 bits of random data are ready.
 */
extern void secondaryRandomNumberReady(uint8_t secondaryRandomNumber);