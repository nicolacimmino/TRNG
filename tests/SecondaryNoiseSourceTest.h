

#include "Probo.h"
#include "../src/SecondaryNoiseSource.h"

void runTestSecondaryNoiseSource()
{
    proboInfo("Secondary Noise Source Test.");

    while (!SecondaryNoiseSource::instance()->isRandomWordReady())
    {
        proboAssertMaxIterations(10, "Waiting random word");

        delay(1000);
    }

    proboAssert(SecondaryNoiseSource::instance()->isRandomWordReady() == true, "Random number ready");
    proboAssert(SecondaryNoiseSource::instance()->getRandomWord() > 0, "Got positive number");
    proboAssert(SecondaryNoiseSource::instance()->isRandomWordReady() == false, "Random number not ready");

    proboPassed();
}
