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

#define OUTPUT_BLOCK_SIZE 1024

// Total amount of random bytes oputput so far.
uint32_t outputBytes=0;

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

void loop()
{
  
  // Temporay storage for output random values.
  byte static randomOut=0;
 
  // Tempoary storage for output from the whitening process.
  byte static whitenedOut=0;
  
  // Amount of bits produced by the whitening pocess.
  byte static whitenedBitsCount=0;
  
  // Current input signal average value.
  float static average=0;

  // Collect 8 random bits by keeping track of the 
  // average signal level with a long IIR low pass
  // and sampling a 1 bit when the current signal is
  // above the average and 0 otherwise.
  
  for(int ix=0; ix<8;ix++)
  {
    int noiseReading = analogRead(INPUT_SIGNAL_PIN);
    average=0.99f*average+0.01f*noiseReading;
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
        outputDataHex(whitenedOut);
        whitenedBitsCount=0;
      }
     }
     randomOut=randomOut>>2;
   }
   
   if(outputBytes>=OUTPUT_BLOCK_SIZE)
   {
     while(Serial.read()>0);
     while(!Serial.available());
     Serial.println("");
     outputBytes=0;
   }
}

/*
 * Output data as two digits HEX, dot separated
 * with 16 bytes per line.
 */
void outputDataHex(byte randomNumber)
{
  Serial.print("0123456789ABCDEF"[randomNumber>>4]);
  Serial.print("0123456789ABCDEF"[randomNumber&0xF]);
  Serial.print((outputBytes%32==31)?"\r\n":""); 
  outputBytes++;  
}
