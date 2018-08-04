// TRNG implements a true random numbers generator.
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

#define PIN_NOISE_IN A0

/*
 * Arduino setup.
 */
void setup()
{
  Serial.begin(115200);

  initPrimaryNoiseSource();
  initSecondaryNoiseSource();
}

/*
 * Arduino main loop.
 */
void loop()
{
  runPrimaryNoiseSource();
}

/*
 * A random number from the primary source is ready. 
 * We feed this into the randomness extractor entropy pool.
 */
void primaryRandomNumberReady(uint8_t primaryRandomNumber)
{
  randomnessExtractorCollectEntropy(primaryRandomNumber);
}

/*
 * A random number from the secondary source is ready. 
 * We feed this into the randomness extractor key entropy pool.
 */
void secondaryRandomNumberReady(uint8_t secondaryRandomNumber)
{
  randomnessExtractorCollectKeyEntropy(secondaryRandomNumber);
}

/*
 * A random number from the randomness extraxtor is ready.
 * This is our final output.
 */
void extractedRandomnessReady(uint8_t extracredRandomNumber)
{
  outputDataHex(extracredRandomNumber);
}

/*
 * Output data as two digits HEX, dot separated with 32 bytes per line.
 */
void outputDataHex(byte randomNumber)
{
  byte static outputBytes = 0;

  Serial.print("0123456789ABCDEF"[(randomNumber >> 4) & 0xF]);
  Serial.print("0123456789ABCDEF"[randomNumber & 0xF]);
  Serial.print((outputBytes % 32 == 31) ? "\n" : ".");
  outputBytes++;
}
