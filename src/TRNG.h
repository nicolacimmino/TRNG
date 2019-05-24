
#ifndef __TRNG_H__
#define __TRNG_H__

#include "PrimaryNoiseSource.h"
#include <Arduino.h>

class TRNG
{
public:
    void begin(uint8_t chargePumpPin0, uint8_t chargePumpPin1, uint8_t chargePumpPin2, uint8_t chargepPumPin3, uint8_t chargepPumPinSense, uint8_t chargepPumPinNoise);
    void loop();

private:
    PrimaryNoiseSource primaryNoiseSource;    
};

#endif