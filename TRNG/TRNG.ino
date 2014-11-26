// TRNG implements a true random numbers generator.
//  Copyright (C) 2014 Nicola Cimmino
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

#define GENERATOR_PWR_PIN 10

#define INPUT_SIGNAL_PIN A0


void setup()
{
  Serial.begin(112500);
  
  pinMode(GENERATOR_PWR_PIN, OUTPUT);
  digitalWrite(GENERATOR_PWR_PIN, HIGH);
  
  pinMode(INPUT_SIGNAL_PIN, INPUT);
  
   // Set ADC prescaler to 16 so we get higher sample 
   // rate than with default settings.
  _SFR_BYTE(ADCSRA) |=  _BV(ADPS2); // Set ADPS2
  _SFR_BYTE(ADCSRA) &= ~_BV(ADPS1); // Clear ADPS1
  _SFR_BYTE(ADCSRA) &= ~_BV(ADPS0); // Clear ADPS0
  
  // Use internal 1.1V reference
  analogReference(INTERNAL);
}

int average=0;
byte randomOut=0;
byte whitenedOut=0;
byte whitenedBitsCount=0;

void loop()
{
  // Collect 8 random bits. A bit is set to 1 if the current 
  // reading is above the running average, zero otherwise.
  // Note that the average keeps running, it's not the average
  // of these 8 samples. This allows to accomodate for drifts
  // in the reading due to temperature, supply voltage, aging etc.
  for(int ix=0; ix<8;ix++)
  {
    int noiseReading = analogRead(INPUT_SIGNAL_PIN);
    average=0.9*average+0.1*noiseReading;
    randomOut = (randomOut<<1)|((noiseReading>average)?1:0);
  }
    
  // The data collected so far might be biased, we do some
  // whitening applying John von Neumann whitening algoirthm.
  // The algorithm consumes 2+ bits to generate one bit, the
  // amount of consumed bits depends on the biasig of the
  // source. The algorithm consits in taking couple of bits,
  // if they are equal they are discarded if they are "10" then
  // a 1 is taken as output, if they are "01" then 0 is taken
  // as output.
  for(int ix=0;ix<8;ix+=2)
  {
    if((randomOut&1) != ((randomOut>>1)&1))
    {
      whitenedOut=(whitenedOut<<1)|(randomOut&1);
      whitenedBitsCount++;
      if(whitenedBitsCount==8)
      {
        //Serial.println(whitenedOut);
        whitenedBitsCount=0;
        
        evaluateOneZerosBalance(whitenedOut);
      }
     }
     randomOut=randomOut>>2;
   }
}

/*
 * Evaluates the bias towards zeros or ones. Prints one
 * reasult every 1Kbyte block.
 */
void evaluateOneZerosBalance(byte randomNumber)
{
  static int32_t ones=0;
  static int32_t zeros=0;
  
  for(int ix=0; ix<8;ix++)
  {
    if(randomNumber&1 == 1)
    {
      ones++; 
    }
    else
    {
      zeros++;
    }
    randomNumber=randomNumber>>1; 
    
    if((ones+zeros)%(1024*8)==0)
    {
      Serial.print(zeros);
      Serial.print("/");
      Serial.println(ones);
      ones=0;
      zeros=0; 
    }
  }
}
