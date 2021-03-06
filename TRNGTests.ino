// Main sketch to run all tests.
//
// Note: this needs to be in the root of the project folder due to the way the Arduino compiler
// grabs only files in the subfolders and copies them into the output folder.
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

#include "src/TRNG.h"
#include "tests/SecondaryNoiseSourceTest.h"
#include "tests/PrimaryNoiseSourceTest.h"
#include "tests/RandomnessExtractorTest.h"

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    proboInit(&Serial);
    runTestPrimaryNoiseSource();
    runTestSecondaryNoiseSource();
    runTestRandomnessExtractor();

    spitupNumbers();
}

void spitupNumbers()
{
    TRNG trng;
    trng.begin(PIN_CHG_PUMP0, PIN_CHG_PUMP1, PIN_CHG_PUMP2, PIN_CHG_PUMP3, PIN_CHG_PUMP_SENSE, PIN_CHG_PUMP_NOISEIN);

    Serial.println("Waiting for TRNG to collect enough entropy...");

    while (true)
    {
        trng.loop();

        while (trng.isRandomDataReady())
        {
            outputDataHex(trng.getRandomByte());
        }        
    }
}

/*
 * Output data as two digits HEX, dot separated with 32 bytes per line.
 */
void outputDataHex(uint8_t randomNumber)
{
  uint8_t static outputBytes = 0;
  
  Serial.print("0123456789ABCDEF"[(randomNumber >> 4) & 0xF]);
  Serial.print("0123456789ABCDEF"[randomNumber & 0xF]);
  Serial.print((outputBytes % 32 == 31) ? "\n" : ".");
  outputBytes++;  
}