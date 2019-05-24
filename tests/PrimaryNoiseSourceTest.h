

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

