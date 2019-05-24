
#ifndef __SECONDARY_NOISE_SOURCE_H__
#define __SECONDARY_NOISE_SOURCE_H__

#include <avr/wdt.h>
#include <CRC32.h>

class SecondaryNoiseSource
{
public:
    static SecondaryNoiseSource* instance();    
    void collectSecondaryNoise();
    bool isRandomWordReady();
    uint32_t getRandomWord();        
private:
    SecondaryNoiseSource();
    static SecondaryNoiseSource* theInstance;        
    CRC32 crc;
    void createSecondaryRandomNumber(uint32_t noiseBuffer);
    bool randomWordReady = false;
    uint32_t randomWord;
};

#endif
