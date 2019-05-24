
#include "src/TRNG.h"

#include "tests/SecondaryNoiseSourceTest.h"
#include "tests/PrimaryNoiseSourceTest.h"

void setup()
{ 
    Serial.begin(115200);
}

void loop()
{
    proboInit(&Serial);
    runTestPrimaryNoiseSource();
    runTestSecondaryNoiseSource();

    while(true);
}

