// Power-On Self Tests.
// Copyright (C) 2018 Nicola Cimmino
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

extern SSD1306AsciiAvrI2c oled;

unsigned long chgPumpMinLevel = 0;

unsigned long chgPumpMaxLevel = 2 ^ 10;

unsigned long chgPumpRaiseTime = 0;

uint8_t chgPumpSenseCal = 0;

void performPost()
{
    oled.clear();
    oled.setCursor(0, 2);
    chargePumpCalibrate();
    chargePumpLo();
    chargePumpHi();
    oled.println("");
    oled.println("POST OK");
    delay(1000);
}

void chargePumpCalibrate()
{
    initChargePump();

    oled.print("CHP Cal");

    setChargePumpOutputsHiZ(true);
    pinMode(PIN_CHG_PUMP_SENSE, OUTPUT);
    digitalWrite(PIN_CHG_PUMP_SENSE, LOW);
    delay(1500);
    pinMode(PIN_CHG_PUMP_SENSE, INPUT);

    unsigned long idleVoltage = 2 ^ 10;
    for (uint8_t ix = 0; ix < 6; ix++)
    {
        idleVoltage = analogRead(PIN_CHG_PUMP_SENSE);
        delay(200);
    }

    chgPumpSenseCal = floor(idleVoltage / 3.3);

    Serial.println(chgPumpSenseCal);
    testOk();
}

void chargePumpLo()
{
    initChargePump();
    setChargePumpOutputsHiZ(true);

    oled.print("CHP Lo");

    unsigned long start = millis();
    while (true)
    {
        pinMode(PIN_CHG_PUMP_SENSE, INPUT);

        unsigned long newChgPumpLevel = analogRead(PIN_CHG_PUMP_SENSE);

        pinMode(PIN_CHG_PUMP_SENSE, OUTPUT);
        digitalWrite(PIN_CHG_PUMP_SENSE, LOW);

        if (newChgPumpLevel == chgPumpMinLevel)
        {
            break;
        }
        chgPumpMinLevel = newChgPumpLevel;

        if ((millis() - start) > 3000)
        {
            testFail();
        }

        delay(400);
    }

    pinMode(PIN_CHG_PUMP_SENSE, INPUT);

    // Must be below 5v.
    if (chgPumpMinLevel > 5 * chgPumpSenseCal)
    {
        testFail();
    }

    testOk();
}

void chargePumpHi()
{
    initChargePump();
    oled.print("CHP Hi");

    setChargePumpOutputsHiZ(true);
    unsigned long chargePumpLevel = 2 ^ 10;
    while (chargePumpLevel > chgPumpMinLevel)
    {
        chargePumpLevel = analogRead(PIN_CHG_PUMP_SENSE);

        pinMode(PIN_CHG_PUMP_SENSE, OUTPUT);
        digitalWrite(PIN_CHG_PUMP_SENSE, LOW);

        delay(200);

        pinMode(PIN_CHG_PUMP_SENSE, INPUT);
    }

    setChargePumpOutputsHiZ(false);

    uint8_t phase = 0;
    unsigned long lastChangeTime = millis();
    unsigned long start = millis();
    while (true)
    {
        digitalWrite(PIN_CHG_PUMP0, (phase % 2 == 0) ? HIGH : LOW);
        digitalWrite(PIN_CHG_PUMP1, (phase % 2 == 0) ? LOW : HIGH);
        digitalWrite(PIN_CHG_PUMP2, (phase % 2 == 0) ? HIGH : LOW);
        phase++;

        if ((phase % 32) == 0)
        {
            unsigned long newChgPumpLevel = analogRead(PIN_CHG_PUMP_SENSE);

            if (newChgPumpLevel != chgPumpMaxLevel)
            {
                lastChangeTime = millis();
            }

            chgPumpMaxLevel = newChgPumpLevel;

            if ((millis() - start) > 6000)
            {
                break;
                testFail();
            }

            if ((millis() - lastChangeTime) > 500)
            {
                break;
            }
        }
    }

    chgPumpRaiseTime = millis() - start;

    setChargePumpOutputsHiZ(true);
    testOk();
}

void testFail()
{
    uint8_t dots = ((oled.displayWidth() - oled.col()) / 5) - 9;
    for (; dots > 0; dots--)
    {
        oled.print(".");
    }
    oled.println("[FAIL]");
    while (true)
    {
        delay(1000);
    }
}

void testOk()
{
    uint8_t dots = ((oled.displayWidth() - oled.col()) / 5) - 7;
    for (; dots > 0; dots--)
    {
        oled.print(".");
    }
    oled.println("[OK]");
}