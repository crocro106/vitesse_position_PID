EESchema Schematic File Version 4
EELAYER 30 0
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
L XG_Lib:Cy8ckit-059 U1
U 1 1 5FF9ED42
P 2450 7125
F 0 "U1" H 3000 10150 60  0000 C CNN
F 1 "Cy8ckit-059" H 2475 9275 60  0000 C CNN
F 2 "XG_PCB_Lib:Cy8ckit-059" H 2550 10175 60  0001 C CNN
F 3 "" H 2550 10175 60  0001 C CNN
	1    2450 7125
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:L298HN U3
U 1 1 5FFAD193
P 7975 4925
F 0 "U3" H 8450 5575 50  0000 C CNN
F 1 "L298HN" H 7975 4925 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-15_P2.54x2.54mm_StaggerOdd_Lead4.58mm_Vertical" H 8025 4275 50  0001 L CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000240.pdf" H 8125 5175 50  0001 C CNN
	1    7975 4925
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J2
U 1 1 5FFADDA1
P 5275 4675
F 0 "J2" H 5355 4717 50  0000 L CNN
F 1 "Conn_01x05" H 5355 4626 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 5275 4675 50  0001 C CNN
F 3 "~" H 5275 4675 50  0001 C CNN
F 4 "Codeur" H 5355 4626 50  0000 L CNN "Nom"
	1    5275 4675
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5FFAEB5F
P 6100 7150
F 0 "C2" H 6215 7196 50  0000 L CNN
F 1 "C" H 6215 7105 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W3.5mm_P2.50mm_P5.00mm" H 6138 7000 50  0001 C CNN
F 3 "~" H 6100 7150 50  0001 C CNN
	1    6100 7150
	1    0    0    -1  
$EndComp
$Comp
L Diode:MBR340 D1
U 1 1 5FFAF69D
P 9125 4550
F 0 "D1" V 9125 4300 50  0000 L CNN
F 1 "MBR360" V 9200 4200 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AD_P12.70mm_Horizontal" H 9125 4550 50  0001 C CNN
F 3 "~" H 9125 4550 50  0001 C CNN
	1    9125 4550
	0    1    1    0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J10
U 1 1 5FFB0F58
P 10250 4725
F 0 "J10" H 10330 4717 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 10330 4626 50  0001 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 10250 4725 50  0001 C CNN
F 3 "~" H 10250 4725 50  0001 C CNN
F 4 "Moteur1" H 10330 4626 50  0000 L CNN "Nom"
	1    10250 4725
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR02
U 1 1 5FFB9307
P 1275 5125
F 0 "#PWR02" H 1275 4925 50  0001 C CNN
F 1 "GNDPWR" V 1279 5016 50  0001 R CNN
F 2 "" H 1275 5075 50  0001 C CNN
F 3 "" H 1275 5075 50  0001 C CNN
	1    1275 5125
	0    1    1    0   
$EndComp
$Comp
L power:GNDPWR #PWR09
U 1 1 5FFBA1BA
P 4650 3500
F 0 "#PWR09" H 4650 3300 50  0001 C CNN
F 1 "GNDPWR" V 4654 3391 50  0001 R CNN
F 2 "" H 4650 3450 50  0001 C CNN
F 3 "" H 4650 3450 50  0001 C CNN
	1    4650 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR07
U 1 1 5FFBBA6D
P 3550 5225
F 0 "#PWR07" H 3550 5025 50  0001 C CNN
F 1 "GNDPWR" V 3554 5116 50  0001 R CNN
F 2 "" H 3550 5175 50  0001 C CNN
F 3 "" H 3550 5175 50  0001 C CNN
	1    3550 5225
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3550 5225 3300 5225
Wire Wire Line
	5150 7225 5150 7325
$Comp
L power:GNDPWR #PWR012
U 1 1 5FFC043C
P 5150 7325
F 0 "#PWR012" H 5150 7125 50  0001 C CNN
F 1 "GNDPWR" V 5154 7216 50  0001 R CNN
F 2 "" H 5150 7275 50  0001 C CNN
F 3 "" H 5150 7275 50  0001 C CNN
	1    5150 7325
	-1   0    0    -1  
$EndComp
Text Label 5300 7025 2    50   ~ 0
Vmot
Wire Wire Line
	5075 4575 4850 4575
Text Label 4875 4575 0    50   ~ 0
5_V
Wire Wire Line
	7975 4225 7975 4100
Text Label 7850 4100 0    50   ~ 0
5_V
Wire Wire Line
	7975 4100 7825 4100
$Comp
L power:GNDPWR #PWR010
U 1 1 5FFC6A32
P 4900 4875
F 0 "#PWR010" H 4900 4675 50  0001 C CNN
F 1 "GNDPWR" V 4904 4766 50  0001 R CNN
F 2 "" H 4900 4825 50  0001 C CNN
F 3 "" H 4900 4825 50  0001 C CNN
	1    4900 4875
	0    1    1    0   
$EndComp
Wire Wire Line
	5075 4875 4900 4875
Wire Wire Line
	9125 5200 9125 5225
Wire Wire Line
	9125 5225 9250 5225
Wire Wire Line
	9375 5225 9375 5200
Wire Wire Line
	9125 4900 9125 4725
Wire Wire Line
	9375 4700 9375 4825
Wire Wire Line
	9375 4400 9375 4350
Wire Wire Line
	9375 4350 9125 4350
Wire Wire Line
	9125 4350 9125 4400
Wire Wire Line
	8575 4725 9125 4725
Connection ~ 9125 4725
Wire Wire Line
	9125 4725 9125 4700
Wire Wire Line
	8575 4825 9375 4825
Connection ~ 9375 4825
Wire Wire Line
	9375 4825 9375 4900
$Comp
L power:GNDPWR #PWR019
U 1 1 5FFD731A
P 7975 5725
F 0 "#PWR019" H 7975 5525 50  0001 C CNN
F 1 "GNDPWR" V 7979 5616 50  0001 R CNN
F 2 "" H 7975 5675 50  0001 C CNN
F 3 "" H 7975 5675 50  0001 C CNN
	1    7975 5725
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR018
U 1 1 5FFD819D
P 7725 5725
F 0 "#PWR018" H 7725 5525 50  0001 C CNN
F 1 "GNDPWR" V 7729 5616 50  0001 R CNN
F 2 "" H 7725 5675 50  0001 C CNN
F 3 "" H 7725 5675 50  0001 C CNN
	1    7725 5725
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR020
U 1 1 5FFD900A
P 9250 5250
F 0 "#PWR020" H 9250 5050 50  0001 C CNN
F 1 "GNDPWR" V 9254 5141 50  0001 R CNN
F 2 "" H 9250 5200 50  0001 C CNN
F 3 "" H 9250 5200 50  0001 C CNN
	1    9250 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7675 5625 7675 5675
Wire Wire Line
	7775 5675 7775 5625
Wire Wire Line
	7725 5725 7725 5675
Wire Wire Line
	7675 5675 7725 5675
Connection ~ 7725 5675
Wire Wire Line
	7725 5675 7775 5675
Wire Wire Line
	7975 5725 7975 5625
Wire Wire Line
	9250 5250 9250 5225
Connection ~ 9250 5225
Wire Wire Line
	9250 5225 9375 5225
Wire Wire Line
	8075 4225 8075 4100
Wire Wire Line
	8075 4100 8275 4100
Text Label 8100 4100 0    50   ~ 0
Vmot
Text Label 9175 4350 0    50   ~ 0
Vmot
Wire Wire Line
	10050 4725 9125 4725
Wire Wire Line
	5075 4475 4850 4475
Text Label 4875 4475 0    50   ~ 0
CH_A
Wire Wire Line
	5075 4675 4850 4675
Text Label 4875 4675 0    50   ~ 0
CH_B
Wire Wire Line
	5075 4775 4850 4775
Text Label 4875 4775 0    50   ~ 0
CH_I
Wire Wire Line
	5100 5475 5100 5700
Wire Wire Line
	5300 5475 5300 5700
Wire Wire Line
	5500 5475 5500 5700
Wire Wire Line
	4175 5475 4175 5700
Wire Wire Line
	4375 5475 4375 5700
Wire Wire Line
	4575 5475 4575 5700
Text Label 5300 5675 1    50   ~ 0
PwmA
Text Label 5900 5675 1    50   ~ 0
PwmB
Text Label 5500 5675 1    50   ~ 0
Enable
Text Label 4175 5675 1    50   ~ 0
CH_A
Text Label 4375 5675 1    50   ~ 0
CH_B
Text Label 4575 5675 1    50   ~ 0
CH_I
$Comp
L Device:C C4
U 1 1 6000F0FE
P 6675 7150
F 0 "C4" H 6790 7196 50  0000 L CNN
F 1 "C" H 6790 7105 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W3.5mm_P2.50mm_P5.00mm" H 6713 7000 50  0001 C CNN
F 3 "~" H 6675 7150 50  0001 C CNN
	1    6675 7150
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR017
U 1 1 6000FF06
P 6675 7375
F 0 "#PWR017" H 6675 7175 50  0001 C CNN
F 1 "GNDPWR" V 6679 7266 50  0001 R CNN
F 2 "" H 6675 7325 50  0001 C CNN
F 3 "" H 6675 7325 50  0001 C CNN
	1    6675 7375
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR014
U 1 1 600105C5
P 6100 7375
F 0 "#PWR014" H 6100 7175 50  0001 C CNN
F 1 "GNDPWR" V 6104 7266 50  0001 R CNN
F 2 "" H 6100 7325 50  0001 C CNN
F 3 "" H 6100 7325 50  0001 C CNN
	1    6100 7375
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 60010A41
P 5775 7150
F 0 "C1" H 5890 7196 50  0000 L CNN
F 1 "C" H 5890 7105 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W3.5mm_P2.50mm_P5.00mm" H 5813 7000 50  0001 C CNN
F 3 "~" H 5775 7150 50  0001 C CNN
	1    5775 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 60010DD4
P 6425 7150
F 0 "C3" H 6540 7196 50  0000 L CNN
F 1 "C" H 6540 7105 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W3.5mm_P2.50mm_P5.00mm" H 6463 7000 50  0001 C CNN
F 3 "~" H 6425 7150 50  0001 C CNN
	1    6425 7150
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR015
U 1 1 60011342
P 6425 7375
F 0 "#PWR015" H 6425 7175 50  0001 C CNN
F 1 "GNDPWR" V 6429 7266 50  0001 R CNN
F 2 "" H 6425 7325 50  0001 C CNN
F 3 "" H 6425 7325 50  0001 C CNN
	1    6425 7375
	1    0    0    -1  
$EndComp
$Comp
L power:GNDPWR #PWR013
U 1 1 600117BF
P 5775 7375
F 0 "#PWR013" H 5775 7175 50  0001 C CNN
F 1 "GNDPWR" V 5779 7266 50  0001 R CNN
F 2 "" H 5775 7325 50  0001 C CNN
F 3 "" H 5775 7325 50  0001 C CNN
	1    5775 7375
	1    0    0    -1  
$EndComp
Wire Wire Line
	6675 7300 6675 7375
Wire Wire Line
	6425 7300 6425 7375
Wire Wire Line
	6100 7300 6100 7375
Wire Wire Line
	5775 7300 5775 7375
Wire Wire Line
	5775 7000 5775 6825
Wire Wire Line
	6100 7000 6100 6825
Wire Wire Line
	6425 7000 6425 6825
Wire Wire Line
	6675 7000 6675 6825
Text Label 5775 6975 1    50   ~ 0
5_V
Text Label 6100 6975 1    50   ~ 0
5_V
Text Label 6425 6975 1    50   ~ 0
Vmot
Text Label 6675 6975 1    50   ~ 0
Vmot
Wire Wire Line
	7375 4425 6925 4425
Wire Wire Line
	7375 4525 6925 4525
Wire Wire Line
	7375 4625 6925 4625
Text Label 6975 4425 0    50   ~ 0
PwmA
Text Label 6975 4525 0    50   ~ 0
PwmB
Text Label 6975 4625 0    50   ~ 0
Enable
Text Label 4750 3450 1    50   ~ 0
5_V
Text Label 3375 5525 0    50   ~ 0
Enable
Text Label 3375 5725 0    50   ~ 0
PwmA
Text Label 3375 5625 0    50   ~ 0
PwmB
$Comp
L Driver_Motor:L293D U5
U 1 1 60096F6D
P 9800 2125
F 0 "U5" H 10150 3075 50  0000 C CNN
F 1 "L293D" H 10025 2325 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 10050 1375 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/l293.pdf" H 9500 2825 50  0001 C CNN
	1    9800 2125
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 2925 9600 3000
Wire Wire Line
	9600 3000 9700 3000
Wire Wire Line
	10000 3000 10000 2925
Wire Wire Line
	9900 2925 9900 3000
Connection ~ 9900 3000
Wire Wire Line
	9900 3000 10000 3000
Wire Wire Line
	9700 2925 9700 3000
Connection ~ 9700 3000
Wire Wire Line
	9700 3000 9800 3000
$Comp
L power:GNDPWR #PWR022
U 1 1 600A50C4
P 9800 3075
F 0 "#PWR022" H 9800 2875 50  0001 C CNN
F 1 "GNDPWR" V 9804 2966 50  0001 R CNN
F 2 "" H 9800 3025 50  0001 C CNN
F 3 "" H 9800 3025 50  0001 C CNN
	1    9800 3075
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 3075 9800 3000
Connection ~ 9800 3000
Wire Wire Line
	9800 3000 9900 3000
Wire Wire Line
	9700 1125 9700 1050
Wire Wire Line
	9700 1050 9450 1050
Text Label 9500 1050 0    50   ~ 0
5_V
Wire Wire Line
	9900 1125 9900 1050
Wire Wire Line
	9900 1050 10200 1050
Text Label 9975 1050 0    50   ~ 0
Vmot
Wire Wire Line
	10300 1525 10675 1525
Wire Wire Line
	10300 1725 10675 1725
Text Label 10450 1525 0    50   ~ 0
M1+
Text Label 10450 1725 0    50   ~ 0
M1-
Text Label 9825 4725 0    50   ~ 0
M1+
Text Label 9825 4825 0    50   ~ 0
M1-
Wire Wire Line
	9300 1925 8825 1925
Wire Wire Line
	9300 1725 8825 1725
Wire Wire Line
	9300 1525 8825 1525
Text Label 8925 1925 0    50   ~ 0
Enable
Text Label 8925 1525 0    50   ~ 0
PwmA
Text Label 8925 1725 0    50   ~ 0
PwmB
$Comp
L XG_Lib:ev-vnh7040ay U4
U 1 1 600FA611
P 6500 2150
F 0 "U4" H 6750 2625 50  0000 C CNN
F 1 "ev-vnh7040ay" H 6100 1800 50  0000 C CNN
F 2 "XG_PCB_Lib:ev-vnh7040ay" H 6500 2150 50  0001 C CNN
F 3 "" H 6500 2150 50  0001 C CNN
	1    6500 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2650 6700 2825
Wire Wire Line
	6700 2825 6600 2825
Wire Wire Line
	6500 2825 6500 2650
Wire Wire Line
	6600 2650 6600 2825
Connection ~ 6600 2825
Wire Wire Line
	6600 2825 6500 2825
Wire Wire Line
	6300 1550 6300 1425
Wire Wire Line
	6300 1425 6500 1425
Wire Wire Line
	6500 1425 6500 1550
Text Label 6325 1425 0    50   ~ 0
Vmot
$Comp
L power:GNDPWR #PWR016
U 1 1 6010DE25
P 6600 2925
F 0 "#PWR016" H 6600 2725 50  0001 C CNN
F 1 "GNDPWR" V 6604 2816 50  0001 R CNN
F 2 "" H 6600 2875 50  0001 C CNN
F 3 "" H 6600 2875 50  0001 C CNN
	1    6600 2925
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2925 6600 2825
Wire Wire Line
	7000 1950 7325 1950
Wire Wire Line
	7325 1850 7000 1850
Text Label 7150 1850 0    50   ~ 0
M1+
Text Label 7150 1950 0    50   ~ 0
M1-
Wire Wire Line
	5800 1850 5500 1850
Text Label 5550 1850 0    50   ~ 0
PwmA
Wire Wire Line
	5800 1950 5750 1950
Wire Wire Line
	5800 2250 5500 2250
Text Label 5550 2250 0    50   ~ 0
Enable
Text Label 5550 1950 0    50   ~ 0
INA
Text Label 5550 2050 0    50   ~ 0
INB
Wire Wire Line
	5500 2050 5800 2050
Wire Wire Line
	5800 2150 5750 2150
Wire Wire Line
	5750 2150 5750 1950
Connection ~ 5750 1950
Wire Wire Line
	5750 1950 5500 1950
Text Label 3375 5425 0    50   ~ 0
INA
Text Label 3375 5325 0    50   ~ 0
INB
Text Label 3400 7625 0    50   ~ 0
I_Sense
Wire Wire Line
	3300 7625 3700 7625
Wire Wire Line
	3300 5725 3650 5725
Wire Wire Line
	3300 5625 3650 5625
Wire Wire Line
	3300 5525 3650 5525
Wire Wire Line
	3300 5425 3650 5425
Wire Wire Line
	3300 5325 3650 5325
NoConn ~ 3300 5125
NoConn ~ 3300 5925
NoConn ~ 3300 6025
NoConn ~ 3300 6125
NoConn ~ 3300 6225
NoConn ~ 3300 6625
NoConn ~ 3300 6725
NoConn ~ 3300 6825
NoConn ~ 3300 6925
NoConn ~ 3300 7025
NoConn ~ 3300 7425
NoConn ~ 3300 7525
NoConn ~ 1600 7425
NoConn ~ 1600 7025
NoConn ~ 1600 6925
NoConn ~ 1600 6825
NoConn ~ 1600 5225
NoConn ~ 1600 5325
NoConn ~ 1600 5425
NoConn ~ 1600 5525
NoConn ~ 1600 5625
NoConn ~ 1600 5725
NoConn ~ 1600 5825
NoConn ~ 1600 5925
NoConn ~ 1600 6025
NoConn ~ 1600 6125
NoConn ~ 1600 6225
NoConn ~ 1600 6325
NoConn ~ 1600 6425
NoConn ~ 3300 5825
Wire Notes Line
	5175 4000 5175 475 
Wire Notes Line
	5450 6550 5450 7775
Text Notes 6025 6725 0    50   ~ 0
Capacité de \nDécouplage
Wire Notes Line
	3725 6550 3725 7800
Wire Notes Line
	3725 6550 6925 6550
Text Notes 4150 7675 0    50   ~ 0
     Alimentation\n\nMax 38V pour VNH7040
Wire Notes Line
	4075 4000 4075 6550
Wire Notes Line
	725  4000 6325 4000
Wire Notes Line
	4075 5100 6325 5100
Wire Notes Line
	6325 3525 6325 6550
Wire Notes Line
	8175 3525 8175 475 
Text Notes 4825 4225 0    50   ~ 0
Connecteur Codeur
Text Notes 4900 6525 0    50   ~ 0
   Connecteur \nPrise de mesure
Text Notes 6700 6225 0    59   ~ 12
Montage avec Driver\n      L298HN\n    46V - 4 A
Text Notes 6775 1025 0    59   ~ 12
Montage avec Driver\n      VNH7040\n    40V - 35 A
Text Notes 8425 1025 0    59   ~ 12
Montage avec Driver\n      L293D\n    36V - 0,6 A
Wire Wire Line
	4750 3175 4750 3550
Wire Wire Line
	4650 3500 4650 3175
Wire Wire Line
	1275 5125 1600 5125
$Comp
L XG_Lib:Cy8ckit-043 U2
U 1 1 5FFCB581
P 3950 2325
F 0 "U2" H 3950 5612 60  0000 C CNN
F 1 "Cy8ckit-043" H 3950 5506 60  0000 C CNN
F 2 "XG_PCB_Lib:Cy8ckit-043" H 4050 5375 60  0001 C CNN
F 3 "" H 4050 5375 60  0001 C CNN
	1    3950 2325
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDPWR #PWR05
U 1 1 6001F8C0
P 1950 3475
F 0 "#PWR05" H 1950 3275 50  0001 C CNN
F 1 "GNDPWR" V 1954 3366 50  0001 R CNN
F 2 "" H 1950 3425 50  0001 C CNN
F 3 "" H 1950 3425 50  0001 C CNN
	1    1950 3475
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 3175 1950 3475
$Comp
L power:GNDPWR #PWR04
U 1 1 60034B62
P 1700 3475
F 0 "#PWR04" H 1700 3275 50  0001 C CNN
F 1 "GNDPWR" V 1704 3366 50  0001 R CNN
F 2 "" H 1700 3425 50  0001 C CNN
F 3 "" H 1700 3425 50  0001 C CNN
	1    1700 3475
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 3175 1700 3475
$Comp
L power:GNDPWR #PWR03
U 1 1 60052C03
P 1600 1100
F 0 "#PWR03" H 1600 900 50  0001 C CNN
F 1 "GNDPWR" V 1604 991 50  0001 R CNN
F 2 "" H 1600 1050 50  0001 C CNN
F 3 "" H 1600 1050 50  0001 C CNN
	1    1600 1100
	-1   0    0    1   
$EndComp
Text Label 1700 1225 3    50   ~ 0
5_V
Wire Wire Line
	1600 1475 1600 1100
Wire Wire Line
	1700 1100 1700 1475
$Comp
L power:GNDPWR #PWR08
U 1 1 6006ACA9
P 3675 4775
F 0 "#PWR08" H 3675 4575 50  0001 C CNN
F 1 "GNDPWR" V 3679 4666 50  0001 R CNN
F 2 "" H 3675 4725 50  0001 C CNN
F 3 "" H 3675 4725 50  0001 C CNN
	1    3675 4775
	0    -1   -1   0   
$EndComp
Text Label 3550 4875 2    50   ~ 0
5_V
Wire Wire Line
	3300 4775 3675 4775
Wire Wire Line
	3675 4875 3300 4875
NoConn ~ 1600 7525
NoConn ~ 1600 7625
$Comp
L power:GNDPWR #PWR01
U 1 1 6008A8E1
P 1275 4875
F 0 "#PWR01" H 1275 4675 50  0001 C CNN
F 1 "GNDPWR" V 1279 4766 50  0001 R CNN
F 2 "" H 1275 4825 50  0001 C CNN
F 3 "" H 1275 4825 50  0001 C CNN
	1    1275 4875
	0    1    1    0   
$EndComp
Wire Wire Line
	1275 4875 1600 4875
NoConn ~ 1600 4275
NoConn ~ 1600 4375
NoConn ~ 1600 4475
NoConn ~ 1600 4575
NoConn ~ 1600 4675
NoConn ~ 1600 4775
NoConn ~ 3300 4675
NoConn ~ 3300 4575
NoConn ~ 3300 4475
NoConn ~ 3300 4375
NoConn ~ 3300 4275
NoConn ~ 1100 3175
NoConn ~ 1200 3175
NoConn ~ 1300 3175
NoConn ~ 1400 3175
NoConn ~ 1500 3175
NoConn ~ 1600 3175
NoConn ~ 1100 1475
NoConn ~ 1200 1475
NoConn ~ 1300 1475
NoConn ~ 1400 1475
NoConn ~ 1500 1475
Wire Notes Line
	5175 3525 11225 3525
NoConn ~ 2050 3175
NoConn ~ 2150 3175
NoConn ~ 2250 3175
NoConn ~ 2350 3175
NoConn ~ 2450 3175
NoConn ~ 2550 3175
NoConn ~ 2650 3175
NoConn ~ 2750 3175
NoConn ~ 2850 3175
NoConn ~ 2950 3175
NoConn ~ 3050 3175
NoConn ~ 3150 3175
NoConn ~ 3250 3175
NoConn ~ 3350 3175
NoConn ~ 3450 3175
NoConn ~ 3550 3175
NoConn ~ 3650 3175
NoConn ~ 3750 3175
NoConn ~ 3850 3175
NoConn ~ 3950 3175
NoConn ~ 4050 3175
NoConn ~ 4150 3175
NoConn ~ 4250 3175
NoConn ~ 4350 3175
NoConn ~ 4450 3175
NoConn ~ 4550 3175
Text Label 3400 7225 0    50   ~ 0
CH_A
Text Label 3400 7125 0    50   ~ 0
CH_B
Text Label 3400 7325 0    50   ~ 0
CH_I
Wire Wire Line
	3675 7325 3300 7325
Wire Wire Line
	3675 7225 3300 7225
Wire Wire Line
	3675 7125 3300 7125
NoConn ~ 1600 6525
NoConn ~ 1600 6625
NoConn ~ 1600 6725
NoConn ~ 1600 7125
NoConn ~ 1600 7225
NoConn ~ 1600 7325
$Comp
L power:GNDPWR #PWR06
U 1 1 60274C61
P 2050 1225
F 0 "#PWR06" H 2050 1025 50  0001 C CNN
F 1 "GNDPWR" V 2054 1116 50  0001 R CNN
F 2 "" H 2050 1175 50  0001 C CNN
F 3 "" H 2050 1175 50  0001 C CNN
	1    2050 1225
	-1   0    0    1   
$EndComp
Wire Wire Line
	2050 1225 2050 1475
Text Label 2350 1400 1    50   ~ 0
Enable
Text Label 2550 1400 1    50   ~ 0
PwmA
Text Label 2450 1400 1    50   ~ 0
PwmB
Text Label 2250 1400 1    50   ~ 0
INA
Text Label 2150 1400 1    50   ~ 0
INB
Wire Wire Line
	2550 1475 2550 1125
Wire Wire Line
	2450 1475 2450 1125
Wire Wire Line
	2350 1475 2350 1125
Wire Wire Line
	2250 1475 2250 1125
Wire Wire Line
	2150 1475 2150 1125
Text Label 3250 1375 1    50   ~ 0
Pwm1_A
Text Label 3350 1375 1    50   ~ 0
Pwm1_B
Text Label 3150 1375 1    50   ~ 0
Enable1
Wire Wire Line
	3350 1100 3350 1475
Wire Wire Line
	3250 1100 3250 1475
Wire Wire Line
	3150 1100 3150 1475
Text Label 4050 1375 1    50   ~ 0
CH_A
Text Label 3950 1375 1    50   ~ 0
CH_B
Text Label 4150 1375 1    50   ~ 0
CH_I
Wire Wire Line
	4150 1100 4150 1475
Wire Wire Line
	4050 1100 4050 1475
Wire Wire Line
	3950 1100 3950 1475
Text Label 4450 1375 1    50   ~ 0
I_Sense
Wire Wire Line
	4450 1475 4450 1075
NoConn ~ 1950 1475
NoConn ~ 2650 1475
NoConn ~ 2750 1475
NoConn ~ 2850 1475
NoConn ~ 2950 1475
NoConn ~ 3050 1475
NoConn ~ 3450 1475
NoConn ~ 3550 1475
NoConn ~ 3650 1475
NoConn ~ 3750 1475
NoConn ~ 3850 1475
NoConn ~ 4250 1475
NoConn ~ 4350 1475
NoConn ~ 4550 1475
NoConn ~ 4650 1475
NoConn ~ 4750 1475
$Comp
L Diode:MBR340 D3
U 1 1 6031D5C3
P 9375 4550
F 0 "D3" V 9400 4725 50  0000 L CNN
F 1 "MBR360" V 9475 4600 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AD_P12.70mm_Horizontal" H 9375 4550 50  0001 C CNN
F 3 "~" H 9375 4550 50  0001 C CNN
	1    9375 4550
	0    1    1    0   
$EndComp
$Comp
L Diode:MBR340 D4
U 1 1 6031E5D9
P 9375 5050
F 0 "D4" V 9400 5225 50  0000 L CNN
F 1 "MBR360" V 9475 5100 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AD_P12.70mm_Horizontal" H 9375 5050 50  0001 C CNN
F 3 "~" H 9375 5050 50  0001 C CNN
	1    9375 5050
	0    1    1    0   
$EndComp
$Comp
L Diode:MBR340 D2
U 1 1 6031ED7D
P 9125 5050
F 0 "D2" V 9125 4800 50  0000 L CNN
F 1 "MBR360" V 9200 4700 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AD_P12.70mm_Horizontal" H 9125 5050 50  0001 C CNN
F 3 "~" H 9125 5050 50  0001 C CNN
	1    9125 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	7000 2150 7325 2150
Text Label 7050 2150 0    50   ~ 0
I_Sense
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 60360B23
P 5325 7025
F 0 "#FLG0101" H 5325 7100 50  0001 C CNN
F 1 "PWR_FLAG" H 5325 7198 50  0000 C CNN
F 2 "" H 5325 7025 50  0001 C CNN
F 3 "~" H 5325 7025 50  0001 C CNN
	1    5325 7025
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J4
U 1 1 6009C9F0
P 4475 5275
F 0 "J4" V 4575 5175 50  0000 L CNN
F 1 "Conn_01x08" H 4555 5176 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 4475 5275 50  0001 C CNN
F 3 "~" H 4475 5275 50  0001 C CNN
F 4 "Mesure Position" V 3900 4975 50  0000 L CNN "Nom"
	1    4475 5275
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDPWR #PWR0101
U 1 1 600AEDEC
P 4875 5700
F 0 "#PWR0101" H 4875 5500 50  0001 C CNN
F 1 "GNDPWR" V 4879 5591 50  0001 R CNN
F 2 "" H 4875 5650 50  0001 C CNN
F 3 "" H 4875 5650 50  0001 C CNN
	1    4875 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4875 5700 4875 5525
NoConn ~ 8575 5025
NoConn ~ 8575 5125
NoConn ~ 7375 4825
NoConn ~ 7375 4925
NoConn ~ 7375 5025
NoConn ~ 3300 6325
NoConn ~ 3300 6425
NoConn ~ 3300 6525
NoConn ~ 9300 2125
NoConn ~ 9300 2325
NoConn ~ 9300 2525
NoConn ~ 10300 2125
NoConn ~ 10300 2325
Wire Wire Line
	9375 4825 10050 4825
$Comp
L Connector_Generic:Conn_01x12 J3
U 1 1 6014C465
P 5600 5275
F 0 "J3" H 5680 5267 50  0000 L CNN
F 1 "Conn_01x012" H 5680 5176 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x12_P2.54mm_Vertical" H 5600 5275 50  0001 C CNN
F 3 "~" H 5600 5275 50  0001 C CNN
F 4 "Mesure PWM" V 5025 5025 50  0000 L CNN "Nom"
	1    5600 5275
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDPWR #PWR0102
U 1 1 6014D779
P 6200 5650
F 0 "#PWR0102" H 6200 5450 50  0001 C CNN
F 1 "GNDPWR" V 6204 5541 50  0001 R CNN
F 2 "" H 6200 5600 50  0001 C CNN
F 3 "" H 6200 5600 50  0001 C CNN
	1    6200 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 5475 6200 5525
Wire Wire Line
	5700 5475 5700 5700
Wire Wire Line
	5900 5700 5900 5475
Text Label 5700 5675 1    50   ~ 0
INB
Text Label 5100 5675 1    50   ~ 0
INA
Wire Wire Line
	4775 5475 4775 5525
Wire Wire Line
	4775 5525 4875 5525
Connection ~ 4875 5525
Wire Wire Line
	4875 5525 4875 5475
NoConn ~ 4675 5475
NoConn ~ 4475 5475
NoConn ~ 4275 5475
Wire Wire Line
	6100 5475 6100 5525
Wire Wire Line
	6100 5525 6200 5525
Connection ~ 6200 5525
Wire Wire Line
	6200 5525 6200 5650
NoConn ~ 5200 5475
NoConn ~ 5400 5475
NoConn ~ 5600 5475
NoConn ~ 6000 5475
NoConn ~ 5800 5475
$Comp
L Diode:MBR340 D5
U 1 1 6003CEC7
P 4775 7025
F 0 "D5" H 4725 6925 50  0000 L CNN
F 1 "MBR360" H 4600 7125 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AD_P12.70mm_Horizontal" H 4775 7025 50  0001 C CNN
F 3 "~" H 4775 7025 50  0001 C CNN
	1    4775 7025
	-1   0    0    1   
$EndComp
Wire Wire Line
	4925 7025 5325 7025
$Comp
L Connector_Generic:Conn_01x01 J1P1
U 1 1 601AAA9E
P 4000 7025
F 0 "J1P1" H 4000 6925 50  0000 C CNN
F 1 "Conn_01x01" H 3918 6891 50  0001 C CNN
F 2 "Connector:Banana_Jack_1Pin" H 4000 7025 50  0001 C CNN
F 3 "~" H 4000 7025 50  0001 C CNN
	1    4000 7025
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1N1
U 1 1 601AC22C
P 4000 7225
F 0 "J1N1" H 4000 7325 50  0000 C CNN
F 1 "Conn_01x01" H 3918 7091 50  0001 C CNN
F 2 "Connector:Banana_Jack_1Pin" H 4000 7225 50  0001 C CNN
F 3 "~" H 4000 7225 50  0001 C CNN
	1    4000 7225
	-1   0    0    1   
$EndComp
Wire Wire Line
	4200 7225 5150 7225
Wire Wire Line
	4200 7025 4625 7025
$EndSCHEMATC