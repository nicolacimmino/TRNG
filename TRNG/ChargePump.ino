// ChargePump implements ancillary functions for the TRNG charge pump.
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

#define PIN_CHG_PUMP_SENSE A1
#define PIN_YELLOW_LED 4
#define PIN_GREEN_LED 5
#define PIN_CHG_PUMP0 13
#define PIN_CHG_PUMP1 11
#define PIN_CHG_PUMP2 12
#define CHG_PUMP_LIMIT_HI 320
#define CHG_PUMP_LIMIT_LO 260
#define CHG_PUMP_ALARM_DELAY_MS 10000

void initChargePump()
{
    //  Set ADC prescaler to 16 so we get higher sample rate than with default settings.
    _SFR_BYTE(ADCSRA) |= _BV(ADPS2);  // Set ADPS2
    _SFR_BYTE(ADCSRA) &= ~_BV(ADPS1); // Clear ADPS1
    _SFR_BYTE(ADCSRA) &= ~_BV(ADPS0); // Clear ADPS0

    pinMode(PIN_NOISE_IN, INPUT);
    pinMode(PIN_CHG_PUMP_SENSE, INPUT);
    pinMode(PIN_YELLOW_LED, OUTPUT);
    pinMode(PIN_GREEN_LED, OUTPUT);

    // Use internal 1.1V reference for the A/D converters
    // since the noise levels we get are rather low.
    analogReference(INTERNAL);
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
