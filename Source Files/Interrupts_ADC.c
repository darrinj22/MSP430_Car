
//===========================================================================
// File Name : Interrupts_ADC.c
//
// Description: This file contains the interrupts to receive the ADC Values 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

// Globals
extern int ADC_Left_Detect; 
extern int ADC_Right_Detect; 
int ADC_Channel;
int ADC_THUMB; 
extern char display_line[numLines][numChars];
extern volatile unsigned char display_changed;
extern char string[numSpaces];


//===========================================================================
// Function Name : ADC_ISR

// 
// Description: ISR to read values from receptors 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
 switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
     case ADCIV_NONE:
      break;
     case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
     // before its previous conversion result was read.
          break;
     case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
           break;
     case ADCIV_ADCHIIFG: // Window comparator interrupt flags
          break;
     case ADCIV_ADCLOIFG: // Window comparator interrupt flag
          break;
     case ADCIV_ADCINIFG: // Window comparator interrupt flag
          break;
     case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
          ADCCTL0 &= ~ADCENC; // Disable ENC bit.
               switch (ADC_Channel++){
                  case leftSensor: // Channel A2 Interrupt
                     ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
                     ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
                     ADC_Left_Detect = ADCMEM0; // Move result into Global
                     ADC_Left_Detect = ADC_Left_Detect >> divide; // Divide the result by 4
                    // HEXtoBCD(ADC_Left_Detect); // Convert result to String
                     //adc_line2(string); // Place String in Display
                     break;
                   case rightSensor:
                     ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A2
                     ADCMCTL0 |= ADCINCH_5; // Enable Next channel A3
                     ADC_Right_Detect = ADCMEM0; // Move result into Global
                     ADC_Right_Detect = ADC_Right_Detect >> divide; // Divide the result by 4
                     //HEXtoBCD(ADC_Right_Detect); // Convert result to String
                     //adc_line3(string); // Place String in Di
                     break;
                   case thumbWheel:
                      ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A2
                     ADCMCTL0 |= ADCINCH_2;
                     ADC_THUMB = ADCMEM0;
                     ADC_THUMB = ADC_THUMB >> divide; // Divide the result by 4
                    // HEXtoBCD(ADC_THUMB); // Convert result to String
                     //adc_line4(string); // Place String in Display
                      ADC_Channel=clear;
                      break;
                   default:
                      break;
                   }
                ADCCTL0 |= ADCENC; // Enable Conversions
                ADCCTL0 |= ADCSC; 
 default:
  break;
 }
}