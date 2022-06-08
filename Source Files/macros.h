//===========================================================================
// File Name : macros.h 
//
// Description: contains ALL Macros 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
//MACROS FROM main.c============================================================
#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1


// MACROS FROM clocks.c=========================================================
#define MCLK_FREQ_MHZ 8                     // MCLK = 8MHz
#define CLEAR_REGISTER     (0X0000)


// Port 1 Pins==================================================================
#define RED_LED (0x01) // 0 RED LED 0
#define A1_SEEED (0x02) // 1 A1_SEEED
#define V_DETECT_L (0x04) // 2 V_DETECT_L
#define V_DETECT_R (0x08) // 3 V_DETECT_R
#define A4_SEEED (0x10) // 4 A4_SEEED
#define V_THUMB (0x20) // 5 V_THUMB
#define UCA0RXD (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80) // 7 Back Channel UCA0TXD


// Port 2 Pins==================================================================
#define P2_0 (0x01) // 0
#define P2_1 (0x02) // 1
#define P2_2 (0x04) // 2
#define SW2 (0x08) // 3 SW2
#define P2_4 (0x10) // 4
#define P2_5 (0x20) // 5
#define LFXOUT (0x40) // XOUTR
#define LFXIN (0x80) // XINR

// Port 3 Pins==================================================================
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define CHECK_BAT (0x02) // 1 CHECK_BAT
#define OA2N (0x04) // 2 Photodiode Circuit
#define OA2P (0x08) // 3 Photodiode Circuit
#define SMCLK_OUT (0x10) // 4 SMCLK
#define IR_LED (0x20) // 5 IR_LED
#define IOT_LINK (0x40) // 6 IOT_LINK
#define P3_7 (0x80) // 7 P3_7

// Port 4 Pins==================================================================
#define RESET_LCD (0x01) // 0 LCD Reset
#define SW1 (0x02) // 1 SW1
#define UCA1RXD (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20) // 5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO (0x40) // 6 UCB1SIMO
#define UCB1SOMI (0x80) // 7 UCB1SOMI

// Port 5 Pins==================================================================
#define IOT_RESET (0x01) // 
#define V_BAT (0x02) // 
#define IOT_PROGRAM_SELECT (0x04) // 
#define V_33 (0x08) //
#define IOT_PROGRAM_MODE (0x10) // 

// Port 6 Pins =================================================================
#define R_FORWARD (0x01) // 
#define L_FORWARD (0x02) // 
#define R_REVERSE (0x04) // 
#define L_REVERSE (0x08) // 
#define LCD_BACKLITE (0x10) // 
#define P6_5 (0x20) // 
#define GRN_LED (0x40) // 

// Default Settings ============================================================
#define def_out (0xFF) // default pin to out 
#define def_low (0x00) // default pin to low 

// init macros =================================================================
#define clear (0x00) // clears a variable 
#define string1 (0x00) // first line of LCD 
#define string2 (0x01) //  second line of LCD 
#define string3 (0x02) // third line of LCD 
#define string4 (0x03) // fourth line line of LCD 
#define lastchar (0x0a) // last character of string 
#define firstchar (0x00) // first character of string 
#define numChars (0x0b) // number of characters in a string on LCD 
#define numLines (0x04) // number of lines on LCD 
#define secChar (0x01) // 
#define thirdChar (0x02) // 
#define fourthChar (0x03) // 

// main macros =================================================================
#define positive (0x01) //
#define time1 250 // max value of time_sequence loop 
#define time2 200 // 
#define time3 150 // 
#define time4 100 // 
#define time5 50 // first increment of time_sequence loop 

// movement macros =============================================================
// time_sequence is 5ms 
#define turnOn 50 // waits 500 time_sequence then turns on wheels (not used) 
#define periodCircle1 1850 // Time period for going the complete circle 
#define tick 10  // amount of ticks of Time_Sequence the wheel is off, before turning the wheel on 
#define tick1 10 // same as above, except for counterclockwise circle 
#define stateCounter 1 // first state of figure8 (first counterclockwise circle) 
#define stateClockwise 2 // 
#define Corner 2 // 
#define straightLine 1 // 
#define lineTime 150 //
#define turnTime 210 // 
#define periodfig8 650 //
#define stateCounter1 3 // 
#define stateClockwise1 4 //

// switches and screen 
#define defaultButton 0 // 
#define buttonOne 1 // 
#define buttonTwo 2 //
#define buttonThree 3 //
#define buttonFour 4 //
#define buttonFive 5 //
#define buttonSix 6 // 
#define cir 2
#define fig8 3
#define tri 4 
#define fig8_2 2
#define tri_2 3
#define clockChange 1 
#define clkChng 4

// ports macros 
#define USE_GPIO (0x00)
#define USE_SMCLK (0x01)

// timers macros 
#define TB0CCR0_INTERVAL 25000
#define TB0CCR1_INTERVAL 25000
#define TB0CCR2_INTERVAL 25000 

#define debounceTime 3
#define base 0 
#define sw1Int 2
#define sw2Int 4
#define overflow 14
#define turnOnDB 10
#define turnOff 20 
#define updis 7

// more movement macros
#define firstStop 40
#define secondStop 100
#define thirdStop 140 
#define fourthStop 220
#define fifthStop 320 
#define firstForward 20
#define secondForward 120
#define firstReverse 60
#define firstCounter 260
#define firstClockW 160

// bcd macros 
#define Thousands 1000
#define Hundreds 100 
#define Tens 10 
#define Ones 1 
#define charThous '1' 
#define charZero '0' 
#define space 0x20
#define extractNum 10 
#define ASCIIOFFSET 0x30
#define numSpaces 11
#define numSpace 10 

// ADC interupt macros 
#define divide 2 
#define leftSensor 0x00
#define rightSensor 0x01  
#define thumbWheel 0x02
#define emitOff 0
#define emitOn 1

// PWM macros 
#define RIGHT_FORWARD_SPEED (TB3CCR1)
#define LEFT_FORWARD_SPEED (TB3CCR2)
#define RIGHT_REVERSE_SPEED (TB3CCR3)
#define LEFT_REVERSE_SPEED (TB3CCR4)
#define WHEEL_PERIOD 40000
#define WHEEL_OFF 0 
#define RHALF_POWER 25000
#define LHALF_POWER 20000 
#define RQUARTER_POWER 30000
#define RQUARTERR_POWER 12000
#define LSTART_POWER 16000
#define RSTART_POWER 16000
#define LQUARTERR_POWER 12000
#define RADJUST_POWER 9000
#define LADJUST_POWER 8000
#define LQUARTER_POWER 30000
#define RFIFTH_POWER 10000
#define LFIFTH_POWER 8000
#define R_ADJUST_RIGHT 10000
#define L_ADJUST_LEFT 10000
#define R_SLOW_DOWN 20000
#define L_SLOW_DOWN 20000
#define R_SLOW_DOWN1 10000
#define L_SLOW_DOWN1 10000
#define R_SLOW_DOWN2 8000
#define L_SLOW_DOWN2 8000
#define L_SLOW_DOWN3 11000
#define R_SLOW_DOWN3 13000

// black line detect and follow macros
#define border 100 
#define delayTimer 20 
#define waitToAlign 2
#define delayAdjust 20
#define circleDelay 20
#define adjustment 3
#define finish 4 
#define fifthChar 4
#define sixthChar 5
#define sevChar 6
#define eightChar 7
#define ninthChar 8
#define tenthChar 9 
#define right 1
#define left 2
#define rightFinished 3
#define leftFinished 4 
#define counterClockDelay 2

// serial communications macros
#define BEGINNING (0)
#define SMALL_RING_SIZE (16) 
#define LARGE_RING_SIZE (32) 
#define noInt (0x00) 
#define ReceiveCase (0x02)
#define TransmitCase (0x04) 
#define endCase (0x08) 
#define baud_115200_BRW (0x04)
#define baud_115200_MCTLW (0x5551) 
#define baud_460800_BRW (0x11)
#define baud_460800_MCTLW (0x4A)
#define baud_9600_BRW (52)
#define baud_9600_MCTLW (0x4911)
#define allRead (0x01) 
#define notRead (0x00) 

#define splashDisplay (0x01) 
#define FivesecDelay (100) 
#define finishSplash (0x02)
#define checkSwitches (0x03) 

#define setBaud115 (0x01) 
#define clearOneTwo (0x02)  
#define TwoSecDelay (0x03) 
#define TwoSecInterval (40)
#define OneSecInterval (20)
#define threeSecs (60)
#define TRANSMIT (0x04)
#define READ (0x05) 
#define lineFeed (0x0D) 
#define nullChar (0x00) 

#define setBaud460 (0x01) 
#define carriageReturn (0x0A)
#define testLength (12)

#define transmit0 (0)
#define transmit1 (1)
#define transmit2 (2)
#define transmit3 (3)
#define transmit4 (4)
#define transmit5 (5)
#define transmit6 (6)
#define transmit7 (7)
#define transmit8 (8)
#define transmit9 (9)
#define transmit10 (10)
 
#define msgr 2
#define msgl 1
#define msge 0

#define waitPeriod 3
#define changeBauds 4 
#define transmitmsg 5 
#define loopback 6 

// iot 
#define slower (0x02) 
#define started (0x01) 
#define wait4IOT 5 
#define wait2connect 400
#define wait4ip 60

#define iotwait 1
#define iotport 2
#define iotip 3
#define getIPadd 4

#define amtIP 10
#define amtIPlus 11
#define secondary 2
#define throwaway 3

#define offset1 1
#define offset2 2
#define offset3 3
#define offset4 4
#define offset5 5
#define offset6 6
#define offset7 7
#define offset8 8

#define digit2 1
#define digit3 2
#define digit4 3

#define clearVars 2
#define hundo 100
#define Hammy 10
#define turnRightWait 3
#define turnRightAgainWait 4
#define turnRight 5 
#define approachBoard 6
#define finishTurn 7 
#define approachBoardWait 8
#define finishApproach 9 
#define finishAgain 10 
#define readyADC 11
#define turnRightAgain 12 
#define FourSecInterval (80)
#define interceptionWait 13
#define interceptionPath 14
#define findWhitePage 15
#define project7code 16
#define end 17 
#define stop 18 

#define lenIP 10
#define border1 200 
#define var2 2 
#define var3 3 
#define cs0 0
#define cs1 1 
#define cs2 2 
#define cs3 3 
#define cs4 4 
#define cs5 5 
#define cs6 6 
#define cs7 7 
#define wait2 40 
#define wait13 13 
#define wait1andhalf 30 
#define findWHITE 100 
#define wait16 16 
#define pp5 5
#define pp6 6 
#define pp7 7 
#define intermediate 11 

