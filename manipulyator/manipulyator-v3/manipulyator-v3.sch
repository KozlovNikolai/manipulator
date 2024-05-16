EESchema Schematic File Version 4
LIBS:manipulyator-v3-cache
EELAYER 29 0
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
L manipulyator-v3-rescue:ProMicro-promicro U1
U 1 1 5CC0C931
P 4150 3650
F 0 "U1" H 4150 4793 60  0000 C CNN
F 1 "ProMicro" H 4150 4687 60  0000 C CNN
F 2 "promicro:ProMicro" H 4150 4581 60  0000 C CNN
F 3 "" H 4250 2600 60  0001 C CNN
	1    4150 3650
	1    0    0    -1  
$EndComp
$Comp
L manipulyator-v3-rescue:oled_128x64_i2c_ssd1306-Display_Graphic D3
U 1 1 5CC0E962
P 3600 2150
F 0 "D3" H 3928 2196 50  0000 L CNN
F 1 "oled_128x64_i2c_ssd1306" H 3928 2105 50  0000 L CNN
F 2 "Display:oled_128x64_i2c_ssd1306" H 3600 2450 50  0001 C CNN
F 3 "" H 3600 2450 50  0001 C CNN
	1    3600 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 5CC0F19E
P 2050 3650
F 0 "R1" H 2109 3696 50  0000 L CNN
F 1 "4k7" H 2109 3605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 2050 3650 50  0001 C CNN
F 3 "~" H 2050 3650 50  0001 C CNN
	1    2050 3650
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D1
U 1 1 5CC0F48E
P 2300 2100
F 0 "D1" H 2300 2316 50  0000 C CNN
F 1 "1N4148" H 2300 2225 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 2300 1925 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 2300 2100 50  0001 C CNN
	1    2300 2100
	-1   0    0    1   
$EndComp
$Comp
L manipulyator-v3-rescue:encoder_KY-040-Device D2
U 1 1 5CC1BD41
P 6450 3700
F 0 "D2" H 6678 3671 50  0000 L CNN
F 1 "encoder_KY-040" H 6678 3580 50  0000 L CNN
F 2 "Rotary_Encoder:encoder-KY-040" H 6450 3950 50  0001 C CNN
F 3 "" H 6450 3950 50  0001 C CNN
	1    6450 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack2_Ground_Switch J1
U 1 1 5CC1CE5B
P 1450 4050
F 0 "J1" H 1482 4475 50  0000 C CNN
F 1 "AudioJack2_Ground_Switch" H 1482 4384 50  0000 C CNN
F 2 "Connector_Audio:audio-3.5mm-5pin" H 1450 4250 50  0001 C CNN
F 3 "~" H 1450 4250 50  0001 C CNN
	1    1450 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5CC213F1
P 2500 3250
F 0 "#PWR0101" H 2500 3000 50  0001 C CNN
F 1 "GND" H 2505 3077 50  0000 C CNN
F 2 "" H 2500 3250 50  0001 C CNN
F 3 "" H 2500 3250 50  0001 C CNN
	1    2500 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3100 2500 3100
Wire Wire Line
	2500 3100 2500 3250
Wire Wire Line
	3450 3200 3450 3100
Connection ~ 3450 3100
$Comp
L power:+5V #PWR0102
U 1 1 5CC21DAA
P 5150 3200
F 0 "#PWR0102" H 5150 3050 50  0001 C CNN
F 1 "+5V" H 5165 3373 50  0000 C CNN
F 2 "" H 5150 3200 50  0001 C CNN
F 3 "" H 5150 3200 50  0001 C CNN
	1    5150 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 3200 4850 3200
$Comp
L power:GND #PWR0103
U 1 1 5CC227B5
P 5300 3000
F 0 "#PWR0103" H 5300 2750 50  0001 C CNN
F 1 "GND" H 5305 2827 50  0000 C CNN
F 2 "" H 5300 3000 50  0001 C CNN
F 3 "" H 5300 3000 50  0001 C CNN
	1    5300 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3000 4850 3000
$Comp
L power:GND #PWR0104
U 1 1 5CC231DD
P 5850 3600
F 0 "#PWR0104" H 5850 3350 50  0001 C CNN
F 1 "GND" H 5855 3427 50  0000 C CNN
F 2 "" H 5850 3600 50  0001 C CNN
F 3 "" H 5850 3600 50  0001 C CNN
	1    5850 3600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 5CC238E3
P 6000 3700
F 0 "#PWR0105" H 6000 3550 50  0001 C CNN
F 1 "+5V" H 6015 3873 50  0000 C CNN
F 2 "" H 6000 3700 50  0001 C CNN
F 3 "" H 6000 3700 50  0001 C CNN
	1    6000 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 3700 6200 3700
Wire Wire Line
	5850 3600 6200 3600
$Comp
L power:GND #PWR0106
U 1 1 5CC24191
P 1450 4500
F 0 "#PWR0106" H 1450 4250 50  0001 C CNN
F 1 "GND" H 1455 4327 50  0000 C CNN
F 2 "" H 1450 4500 50  0001 C CNN
F 3 "" H 1450 4500 50  0001 C CNN
	1    1450 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2000 3000 2000
$Comp
L Diode:1N4148 D5
U 1 1 5CC250FE
P 1900 2100
F 0 "D5" H 1900 2316 50  0000 C CNN
F 1 "1N4148" H 1900 2225 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1900 1925 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1900 2100 50  0001 C CNN
	1    1900 2100
	-1   0    0    1   
$EndComp
$Comp
L Diode:1N4148 D4
U 1 1 5CC254E1
P 1500 2100
F 0 "D4" H 1500 2316 50  0000 C CNN
F 1 "1N4148" H 1500 2225 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1500 1925 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 1500 2100 50  0001 C CNN
	1    1500 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	1650 2100 1750 2100
Wire Wire Line
	2050 2100 2150 2100
Wire Wire Line
	2450 2100 3200 2100
$Comp
L power:+5V #PWR0107
U 1 1 5CC29331
P 1300 2050
F 0 "#PWR0107" H 1300 1900 50  0001 C CNN
F 1 "+5V" H 1315 2223 50  0000 C CNN
F 2 "" H 1300 2050 50  0001 C CNN
F 3 "" H 1300 2050 50  0001 C CNN
	1    1300 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2050 1300 2100
Wire Wire Line
	1300 2100 1350 2100
$Comp
L Device:R_Small R2
U 1 1 5CC2EE99
P 2400 3650
F 0 "R2" H 2459 3696 50  0000 L CNN
F 1 "4k7" H 2459 3605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 2400 3650 50  0001 C CNN
F 3 "~" H 2400 3650 50  0001 C CNN
	1    2400 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 3750 2050 3850
Wire Wire Line
	2050 3850 1650 3850
Wire Wire Line
	1650 4050 2400 4050
Wire Wire Line
	2400 4050 2400 3750
Wire Wire Line
	2050 3550 2300 3550
$Comp
L power:+5V #PWR0108
U 1 1 5CC30E13
P 2300 3450
F 0 "#PWR0108" H 2300 3300 50  0001 C CNN
F 1 "+5V" H 2315 3623 50  0000 C CNN
F 2 "" H 2300 3450 50  0001 C CNN
F 3 "" H 2300 3450 50  0001 C CNN
	1    2300 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 3450 2300 3550
Connection ~ 2300 3550
Wire Wire Line
	2300 3550 2400 3550
Wire Wire Line
	1450 4350 1450 4500
$Comp
L power:GND #PWR0109
U 1 1 5CC35609
P 2900 1900
F 0 "#PWR0109" H 2900 1650 50  0001 C CNN
F 1 "GND" H 2905 1727 50  0000 C CNN
F 2 "" H 2900 1900 50  0001 C CNN
F 3 "" H 2900 1900 50  0001 C CNN
	1    2900 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 1900 3000 1900
Wire Wire Line
	3000 1900 3000 2000
Wire Wire Line
	3450 3700 2850 3700
Wire Wire Line
	2850 3700 2850 3850
Wire Wire Line
	2850 3850 2050 3850
Connection ~ 2050 3850
Wire Wire Line
	3450 3800 2950 3800
Wire Wire Line
	2950 3800 2950 4050
Wire Wire Line
	2950 4050 2400 4050
Connection ~ 2400 4050
Wire Wire Line
	3200 2200 2900 2200
Wire Wire Line
	2900 3400 3450 3400
Wire Wire Line
	3200 2300 3100 2300
Wire Wire Line
	3100 3300 3450 3300
$Comp
L Device:R_Small R3
U 1 1 5CC53497
P 2900 2500
F 0 "R3" H 2959 2546 50  0000 L CNN
F 1 "100" H 2959 2455 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 2900 2500 50  0001 C CNN
F 3 "~" H 2900 2500 50  0001 C CNN
	1    2900 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R4
U 1 1 5CC539AC
P 3100 2750
F 0 "R4" H 3159 2796 50  0000 L CNN
F 1 "100" H 3159 2705 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 3100 2750 50  0001 C CNN
F 3 "~" H 3100 2750 50  0001 C CNN
	1    3100 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 2200 2900 2400
Wire Wire Line
	3100 2300 3100 2650
Wire Wire Line
	2900 2600 2900 3400
Wire Wire Line
	3100 2850 3100 3300
Wire Wire Line
	6200 3800 4850 3800
Wire Wire Line
	6200 3900 4850 3900
Wire Wire Line
	6200 4000 4850 4000
$Comp
L Timer:NE555 U2
U 1 1 5CC5F0C7
P 7050 1800
F 0 "U2" H 7050 2381 50  0000 C CNN
F 1 "NE555" H 7050 2290 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 7050 1800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ne555.pdf" H 7050 1800 50  0001 C CNN
	1    7050 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5CC5F9C7
P 7050 3000
F 0 "#PWR0110" H 7050 2750 50  0001 C CNN
F 1 "GND" H 7055 2827 50  0000 C CNN
F 2 "" H 7050 3000 50  0001 C CNN
F 3 "" H 7050 3000 50  0001 C CNN
	1    7050 3000
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC547 Q1
U 1 1 5CC65898
P 6950 2650
F 0 "Q1" H 7141 2696 50  0000 L CNN
F 1 "BC547" H 7141 2605 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Wide" H 7150 2575 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 6950 2650 50  0001 L CNN
	1    6950 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 2200 7050 2450
$Comp
L Device:R_Small R5
U 1 1 5CC67BB1
P 6200 2650
F 0 "R5" H 6259 2696 50  0000 L CNN
F 1 "4k7" H 6259 2605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 6200 2650 50  0001 C CNN
F 3 "~" H 6200 2650 50  0001 C CNN
	1    6200 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R6
U 1 1 5CC68484
P 7550 1400
F 0 "R6" H 7609 1446 50  0000 L CNN
F 1 "10k" H 7609 1355 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 7550 1400 50  0001 C CNN
F 3 "~" H 7550 1400 50  0001 C CNN
	1    7550 1400
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5CC68AEB
P 7650 2350
F 0 "C2" H 7742 2396 50  0000 L CNN
F 1 "0.1" H 7742 2305 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 7650 2350 50  0001 C CNN
F 3 "~" H 7650 2350 50  0001 C CNN
	1    7650 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5CC69507
P 6500 2300
F 0 "C1" H 6592 2346 50  0000 L CNN
F 1 "0.01" H 6592 2255 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 6500 2300 50  0001 C CNN
F 3 "~" H 6500 2300 50  0001 C CNN
	1    6500 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 2000 7650 2000
Wire Wire Line
	6350 950  6350 1600
Wire Wire Line
	6350 1600 6550 1600
Wire Wire Line
	6550 2000 6450 2000
Wire Wire Line
	6450 2000 6450 1400
Wire Wire Line
	6450 1400 6650 1400
$Comp
L power:+5V #PWR0111
U 1 1 5CC6C9AD
P 6650 1250
F 0 "#PWR0111" H 6650 1100 50  0001 C CNN
F 1 "+5V" H 6665 1423 50  0000 C CNN
F 2 "" H 6650 1250 50  0001 C CNN
F 3 "" H 6650 1250 50  0001 C CNN
	1    6650 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 1250 6650 1400
Connection ~ 6650 1400
Wire Wire Line
	6650 1400 7050 1400
Wire Wire Line
	6500 2200 6500 1800
Wire Wire Line
	6500 1800 6550 1800
Wire Wire Line
	6500 2400 6500 2950
Wire Wire Line
	6500 2950 7050 2950
Wire Wire Line
	7050 2850 7050 2950
Connection ~ 7050 2950
Wire Wire Line
	7050 2950 7050 3000
Wire Wire Line
	7650 2250 7650 2000
Connection ~ 7650 2000
Wire Wire Line
	7650 2450 7650 2950
Wire Wire Line
	7650 2950 7050 2950
Wire Wire Line
	7650 2000 7900 2000
Wire Wire Line
	6350 950  8250 950 
Wire Wire Line
	7450 1400 7050 1400
Connection ~ 7050 1400
Wire Wire Line
	7650 1800 7550 1800
Wire Wire Line
	6750 2650 6300 2650
Wire Wire Line
	6100 2650 5650 2650
Wire Wire Line
	5650 2650 5650 3300
Wire Wire Line
	5650 4550 3300 4550
Wire Wire Line
	3300 4550 3300 3600
Wire Wire Line
	3300 3600 3450 3600
Wire Wire Line
	8850 2950 7650 2950
Connection ~ 7650 2950
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5CCB839E
P 2200 1200
F 0 "#FLG0101" H 2200 1275 50  0001 C CNN
F 1 "PWR_FLAG" H 2200 1373 50  0000 C CNN
F 2 "" H 2200 1200 50  0001 C CNN
F 3 "~" H 2200 1200 50  0001 C CNN
	1    2200 1200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0112
U 1 1 5CCB8D47
P 2200 1200
F 0 "#PWR0112" H 2200 1050 50  0001 C CNN
F 1 "+5V" H 2215 1373 50  0000 C CNN
F 2 "" H 2200 1200 50  0001 C CNN
F 3 "" H 2200 1200 50  0001 C CNN
	1    2200 1200
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5CCB92A5
P 2600 1200
F 0 "#FLG0102" H 2600 1275 50  0001 C CNN
F 1 "PWR_FLAG" H 2600 1373 50  0000 C CNN
F 2 "" H 2600 1200 50  0001 C CNN
F 3 "~" H 2600 1200 50  0001 C CNN
	1    2600 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5CCB980D
P 2600 1200
F 0 "#PWR0113" H 2600 950 50  0001 C CNN
F 1 "GND" H 2605 1027 50  0000 C CNN
F 2 "" H 2600 1200 50  0001 C CNN
F 3 "" H 2600 1200 50  0001 C CNN
	1    2600 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 5CCD4C30
P 7900 1800
F 0 "RV1" V 7693 1800 50  0000 C CNN
F 1 "10k" V 7784 1800 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_ACP_CA9-V10_Vertical" H 7900 1800 50  0001 C CNN
F 3 "~" H 7900 1800 50  0001 C CNN
	1    7900 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 1400 7650 1800
Wire Wire Line
	8250 950  8250 1800
Wire Wire Line
	7750 1800 7650 1800
Connection ~ 7650 1800
Wire Wire Line
	8050 1800 8250 1800
Connection ~ 8250 1800
Wire Wire Line
	8250 1800 8250 2000
Wire Wire Line
	7900 1950 7900 2000
Connection ~ 7900 2000
Wire Wire Line
	7900 2000 8250 2000
$Comp
L Connector:AudioJack2_Ground_Switch J2
U 1 1 5CC52551
P 8600 2250
F 0 "J2" H 8632 2675 50  0000 C CNN
F 1 "AudioJack2_Ground_Switch" H 8632 2584 50  0000 C CNN
F 2 "Connector_Audio:audio-3.5mm-5pin" H 8600 2450 50  0001 C CNN
F 3 "~" H 8600 2450 50  0001 C CNN
	1    8600 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 2950 8850 2550
Wire Wire Line
	8850 2550 8600 2550
Wire Wire Line
	8850 2050 8800 2050
Wire Wire Line
	8850 1600 8850 2050
Wire Wire Line
	8800 2250 8950 2250
Wire Wire Line
	8950 2250 8950 2050
Wire Wire Line
	8950 2050 8850 2050
Connection ~ 8850 2050
$Comp
L Isolator:PC817 U3
U 1 1 5CC5950B
P 8100 3700
F 0 "U3" H 8100 4025 50  0000 C CNN
F 1 "PC817" H 8100 3934 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 7900 3500 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 8100 3700 50  0001 L CNN
	1    8100 3700
	1    0    0    -1  
$EndComp
$Comp
L Isolator:PC817 U4
U 1 1 5CC59BA3
P 8100 4400
F 0 "U4" H 8100 4725 50  0000 C CNN
F 1 "PC817" H 8100 4634 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 7900 4200 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 8100 4400 50  0001 L CNN
	1    8100 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5CC5A8D3
P 7750 3850
F 0 "#PWR0114" H 7750 3600 50  0001 C CNN
F 1 "GND" H 7755 3677 50  0000 C CNN
F 2 "" H 7750 3850 50  0001 C CNN
F 3 "" H 7750 3850 50  0001 C CNN
	1    7750 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5CC5AE07
P 7750 4600
F 0 "#PWR0115" H 7750 4350 50  0001 C CNN
F 1 "GND" H 7755 4427 50  0000 C CNN
F 2 "" H 7750 4600 50  0001 C CNN
F 3 "" H 7750 4600 50  0001 C CNN
	1    7750 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 3800 7750 3800
Wire Wire Line
	7750 3800 7750 3850
Wire Wire Line
	7800 4500 7750 4500
Wire Wire Line
	7750 4500 7750 4600
$Comp
L Device:R_Small R7
U 1 1 5CC5F433
P 7450 3600
F 0 "R7" H 7509 3646 50  0000 L CNN
F 1 "510" H 7509 3555 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 7450 3600 50  0001 C CNN
F 3 "~" H 7450 3600 50  0001 C CNN
	1    7450 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R8
U 1 1 5CC5FB1E
P 7500 4300
F 0 "R8" H 7559 4346 50  0000 L CNN
F 1 "510" H 7559 4255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 7500 4300 50  0001 C CNN
F 3 "~" H 7500 4300 50  0001 C CNN
	1    7500 4300
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 3600 7550 3600
Wire Wire Line
	7800 4300 7600 4300
Wire Wire Line
	7400 4300 7300 4300
Wire Wire Line
	7300 4300 7300 3600
Wire Wire Line
	7300 3600 7350 3600
Wire Wire Line
	7300 3600 7300 3300
Wire Wire Line
	7300 3300 5650 3300
Connection ~ 7300 3600
Connection ~ 5650 3300
Wire Wire Line
	5650 3300 5650 4550
$Comp
L Device:D_Bridge_+-AA D7
U 1 1 5CC6B97D
P 8900 4500
F 0 "D7" H 9244 4546 50  0000 L CNN
F 1 "D_Bridge_+-AA" H 9244 4455 50  0000 L CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 8900 4500 50  0001 C CNN
F 3 "~" H 8900 4500 50  0001 C CNN
	1    8900 4500
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Bridge_+-AA D6
U 1 1 5CC6D35A
P 8850 3800
F 0 "D6" H 9194 3846 50  0000 L CNN
F 1 "D_Bridge_+-AA" H 9194 3755 50  0000 L CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 8850 3800 50  0001 C CNN
F 3 "~" H 8850 3800 50  0001 C CNN
	1    8850 3800
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack2_Ground_Switch J3
U 1 1 5CC6DBE2
P 10300 3700
F 0 "J3" H 10332 4125 50  0000 C CNN
F 1 "AudioJack2_Ground_Switch" H 10332 4034 50  0000 C CNN
F 2 "Connector_Audio:audio-3.5mm-5pin" H 10300 3900 50  0001 C CNN
F 3 "~" H 10300 3900 50  0001 C CNN
	1    10300 3700
	-1   0    0    -1  
$EndComp
$Comp
L Connector:AudioJack2_Ground_Switch J4
U 1 1 5CC6E1BC
P 10400 4600
F 0 "J4" H 10432 5025 50  0000 C CNN
F 1 "AudioJack2_Ground_Switch" H 10432 4934 50  0000 C CNN
F 2 "Connector_Audio:audio-3.5mm-5pin" H 10400 4800 50  0001 C CNN
F 3 "~" H 10400 4800 50  0001 C CNN
	1    10400 4600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8550 3800 8400 3800
Wire Wire Line
	9150 3800 9150 3350
Wire Wire Line
	9150 3350 8500 3350
Wire Wire Line
	8500 3350 8500 3600
Wire Wire Line
	8500 3600 8400 3600
Wire Wire Line
	8600 4500 8400 4500
Wire Wire Line
	9200 4500 9200 4150
Wire Wire Line
	9200 4150 8650 4150
Wire Wire Line
	8650 4150 8650 4300
Wire Wire Line
	8650 4300 8400 4300
Wire Wire Line
	8900 4800 9750 4800
Wire Wire Line
	9750 4800 9750 4900
Wire Wire Line
	9750 4900 10400 4900
Wire Wire Line
	8850 4100 10300 4100
Wire Wire Line
	10300 4100 10300 4000
Wire Wire Line
	8850 3500 9800 3500
Wire Wire Line
	9800 3500 9800 3700
Wire Wire Line
	9800 3700 10100 3700
Wire Wire Line
	8900 4200 9700 4200
Wire Wire Line
	9700 4200 9700 4600
Wire Wire Line
	9700 4600 10200 4600
$Comp
L Device:CP_Small C3
U 1 1 5CE6D594
P 8650 1600
F 0 "C3" V 8875 1600 50  0000 C CNN
F 1 "CP_Small" V 8784 1600 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D7.5mm_P2.50mm" H 8650 1600 50  0001 C CNN
F 3 "~" H 8650 1600 50  0001 C CNN
	1    8650 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8750 1600 8850 1600
Wire Wire Line
	8550 1600 7550 1600
$EndSCHEMATC