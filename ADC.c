
//===========================================================================
// File Name : ADC.c
//
// Description: This file contains initialization of ports for ADC use as 
// well as functions required to display ADC values and a hex to bcd function
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h" 

//      GLOBALS 
char thousands = clear; 
char hundreds = clear;
char tens = clear; 
char ones = clear; 
extern char display_line[numLines][numChars];
extern volatile unsigned char display_changed;
int i; 
char string[numSpaces];

//===========================================================================
// Function Name : HEXtoBCD 
// Arguments: int hexval 
// Return: None 
// Called From: Interrupts_ADC 
//
// Globals: ones, tens, hundreds, thousands 
// Locals: none 
// 
// Description: converts the hexadecimal value received from the photoresistors
// to a decimal value. It's commented out here because it's not needed. 
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================



/*void HEXtoBCD(int hexval){
  
  if(hexval >= Thousands){
    thousands = charThous;
  }else{
    thousands = charZero; 
  }
    ones = hexval % extractNum; 
    hexval = hexval / extractNum; 
    tens = hexval % extractNum; 
    hexval = hexval / extractNum; 
    hundreds = hexval % extractNum;
    
 
    for(i=clear;i<numSpace;i++){
      string[i] = space; 
    }
  string[firstchar] = thousands; 
  string[secChar] = hundreds | ASCIIOFFSET ;  
  string[thirdChar] = tens | ASCIIOFFSET; 
  string[fourthChar] = ones | ASCIIOFFSET ; 
  
}*/

//===========================================================================
// Function Name : adc_line
// Arguments: char* bcdVal
// Return: None 
// Called From: Interrupts_ADC 
//
// Globals: none  
// Locals: none 
// 
// Description: Displays the converted value to the proper display line 
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

void adc_line4(char* bcdVal){
 /* string[fifthChar] = space; 
  string[sixthChar] = space; 
  string[sevChar] = space; 
  string[eightChar] = space; 
  string[ninthChar] = space; 
  string[tenthChar] = space; */
  strcpy(display_line[string4], bcdVal);
  update_string(display_line[string4], string4);
  display_changed = positive; 
}
void adc_line3(char* bcdVal){
  /*string[fifthChar] = space; 
  string[sixthChar] = space; 
  string[sevChar] = space; 
  string[eightChar] = space; 
  string[ninthChar] = space; 
  string[tenthChar] = space; */
  strcpy(display_line[string3], bcdVal);
  update_string(display_line[string3], string3);
  display_changed = positive; 
}
void adc_line2(char* bcdVal){
 /* string[fifthChar] = space; 
  string[sixthChar] = space; 
  string[sevChar] = space; 
  string[eightChar] = space; 
  string[ninthChar] = space; 
  string[tenthChar] = space; */
  strcpy(display_line[string2], bcdVal);
  update_string(display_line[string2], string2);
  display_changed = positive; 
}

//===========================================================================
// Function Name : Init_ADC
// Arguments: None
// Return: None 
// Called From: Main 
//
// Globals: None 
// Locals: None 
// 
// Description: Initializes the ADC ports in the MSP430  
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void Init_ADC(void){
//------------------------------------------------------------------------------
// V_DETECT_L (0x04) // Pin 2 A2
// V_DETECT_R (0x08) // Pin 3 A3
// V_THUMB (0x20) // Pin 5 A5
//------------------------------------------------------------------------------
// ADCCTL0 Register
 ADCCTL0 = 0; // Reset
 ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
 ADCCTL0 |= ADCMSC; // MSC
 ADCCTL0 |= ADCON; // ADC ON
// ADCCTL1 Register
 ADCCTL2 = 0; // Reset
 ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
 ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
 ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
 ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
 ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
 ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
// ADCCTL1 & ADCBUSY identifies a conversion is in process
// ADCCTL2 Register
 ADCCTL2 = 0; // Reset
 ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
 ADCCTL2 |= ADCRES_2; // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
 ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
 ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
// ADCMCTL0 Register
 ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
 ADCMCTL0 |= ADCINCH_5; // V_THUMB (0x20) Pin 5 A5
 ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
 ADCCTL0 |= ADCENC; // ADC enable conversion.
 ADCCTL0 |= ADCSC; // ADC start conversion.
}