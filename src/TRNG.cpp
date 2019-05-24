
#include "TRNG.h"

void TRNG::begin(uint8_t chargePumpPin0, uint8_t chargePumpPin1, uint8_t chargePumpPin2, uint8_t chargepPumPin3, uint8_t chargepPumPinSense, uint8_t chargepPumPinNoise)
{
    this->primaryNoiseSource.begin(chargePumpPin0, chargePumpPin1, chargePumpPin2, chargepPumPin3, chargepPumPinSense, chargepPumPinNoise);
}

void TRNG::loop()
{
    uint8_t randomByte = this->primaryNoiseSource.getRandomByte();

    if (!this->primaryNoiseSource.sourceGood)
    {
        return;
    }
}
