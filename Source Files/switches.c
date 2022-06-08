//===========================================================================
// File Name : switches.c
//
// Description: this file is not used  
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

extern volatile unsigned int Time_Sequence;
char display_1[numChars];
char display_2[numChars];
char display_3[numChars];
char display_4[numChars];
int posL1; 
int posL2; 
int posL3; 
int posL4;
extern char display_line[numLines][numChars];
int buttonPress = clear;
int button2Press = clear; 
int buttonTime;
int block = clear; 
int TimeSeqLast1;
int whichCase; 
extern int shapesCase = clear; 
//extern int triangleCase = 0; 
//extern int Fig8Case = 0; 


void Switches_Process(void){
   if(TimeSeqLast1 != Time_Sequence){  // increments myTime everytime Time_Sequence is incremented 
      buttonTime++;
      TimeSeqLast1 = Time_Sequence; 
  }
  if(buttonTime%time1 == clear){  
      block = positive; 
  }
  if (!(P4IN & SW1) && block == positive) {
    buttonPress++;
    block = clear; 
}
  if (!(P2IN & SW2) && block == positive) {
    switch(whichCase){
    case cir:
      shapesCase = positive; 
      break;
    case fig8:
      shapesCase = fig8_2;  
      break;
    case tri: 
      shapesCase = tri_2;  
      break;
    case positive:
      shapesCase = clkChng; 
      break; 
    }
    block = clear; 
}
  switch(buttonPress){
  case defaultButton:
  strcpy(display_line[string1], "   NCSU   ");
  update_string(display_line[string1], string1);
  strcpy(display_line[string2], "  ECE306  ");
  update_string(display_line[string2], string2);
  strcpy(display_line[string3], "    LR    ");
  update_string(display_line[string3], string3);
  strcpy(display_line[string4], "    BC    ");
  update_string(display_line[string4], string4);
  whichCase = clear; 
  break;
 
  case buttonOne:  
  
  strcpy(display_line[string1], "Circle    ");
  update_string(display_line[string1], string1);
  strcpy(display_line[string2], "Figure 8  ");
  update_string(display_line[string2], string2);
  strcpy(display_line[string3], "Triangle  ");
  update_string(display_line[string3], string3);
  strcpy(display_line[string4], ">Change CLK      ");
  update_string(display_line[string4], string4);
  
  whichCase = positive; 
  
  break;
 
  case buttonTwo:  
  
   strcpy(display_line[string1], "Circle    ");
  update_string(display_line[string1], string1);
  strcpy(display_line[string2], "Figure 8  ");
  update_string(display_line[string2], string2);
  strcpy(display_line[string3], "Triangle  ");
  update_string(display_line[string3], string3);
  strcpy(display_line[string4], ">CLK  Back    ");
  update_string(display_line[string4], string4);
  
  whichCase = cir; 
  break;
  
  case buttonThree:  
  
   strcpy(display_line[string1], "Circle    ");
  update_string(display_line[string1], string1);
  strcpy(display_line[string2], ">Figure 8  ");
  update_string(display_line[string2], string2);
  strcpy(display_line[string3], "Triangle  ");
  update_string(display_line[string3], string3);
  strcpy(display_line[string4], "Change CLK      ");
  update_string(display_line[string4], string4);
  whichCase = fig8; 
  
  
  break;
  
  case buttonFour:  
  
   strcpy(display_line[string1], "Circle    ");
  update_string(display_line[string1], string1);
  strcpy(display_line[string2], "Figure 8  ");
  update_string(display_line[string2], string2);
  strcpy(display_line[string3], ">Triangle  ");
  update_string(display_line[string3], string3);
  strcpy(display_line[string4], "Change CLK      ");
  update_string(display_line[string4], string4);
  whichCase = tri; 
  
  break;
  
  case buttonFive:  
  
   strcpy(display_line[string1], "Circle    ");
  update_string(display_line[string1], string1);
  strcpy(display_line[string2], "Figure 8  ");
  update_string(display_line[string2], string2);
  strcpy(display_line[string3], "Triangle  ");
  update_string(display_line[string3], string3);
  strcpy(display_line[string4], ">Change CLK      ");
  update_string(display_line[string4], string4);
  whichCase = clockChange; 
  
  break;
  
  
  
  case buttonSix: 
    buttonPress = clear; 
    break; 
  }
//------------------------------------------------------------------------------
}