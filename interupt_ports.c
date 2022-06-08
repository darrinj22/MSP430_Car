//===========================================================================
// File Name : interrupt_ports.c
//
// Description: ISR to check for switch presses for SW1 and SW2 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#include "macros.h" 
#include "functions.h"
#include "msp430.h" 
#include <string.h>

// globals 
extern char display_line[numLines][numChars];
int SW1_Pressed = clear; 
extern int SW1_Debounced = clear; 
int SW2_Pressed = clear; 
extern int SW2_Debounced = clear; 
extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
int irState = clear; 
extern int delayForward = clear; 
extern int adjustEnabled = clear; 
extern int emitter = positive; 
extern int transmit_go;
extern int transmit_large; 

//===========================================================================
// File Name : switchP4_interrupt
//
// Description: interrupts main if switch is pressed 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
// Switch 1
if (P4IFG & SW1) {
P4IFG &= ~SW1; // IFG SW1 cleared
P4IE &= ~SW1;
SW1_Pressed = positive; 
SW1_Debounced = positive; 
TB0CCTL1 |= CCIE;
TB0CCTL0 &= ~CCIE;

transmit_go = positive; 
transmit_large = clear;

switch(irState){
case emitOff: 
  
  P3OUT &= ~IR_LED;
/*strcpy(display_line[string1], "EMITTEROFF");
  update_string(display_line[string1], string1);
  
  display_changed = positive;*/
    emitter = clear; 
  irState++;
break; 

case emitOn:
  P3OUT |= IR_LED;
/*strcpy(display_line[string1], "EMITTER ON");
  update_string(display_line[string1], string1);
  
  display_changed = positive; */
  
  emitter = positive; 
  
  irState = clear; 
  break; 
default:break; 
}
}
}

//===========================================================================
// File Name : switchP2_interrupt
//
// Description: interrupts main if switch is pressed 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
// Switch 2
if (P2IFG & SW2) {
P2IFG &= ~SW2; // IFG SW2 cleared
P2IE &= ~SW2;

SW2_Pressed = positive; 
SW2_Debounced = positive; 
TB0CCTL2 |= CCIE;
TB0CCTL0 &= ~CCIE;

delayForward = positive; 
adjustEnabled = positive; 
transmit_large = positive;
transmit_go = clear;
}
}