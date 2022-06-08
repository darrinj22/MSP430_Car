//===========================================================================
// File Name : movement.c 
//
// Description: contains functions to move car in various ways 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"


// globals 
int myTime;
int myTime1;
int myTime2;
extern volatile unsigned int Time_Sequence;
int timeStamp;
int lastTime; 
int clockwiseTime;
int stateFigure; 
int stateTriangle; 
int triTime; 
int TimeSeqLast;
int numTurns; 
int periodCircle = periodCircle1; 

//===========================================================================
// File Name : slowforward
//
// Description: moves the car forward at a slower pace 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void slowForward(void){
  RIGHT_FORWARD_SPEED = R_SLOW_DOWN; 
 LEFT_FORWARD_SPEED = L_SLOW_DOWN;
}
//===========================================================================
// File Name : forward
//
// Description: moves the car forward
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void forward(void){
 RIGHT_FORWARD_SPEED = RQUARTER_POWER; 
 LEFT_FORWARD_SPEED = LQUARTER_POWER;
}
//===========================================================================
// File Name : reverse
//
// Description: makes the car go reverse
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

void reverse(void){
 RIGHT_REVERSE_SPEED = RQUARTER_POWER;
 LEFT_REVERSE_SPEED = LQUARTER_POWER;
}
//===========================================================================
// File Name : off
//
// Description: turns the wheels of the car off 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

void off(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF; 
 LEFT_FORWARD_SPEED = WHEEL_OFF;
 RIGHT_REVERSE_SPEED = WHEEL_OFF;
 LEFT_REVERSE_SPEED = WHEEL_OFF; 
}
//===========================================================================
// File Name : clkwse
//
// Description: rotates the car clockwise
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

void clkwse(void){
  RIGHT_REVERSE_SPEED = RQUARTERR_POWER;
 LEFT_FORWARD_SPEED = LQUARTERR_POWER; 

}
//===========================================================================
// File Name : cntClkWse
//
// Description: car rotates counter clockwise
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void cntClkWse(void){
  LEFT_REVERSE_SPEED = L_SLOW_DOWN3;
 RIGHT_FORWARD_SPEED = R_SLOW_DOWN3; 
}

//===========================================================================
// File Name : circleClockwise
//
// Description: makes the car do a clockwise circle
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

void circleClockwise(void){
 

  if(clockwiseTime < periodCircle){ // if my counter is less than the prescribed amt of time it takes to complete a circle, then the loop continues 
    
   if(timeStamp > tick1){         // timeStamp records a determined amount of ticks of Time_Sequence, if it's greater than ticks (macros) than we turn the motor on                                   
    P6OUT |= R_FORWARD; 
    timeStamp = clear;             // clears timeStamp 
   }
   
   if(lastTime != Time_Sequence){  // increments myTime everytime Time_Sequence is incremented 
      clockwiseTime++;                 
      timeStamp++;
      lastTime = Time_Sequence; 
     P6OUT &= ~R_FORWARD;       // turns left motor off
     P6OUT |= L_FORWARD;       // turns right motor on
  }
   
  
  }else{
  P6OUT &= ~L_FORWARD;
  P6OUT &= ~R_FORWARD; 
  stateFigure = stateCounter1; 
  }
  
}
//===========================================================================
// File Name : circleClockwise1
//
// Description: makes the car do a clockwise circle 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void circleClockwise1(void){
 

  if(myTime1 < periodCircle){ // if my counter is less than the prescribed amt of time it takes to complete a circle, then the loop continues 
    
   if(timeStamp > tick1){         // timeStamp records a determined amount of ticks of Time_Sequence, if it's greater than ticks (macros) than we turn the motor on                                   
    P6OUT |= R_FORWARD; 
    timeStamp = clear;             // clears timeStamp 
   }
   
   if(lastTime != Time_Sequence){  // increments myTime everytime Time_Sequence is incremented 
      myTime1++;                 
      timeStamp++;
      lastTime = Time_Sequence; 
     P6OUT &= ~R_FORWARD;       // turns left motor off
     P6OUT |= L_FORWARD;       // turns right motor on
  }
   
  
  }else{
  P6OUT &= ~L_FORWARD;
  P6OUT &= ~R_FORWARD; 
  stateFigure = clear; 
  }
  
}
//===========================================================================
// File Name : circleCounterClock
//
// Description: makes the car do a counterclock wise circle 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void circleCounterClock(void){
                 
  

  if(myTime < periodCircle){ // if my counter is less than the prescribed amt of time it takes to complete a circle, then the loop continues 
    
   if(timeStamp > tick){         // timeStamp records a determined amount of ticks of Time_Sequence, if it's greater than ticks (macros) than we turn the motor on                                   
    P6OUT |= L_FORWARD; 
    timeStamp = clear;             // clears timeStamp 
   }
   
   if(lastTime != Time_Sequence){  // increments myTime everytime Time_Sequence is incremented 
      myTime++;                 
      timeStamp++;
      lastTime = Time_Sequence; 
     P6OUT &= ~L_FORWARD;       // turns left motor off
      P6OUT |= R_FORWARD;       // turns right motor on
  }
   
  
  }else{
  P6OUT &= ~L_FORWARD;
  P6OUT &= ~R_FORWARD; 
  stateFigure = stateClockwise; 
  }
}
//===========================================================================
// File Name : circleCounterClock1
//
// Description: makes the car do a counter clockwise circle 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void circleCounterClock1(void){
                 
  

  if(myTime2 < periodCircle){ // if my counter is less than the prescribed amt of time it takes to complete a circle, then the loop continues 
    
   if(timeStamp > tick){         // timeStamp records a determined amount of ticks of Time_Sequence, if it's greater than ticks (macros) than we turn the motor on                                   
    P6OUT |= L_FORWARD; 
    timeStamp = clear;             // clears timeStamp 
   }
   
   if(lastTime != Time_Sequence){  // increments myTime everytime Time_Sequence is incremented 
      myTime2++;                 
      timeStamp++;
      lastTime = Time_Sequence; 
     P6OUT &= ~L_FORWARD;       // turns left motor off
      P6OUT |= R_FORWARD;       // turns right motor on
  }
   
  
  }else{
  P6OUT &= ~L_FORWARD;
  P6OUT &= ~R_FORWARD; 
  stateFigure = stateClockwise1; 
  }
}
//===========================================================================
// File Name : triangle
//
// Description: makes the car make a triangle 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void triangle(void){
  if(numTurns <= 5){
  switch(stateTriangle){
  case straightLine:
    if(TimeSeqLast != Time_Sequence){  // increments myTime everytime Time_Sequence is incremented 
      triTime++;
      TimeSeqLast = Time_Sequence; 
  }
    if(triTime < lineTime){
    P6OUT |= L_FORWARD; 
    P6OUT |= R_FORWARD;
    }else if(triTime < (lineTime + turnTime)){
      P6OUT &= ~R_FORWARD;  
    }else{
      stateTriangle = Corner; 
    }
    break; 
  case Corner:
    triTime = clear; 
    numTurns++; 
    stateTriangle = straightLine; 
    break;
  }
  }else{
    P6OUT &= ~L_FORWARD;
    P6OUT &= ~R_FORWARD; 
    
  }
}
//===========================================================================
// File Name : figure8
//
// Description: makes the car do a figure 8 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void figure8(void){
   switch(stateFigure){
  case stateCounter:
      periodCircle = periodfig8; 
      circleCounterClock();
      break;
  case stateClockwise:
    periodCircle = periodfig8;
      circleClockwise();
      break;
   case stateCounter1:
      
      periodCircle = periodfig8; 
      circleCounterClock1();
      break;
   case stateClockwise1:
      
     clockwiseTime = clear;
    periodCircle = periodfig8;
      circleClockwise1();
      break;
   default:
      
     break; 
   
  }
}