EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:trng-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ZENER D1
U 1 1 5A32F398
P 4850 1300
F 0 "D1" H 4850 1400 50  0000 C CNN
F 1 "12V" H 4850 1200 50  0000 C CNN
F 2 "" H 4850 1300 50  0000 C CNN
F 3 "" H 4850 1300 50  0000 C CNN
	1    4850 1300
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5A32F417
P 4600 1100
F 0 "R1" V 4500 1100 50  0000 C CNN
F 1 "530K" V 4700 1100 50  0000 C CNN
F 2 "" V 4530 1100 50  0000 C CNN
F 3 "" H 4600 1100 50  0000 C CNN
	1    4600 1100
	0    1    1    0   
$EndComp
$Comp
L CP C5
U 1 1 5A32F468
P 4350 2250
F 0 "C5" H 4375 2350 50  0000 L CNN
F 1 "10uF" H 4375 2150 50  0000 L CNN
F 2 "" H 4388 2100 50  0000 C CNN
F 3 "" H 4350 2250 50  0000 C CNN
	1    4350 2250
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5A32F6B9
P 2700 1750
F 0 "C3" H 2725 1850 50  0000 L CNN
F 1 "100n" H 2725 1650 50  0000 L CNN
F 2 "" H 2738 1600 50  0000 C CNN
F 3 "" H 2700 1750 50  0000 C CNN
	1    2700 1750
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5A32F6F6
P 3250 1750
F 0 "C4" H 3275 1850 50  0000 L CNN
F 1 "100n" H 3275 1650 50  0000 L CNN
F 2 "" H 3288 1600 50  0000 C CNN
F 3 "" H 3250 1750 50  0000 C CNN
	1    3250 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 5A32FA45
P 4350 2500
F 0 "#PWR8" H 4350 2250 50  0001 C CNN
F 1 "GND" H 4350 2350 50  0000 C CNN
F 2 "" H 4350 2500 50  0000 C CNN
F 3 "" H 4350 2500 50  0000 C CNN
	1    4350 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 5A32FA69
P 4850 1650
F 0 "#PWR1" H 4850 1400 50  0001 C CNN
F 1 "GND" H 4850 1500 50  0000 C CNN
F 2 "" H 4850 1650 50  0000 C CNN
F 3 "" H 4850 1650 50  0000 C CNN
	1    4850 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1650 4850 1500
Wire Wire Line
	4350 2500 4350 2400
Wire Wire Line
	4750 1100 4850 1100
Wire Wire Line
	4850 1100 4900 1100
$Comp
L C C1
U 1 1 5A32FB09
P 5050 1100
F 0 "C1" V 5000 950 50  0000 L CNN
F 1 "100n" V 5200 1050 50  0000 L CNN
F 2 "" H 5088 950 50  0000 C CNN
F 3 "" H 5050 1100 50  0000 C CNN
	1    5050 1100
	0    1    1    0   
$EndComp
Connection ~ 4850 1100
Connection ~ 3250 2000
Connection ~ 2700 2000
$Comp
L VCC #PWR2
U 1 1 5A33016D
P 1550 1350
F 0 "#PWR2" H 1550 1200 50  0001 C CNN
F 1 "VCC" H 1550 1500 50  0000 C CNN
F 2 "" H 1550 1350 50  0000 C CNN
F 3 "" H 1550 1350 50  0000 C CNN
	1    1550 1350
	1    0    0    -1  
$EndComp
Text GLabel 2150 1500 1    60   Input ~ 0
PH0
Text GLabel 2700 1500 1    60   Input ~ 0
PH1
Wire Wire Line
	2700 2000 2700 1900
Wire Wire Line
	2700 1600 2700 1500
Wire Wire Line
	3250 1600 3250 1500
Wire Wire Line
	3250 1900 3250 2000
$Comp
L C C2
U 1 1 5ADB0E3F
P 2150 1750
F 0 "C2" H 2175 1850 50  0000 L CNN
F 1 "100n" H 2175 1650 50  0000 L CNN
F 2 "" H 2188 1600 50  0000 C CNN
F 3 "" H 2150 1750 50  0000 C CNN
	1    2150 1750
	1    0    0    -1  
$EndComp
Text GLabel 3250 1500 1    60   Input ~ 0
PH2
Wire Wire Line
	2150 1900 2150 2000
Connection ~ 2150 2000
Wire Wire Line
	2150 1600 2150 1500
$Comp
L INDUCTOR L1
U 1 1 5ADB1265
P 4000 2000
F 0 "L1" V 3950 2050 50  0000 C CNN
F 1 "INDUCTOR" V 4150 2100 50  0001 C CNN
F 2 "" H 4000 2000 50  0000 C CNN
F 3 "" H 4000 2000 50  0000 C CNN
	1    4000 2000
	0    -1   -1   0   
$EndComp
Connection ~ 4350 2000
Wire Wire Line
	1550 1350 1550 2000
$Comp
L R R2
U 1 1 5ADB16EE
P 5250 1400
F 0 "R2" V 5330 1400 50  0000 C CNN
F 1 "1K5" V 5250 1400 50  0000 C CNN
F 2 "" V 5180 1400 50  0000 C CNN
F 3 "" H 5250 1400 50  0000 C CNN
	1    5250 1400
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR3
U 1 1 5ADB179B
P 5250 1650
F 0 "#PWR3" H 5250 1400 50  0001 C CNN
F 1 "GND" H 5250 1500 50  0000 C CNN
F 2 "" H 5250 1650 50  0000 C CNN
F 3 "" H 5250 1650 50  0000 C CNN
	1    5250 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 1650 5250 1550
Connection ~ 5250 1100
Wire Wire Line
	5250 1100 5250 1250
$Comp
L R R3
U 1 1 5ADB3536
P 4850 2000
F 0 "R3" V 4930 2000 50  0000 C CNN
F 1 "50K" V 4750 2000 50  0000 C CNN
F 2 "" V 4780 2000 50  0000 C CNN
F 3 "" H 4850 2000 50  0000 C CNN
	1    4850 2000
	0    -1   -1   0   
$EndComp
$Comp
L R R4
U 1 1 5ADB35B9
P 5250 2250
F 0 "R4" V 5150 2250 50  0000 C CNN
F 1 "1K" V 5350 2250 50  0000 C CNN
F 2 "" V 5180 2250 50  0000 C CNN
F 3 "" H 5250 2250 50  0000 C CNN
	1    5250 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR9
U 1 1 5ADB3627
P 5250 2500
F 0 "#PWR9" H 5250 2250 50  0001 C CNN
F 1 "GND" H 5250 2350 50  0000 C CNN
F 2 "" H 5250 2500 50  0000 C CNN
F 3 "" H 5250 2500 50  0000 C CNN
	1    5250 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2000 5250 2000
Wire Wire Line
	5250 2000 5500 2000
Wire Wire Line
	5250 2000 5250 2100
Wire Wire Line
	5250 2500 5250 2400
Text GLabel 5500 2000 2    60   Input ~ 0
CPS
Connection ~ 5250 2000
$Comp
L D_Schottky D2
U 1 1 5ADB4CE0
P 1850 2000
F 0 "D2" H 1850 2100 50  0000 C CNN
F 1 "D_Schottky" H 1850 1900 50  0001 C CNN
F 2 "" H 1850 2000 50  0000 C CNN
F 3 "" H 1850 2000 50  0000 C CNN
	1    1850 2000
	-1   0    0    1   
$EndComp
$Comp
L D_Schottky D3
U 1 1 5ADB4EB9
P 2450 2000
F 0 "D3" H 2450 2100 50  0000 C CNN
F 1 "D_Schottky" H 2450 1900 50  0001 C CNN
F 2 "" H 2450 2000 50  0000 C CNN
F 3 "" H 2450 2000 50  0000 C CNN
	1    2450 2000
	-1   0    0    1   
$EndComp
$Comp
L D_Schottky D4
U 1 1 5ADB4F15
P 3000 2000
F 0 "D4" H 3000 2100 50  0000 C CNN
F 1 "D_Schottky" H 3000 1900 50  0001 C CNN
F 2 "" H 3000 2000 50  0000 C CNN
F 3 "" H 3000 2000 50  0000 C CNN
	1    3000 2000
	-1   0    0    1   
$EndComp
$Comp
L D_Schottky D5
U 1 1 5ADB4F70
P 3500 2000
F 0 "D5" H 3500 2100 50  0000 C CNN
F 1 "D_Schottky" H 3500 1900 50  0001 C CNN
F 2 "" H 3500 2000 50  0000 C CNN
F 3 "" H 3500 2000 50  0000 C CNN
	1    3500 2000
	-1   0    0    1   
$EndComp
Wire Wire Line
	1550 2000 1700 2000
Wire Wire Line
	2000 2000 2150 2000
Wire Wire Line
	2150 2000 2300 2000
Wire Wire Line
	2600 2000 2700 2000
Wire Wire Line
	2700 2000 2850 2000
Wire Wire Line
	3150 2000 3250 2000
Wire Wire Line
	3250 2000 3350 2000
Wire Wire Line
	3650 2000 3700 2000
Wire Wire Line
	4350 1100 4350 2000
Wire Wire Line
	4350 2000 4350 2100
Wire Wire Line
	4350 1100 4450 1100
Wire Wire Line
	4300 2000 4350 2000
Wire Wire Line
	4350 2000 4700 2000
Text GLabel 5500 1100 2    60   Input ~ 0
NOUT
Wire Wire Line
	5200 1100 5250 1100
Wire Wire Line
	5250 1100 5500 1100
$EndSCHEMATC
