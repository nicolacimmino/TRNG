
#ifndef _TRNG_PRIMARY_NOISE_SOURCE_H_
#define _TRNG_PRIMARY_NOISE_SOURCE_H_

#define CHG_PUMP_LIMIT_HI 300
#define CHG_PUMP_LIMIT_LO 280
#define CHG_PUMP_ALARM_DELAY_MS 10000

#include <Arduino.h>

class PrimaryNoiseSource
{
public:
    void begin(uint8_t chargePumpPin0, uint8_t chargePumpPin1, uint8_t chargePumpPin2, uint8_t chargepPumPin3, uint8_t chargepPumpPinSense, uint8_t noiseInPin);    
    uint8_t getRandomByte();
    bool isHighVoltageReseviourAboveMin();
    bool sourceGood = false;        
    
private:
    uint8_t chargePumpPin0;
    uint8_t chargePumpPin1;
    uint8_t chargePumpPin2;
    uint8_t chargePumpPin3;
    uint8_t chargepPumpPinSense;
    uint8_t noiseInPin;
    void chargeHighVoltageReserviour();
    void setChargePumpOutputsHiZ(bool on);
    uint8_t sample8BitsWhitenedNoise();
    uint8_t sampleNBitsOfNoise(uint8_t bits);    
};

#endif