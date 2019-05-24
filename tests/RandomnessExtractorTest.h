// Tests for the randomness extractor.
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
#include "../src/RandomnessExtractor.h"

void runTestRandomnessExtractor()
{
    proboInfo("Randomness Extractor Test.");

    RandomnessExtractor *randomnessExtractor = new RandomnessExtractor();

    while (!randomnessExtractor->isKeyValid())
    {
        proboAssertMaxIterations(32, "Waiting key ready", true);

        randomnessExtractor->collectKeyEntropy(random(0, 255));                
    }


    while (!randomnessExtractor->isRandomDataReady())
    {
        proboAssertMaxIterations(32, "Waiting random data", true);
        
        randomnessExtractor->collectEntropy(random(0, 255));        
    }

    proboAssert(randomnessExtractor->isRandomDataReady() == true, "Random data ready");
    uint8_t *data = randomnessExtractor->getRandomData();

    proboAssert(data[0] != data[1], "Got different numbers"); // Statistically can fail with a 1/256 probability

    proboAssert(randomnessExtractor->isRandomDataReady() == false, "Random data not ready");

    proboPassed();
}
