// Secondary noise source pulls 32 bits of entropy from the internal time jitter.
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

#ifndef __SECONDARY_NOISE_SOURCE_H__
#define __SECONDARY_NOISE_SOURCE_H__

#include <avr/wdt.h>
#include <CRC32.h>

class SecondaryNoiseSource
{
public:
    static SecondaryNoiseSource* instance();    
    void collectSecondaryNoise();
    bool isRandomDataReady();
    uint8_t *getRandomData();        
private:
    SecondaryNoiseSource();
    static SecondaryNoiseSource* theInstance;        
    CRC32 crc;
    void createSecondaryRandomNumber(uint32_t noiseBuffer);
    bool randomDataReady = false;
    uint8_t randomData[4];
};

#endif
