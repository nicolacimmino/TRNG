

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
