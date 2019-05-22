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

#include <SSD1306AsciiAvrI2c.h>

#define DISPLAY_I2C_ADDRESS 0x3C
SSD1306AsciiAvrI2c oled;

extern bool randomnessExtractorSecretKeyValid;
extern bool randomnessExtractorSecretKeyId;
extern unsigned int outputSpeedbps;
extern unsigned long chgPumpMinLevel;
extern unsigned long chgPumpMaxLevel;
extern unsigned long chgPumpRaiseTime;

void initDisplay()
{
    oled.begin(&Adafruit128x64, DISPLAY_I2C_ADDRESS);
    oled.setFont(System5x7);
}

void refreshDisplay()
{
    oled.setCursor(0, 0);
    oled.print(!highVoltageReserviourGood ? "CHP " : "    ");
    if (randomnessExtractorSecretKeyValid)
    {
        oled.print(randomnessExtractorSecretKeyId ? "KEYA      " : "     KEYB ");
    }
    else
    {
        oled.print("     ");
    }

    oled.setCursor(0, 2);
    oled.print("Vchp: ");
    oled.print((chgPumpLevel / 2) / 10.0);
    oled.print("V");
    oled.clearToEOL();

    oled.setCursor(0, 3);
    oled.print("VchpMin: ");
    oled.print((chgPumpMinLevel / 2) / 10.0);
    oled.print("V");
    oled.clearToEOL();

    oled.setCursor(0, 4);
    oled.print("VchpMax: ");
    oled.print((chgPumpMaxLevel / 2) / 10.0);
    oled.print("V");
    oled.clearToEOL();

    oled.setCursor(0, 5);
    oled.print("TChpRise: ");
    oled.print(chgPumpRaiseTime);
    oled.print("mS");
    oled.clearToEOL();

    oled.setCursor(0, 6);
    oled.print("Out:  ");
    oled.print(outputSpeedbps);
    oled.print("bps");
    oled.clearToEOL();
}
