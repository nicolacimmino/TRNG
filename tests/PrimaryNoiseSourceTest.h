
// Tests for the primary noise source.
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

#include "Probo.h"
#include "../src/PrimaryNoiseSource.h"

#define PIN_CHG_PUMP_NOISEIN A0
#define PIN_CHG_PUMP_SENSE A1
#define PIN_CHG_PUMP0 2
#define PIN_CHG_PUMP1 3
#define PIN_CHG_PUMP2 4
#define PIN_CHG_PUMP3 5

void runTestPrimaryNoiseSource()
{
    proboInfo("Primary Noise Source Test.");

    PrimaryNoiseSource *primaryNoiseSource = new PrimaryNoiseSource();
    primaryNoiseSource->begin(PIN_CHG_PUMP0, PIN_CHG_PUMP1, PIN_CHG_PUMP2, PIN_CHG_PUMP3, PIN_CHG_PUMP_SENSE, PIN_CHG_PUMP_NOISEIN);

    proboAssert(primaryNoiseSource->getRandomByte() != primaryNoiseSource->getRandomByte(), "Random numbers differ");

    proboPassed();
}

