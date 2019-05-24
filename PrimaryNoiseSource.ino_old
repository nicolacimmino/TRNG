// Primary noise source pulls 8 bits of entropy from a withened bitsream 
// generated from a hardware white noise generator. 
//  Copyright (C) 2018 Nicola Cimmino
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

/**
 * Callback invoked once 8 bits of random noise are ready.
 */
extern void primaryRandomNumberReady(uint8_t primaryRandomNumber);

void initPrimaryNoiseSource()
{
    initChargePump();    
}

void runPrimaryNoiseSource()
{
  chargeHighVoltageReserviour();
  
  // The charge pump is not running now, so things are silent and we can start
  // to generate random numbers, until the reserviour runs low.
  while (isHighVoltageReseviourAboveMin())
  {
    uint8_t randomByte = sample8BitsWhitenedNoise();    
    primaryRandomNumberReady(randomByte);    
  }
}

/**
 * The data collected from the noise might be biased, we do some
 * whitening applying John von Neumann whitening algoirthm.
*/
uint8_t sample8BitsWhitenedNoise()
{
  byte whitenedOut = 0;
  byte whitenedBitsCount = 0;

  while (true)
  {
    uint8_t sampledNoise = sampleNBitsOfNoise(2);

    if ((sampledNoise & 1) != ((sampledNoise >> 1) & 1))
    {
      whitenedOut = (whitenedOut << 1) | (sampledNoise & 1);
      whitenedBitsCount++;
      if (whitenedBitsCount == 8)
      {
        return whitenedOut;
      }
    }
  }
}

/**
 * Sample N (max 8) bits from the analog noise source.
 */
uint8_t sampleNBitsOfNoise(uint8_t bits)
{
  int analogValue = 0;
  uint8_t sampledNoise = 0;
  for (int ix = 0; ix < bits; ix++)
  {
    analogValue = 0;
    while (analogValue == 0)
    {
      analogValue = analogRead(PIN_NOISE_IN);
    }

    sampledNoise = (sampledNoise << 1) | (analogValue & 1);
  }

  return sampledNoise;
}
