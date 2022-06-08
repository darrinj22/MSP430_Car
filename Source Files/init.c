//===========================================================================
// File Name : init.c
//
// Description: Initializes the display values. 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#include "macros.h" 
#include "functions.h"
#include "msp430.h" 

extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
extern char display_line[numLines][numChars];
extern char *display[numLines];
extern int stateFigure;



//===========================================================================
// Function Name : Init_Conditions
// Arguments: None  
// Return: None 
// Called From: Main
//
// Globals: display_line 
// Locals: none 
// 
// Description: Clear alls the spaces on the display line  
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;
  stateFigure = stateCounter; 

  for(i=clear;i<numChars;i++){
    display_line[string1][i] = RESET_STATE;
    display_line[string2][i] = RESET_STATE;
    display_line[string3][i] = RESET_STATE;
    display_line[string4][i] = RESET_STATE;
  }
  display_line[string1][lastchar] = clear;
  display_line[string2][lastchar] = clear;
  display_line[string3][lastchar] = clear;
  display_line[string4][lastchar] = clear;

  display[string1] = &display_line[string1][firstchar];
  display[string2] = &display_line[string2][firstchar];
  display[string3] = &display_line[string3][firstchar];
  display[string4] = &display_line[string4][firstchar];
  update_display = clear;
  update_display_count = clear;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}
