// Tests for the secondary noise source.
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
#include "../src/SecondaryNoiseSource.h"

void runTestSecondaryNoiseSource()
{
    proboInfo("Secondary Noise Source Test.");

    while (!SecondaryNoiseSource::instance()->isRandomDataReady())
    {
        proboAssertMaxIterations(10, "Waiting random word");

        delay(1000);
    }

    proboAssert(SecondaryNoiseSource::instance()->isRandomDataReady() == true, "Random data ready");
    proboAssert(SecondaryNoiseSource::instance()->getRandomData()[0] > 0, "Got positive number");
    proboAssert(SecondaryNoiseSource::instance()->isRandomDataReady() == false, "Random data not ready");

    proboPassed();
}
