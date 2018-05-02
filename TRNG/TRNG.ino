
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
#define PIN_CHG_PUMP_SENSE A1
#define PIN_YELLOW_LED 4
#define PIN_GREEN_LED 5
#define PIN_CHG_PUMP0 13
#define PIN_CHG_PUMP1 11
#define PIN_CHG_PUMP2 12
#define CHG_PUMP_LIMIT_HI 320
#define CHG_PUMP_LIMIT_LO 260
#define CHG_PUMP_ALARM_DELAY_MS 10000

// Tempoary storage for output from the whitening process.
byte whitenedOut = 0;

// Amount of bits produced by the whitening pocess.
byte whitenedBitsCount = 0;

/**
 * Arduino setup.
 */
void setup()
{
  Serial.begin(115200);

  pinMode(PIN_NOISE_IN, INPUT);
  pinMode(PIN_CHG_PUMP_SENSE, INPUT);
  pinMode(PIN_YELLOW_LED, OUTPUT);
  pinMode(PIN_GREEN_LED, OUTPUT);

  // Use internal 1.1V reference for the A/D converters
  // since the noise levels we get are rather low.
  analogReference(INTERNAL);
}

/**
 * Arduino main loop.
 */
void loop()
{
  chargeHighVoltageReserviour();

  // The charge pump is not running now, so things are silent and we can start
  // to generate random numbers, until the reserviour runs low.
  while (isHighVoltageReseviourAboveMin())
  {
    generateRandomNumbers();
  }
}

/**
 * Run the charge pump until it reaches the preset high level. This function blocks
 * until the level is reached. Upon return the charge pump is stopped and the reserviour
 * cap loaded.
 */
void chargeHighVoltageReserviour()
{
  setChargePumpOutputsHiZ(false);
  setChargePumpIndicator(true);

  long chgPumpLevel;
  unsigned char phase = 0;
  unsigned long startTime = millis();
  while ((chgPumpLevel = analogRead(PIN_CHG_PUMP_SENSE)) < CHG_PUMP_LIMIT_HI)
  {
    digitalWrite(PIN_CHG_PUMP0, (phase % 2 == 0) ? HIGH : LOW);
    digitalWrite(PIN_CHG_PUMP1, (phase % 2 == 0) ? LOW : HIGH);
    digitalWrite(PIN_CHG_PUMP2, (phase % 2 == 0) ? HIGH : LOW);
    phase++;

    // millis wrapped around, don't get stuck in alarm.
    if (millis() < startTime)
    {
      startTime = millis();
    }

    if (millis() - startTime > CHG_PUMP_ALARM_DELAY_MS)
    {
      chargePumpAlarmAndHalt(chgPumpLevel);
    }
  }

  setChargePumpOutputsHiZ(true);
  setChargePumpIndicator(false);
}

bool isHighVoltageReseviourAboveMin()
{
  return analogRead(PIN_CHG_PUMP_SENSE) > CHG_PUMP_LIMIT_LO;
}

/**
 * Enter charge pump failure alarm mode and halt here.
 * 
 * Yellow flashes indicating the fault.
 */
void chargePumpAlarmAndHalt(long reachedLevel)
{
  setChargePumpOutputsHiZ(true);

  while (true)
  {
    digitalWrite(PIN_YELLOW_LED, LOW);
    delay(800);
    digitalWrite(PIN_YELLOW_LED, HIGH);
    delay(200);
    Serial.print("ALARM_CHARGE_PUMP ");
    Serial.println(reachedLevel);
  }
}

/**
 * Set the charge pump indicator on/off.
 * 
 * Yellow indicates the charge pump is running, green that it's off.
 */
void setChargePumpIndicator(bool on)
{
  digitalWrite(PIN_YELLOW_LED, on ? HIGH : LOW);
  digitalWrite(PIN_GREEN_LED, on ? LOW : HIGH);
}

/**
 * Set the charge pump output hi impedance.
 */
void setChargePumpOutputsHiZ(bool on)
{
  pinMode(PIN_CHG_PUMP0, on ? INPUT : OUTPUT);
  pinMode(PIN_CHG_PUMP1, on ? INPUT : OUTPUT);
  pinMode(PIN_CHG_PUMP2, on ? INPUT : OUTPUT);
}

/**
 * Sample the generated noise and use it to create a stream of random numbers.
 */
void generateRandomNumbers()
{
  uint32_t sampledNoise = sampleNoise();

  // The data collected so far might be biased, we do some
  // whitening applying John von Neumann whitening algoirthm.
  // The algorithm consumes 2+ bits to generate one bit, the
  // amount of consumed bits depends on the biasig of the
  // source. The algorithm consits in taking couple of bits,
  // if they are equal they are discarded if they are "10" then
  // a 1 is taken as output, if they are "01" then 0 is taken
  // as output.
  for (int ix = 0; ix < 32; ix += 2)
  {
    if ((sampledNoise & 1) != ((sampledNoise >> 1) & 1))
    {
      whitenedOut = (whitenedOut << 1) | (sampledNoise & 1);
      whitenedBitsCount++;
      if (whitenedBitsCount == 8)
      {
        outputDataHex(whitenedOut);
        whitenedBitsCount = 0;
      }
    }
    sampledNoise = sampledNoise >> 2;
  }
}

/**
 * Sample 32 bits from the analog noise source.
 */
uint32_t sampleNoise()
{
  int analogValue = 0;
  uint32_t sampledNoise = 0;
  for (int ix = 0; ix < 32; ix++)
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

/*
 * Output data as two digits HEX, dot separated with 16 bytes per line.
 */
void outputDataHex(byte randomNumber)
{
  Serial.print("0123456789ABCDEF"[(randomNumber >> 4) & 0xF]);
  Serial.print("0123456789ABCDEF"[randomNumber & 0xF]);
  Serial.print(".");
}
