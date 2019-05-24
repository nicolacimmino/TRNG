// Primary noise source.
// Here we drive the external charge pump and the zener noise source to get random data.
//
//  Copyright (C) 2019 Nicola Cimmino
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

#include "PrimaryNoiseSource.h"

void PrimaryNoiseSource::begin(uint8_t chargePumpPin0, uint8_t chargePumpPin1, uint8_t chargePumpPin2, uint8_t chargepPumPin3, uint8_t chargepPumpPinSense, uint8_t noiseInPin)
{
  this->chargePumpPin0 = chargePumpPin0;
  this->chargePumpPin1 = chargePumpPin1;
  this->chargePumpPin2 = chargePumpPin2;
  this->chargePumpPin3 = chargePumpPin3;
  this->chargepPumpPinSense = chargepPumpPinSense;
  this->noiseInPin = noiseInPin;

  //  Set ADC prescaler to 16 so we get higher sample rate than with default settings.
  _SFR_BYTE(ADCSRA) |= _BV(ADPS2);  // Set ADPS2
  _SFR_BYTE(ADCSRA) &= ~_BV(ADPS1); // Clear ADPS1
  _SFR_BYTE(ADCSRA) &= ~_BV(ADPS0); // Clear ADPS0

  pinMode(this->noiseInPin, INPUT);
  pinMode(this->chargepPumpPinSense, INPUT);
}

uint8_t PrimaryNoiseSource::getRandomByte()
{
  if (!this->isHighVoltageReseviourAboveMin())
  {
    this->chargeHighVoltageReserviour();
  }

  if (!this->isHighVoltageReseviourAboveMin())
  {
    this->sourceGood = false;

    return 0;
  }

  this->sourceGood = true;

  return this->sample8BitsWhitenedNoise();
}

/**
 * Run the charge pump until it reaches the preset high level. This function blocks
 * until the level is reached. Upon return the charge pump is stopped and the reserviour
 * cap loaded.
 */
void PrimaryNoiseSource::chargeHighVoltageReserviour()
{
  this->setChargePumpOutputsHiZ(false);

  unsigned char phase = 0;
  unsigned long startTime = millis();
  while (analogRead(this->chargepPumpPinSense) < CHG_PUMP_LIMIT_HI)
  {
    digitalWrite(this->chargePumpPin0, (phase % 2 == 0) ? HIGH : LOW);
    digitalWrite(this->chargePumpPin1, (phase % 2 == 0) ? LOW : HIGH);
    digitalWrite(this->chargePumpPin2, (phase % 2 == 0) ? HIGH : LOW);
    digitalWrite(this->chargePumpPin3, (phase % 2 == 0) ? LOW : HIGH);
    phase++;

    // millis wrapped around, don't get stuck in alarm.
    if (millis() < startTime)
    {
      startTime = millis();
    }

    if (millis() - startTime > CHG_PUMP_ALARM_DELAY_MS)
    {
      // Give up.
      return;
    }
  }

  this->setChargePumpOutputsHiZ(true);
}

bool PrimaryNoiseSource::isHighVoltageReseviourAboveMin()
{
  return analogRead(this->chargepPumpPinSense) > CHG_PUMP_LIMIT_LO;
}

/**
 * Set the charge pump output hi impedance on/off.
 */
void PrimaryNoiseSource::setChargePumpOutputsHiZ(bool on)
{
  pinMode(this->chargePumpPin0, on ? INPUT : OUTPUT);
  pinMode(this->chargePumpPin1, on ? INPUT : OUTPUT);
  pinMode(this->chargePumpPin2, on ? INPUT : OUTPUT);
  pinMode(this->chargePumpPin3, on ? INPUT : OUTPUT);
}

/**
 * The data collected from the noise might be biased, we do some
 * whitening applying John von Neumann whitening algoirthm.
*/
uint8_t PrimaryNoiseSource::sample8BitsWhitenedNoise()
{
  byte whitenedOut = 0;
  byte whitenedBitsCount = 0;

  while (true)
  {
    uint8_t sampledNoise = this->sampleNBitsOfNoise(2);

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
uint8_t PrimaryNoiseSource::sampleNBitsOfNoise(uint8_t bits)
{
  analogReference(INTERNAL);

  int analogValue = 0;
  uint8_t sampledNoise = 0;
  for (int ix = 0; ix < bits; ix++)
  {
    analogValue = 0;
    while (analogValue == 0)
    {
      analogValue = analogRead(this->noiseInPin);
    }

    sampledNoise = (sampledNoise << 1) | (analogValue & 1);
  }

  analogReference(DEFAULT);

  return sampledNoise;
}