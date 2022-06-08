//===========================================================================
// File Name : interrupts_timers.c
//
// Description: ISR for timers 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#include "macros.h" 
#include "functions.h"
#include "msp430.h" 
#include <string.h>

//globals 
extern volatile unsigned char display_changed;
int timeCount = clear; 
int displayCount = clear;
volatile unsigned int Time_Sequence = clear;
volatile char one_time; 
extern volatile unsigned char update_display;
int debounceTimerSW1 = clear; 
int debounceTimerSW2 = clear; 
extern int SW1_Debounced;
extern int SW2_Debounced;
extern char display_line[numLines][numChars];
extern int motionCount = clear; 
extern int delayForward; 
extern int delayTime = clear; 
extern int startForward = clear; 
extern int detectBlack;
extern int driveTowardLine;
extern int process; 
extern int adjustDelay = clear; 
extern int adjustState; 
extern int adjustmentCounter = clear; 
extern int circleTimer = clear; 
extern int startCircle; 
extern int reAdjust = clear; 
extern int reAdjustTime = clear; 
extern int totalTime = clear; 
extern int timerTotal = clear;
extern int timerDisplay = clear; 
extern int timerCount = clear; 
extern int process; 
extern char string[numSpaces]; 
extern int splashTime = clear; 
extern int splash = clear; 
extern int baud_Delay = clear; 
extern int baudTimer = clear; 
extern int iotStart =clear; 
extern int iotDelay = clear; 
extern int ONTIME; 
extern int ONTIMER = clear; 
extern int timetravel; 
extern int starttimetravel; 
extern int tempTrav = clear; 
extern char timetoPos[11];
int ts100 = clear; 
int ts10 = clear; 
int ts1 = clear; 
int tempDisplayCount = clear;
// interrupt for timer B0, increments time sequence, display update

//===========================================================================
// File Name: Timer0_B0_ISR
//
// Description: ISR for timer B0 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//----------------------------------------------------------------------------
one_time = positive; 
Time_Sequence++; 
timeCount++; 
displayCount++;
motionCount++;
timerCount++; 

switch(timerCount){
case 10: 
  if(process >= positive){
  timerDisplay++; 
  timerCount = clear;}
  break; 
default: break; 
}

switch(starttimetravel){
case 1: 
  tempTrav++;
  switch(tempTrav){
  case 20:
    timetravel++;
    iTc(timetravel); 
     strcpy(display_line[string4], timetoPos);
  update_string(display_line[string4], string4);
  display_changed = positive;
  tempTrav = clear; 
    break;
  default:break; 
  }
    break; 
  
default: break; 
}


switch(iotStart){
case 1: 
  iotDelay++;
    break; 
  
default: break; 
}


switch(ONTIME){
case 1: 
  ONTIMER++;
    break; 
  
default: break; 
}


switch(displayCount){
case updis:
  update_display = positive; 
  displayCount = clear;
  break; 
default: break; 
}

switch(delayForward){
case 1: 
  delayTime++;
    break; 
  
default: break; 
}

switch(splash){
case positive: 
  splashTime++;
    break; 
  
default: break; 
}

switch(baud_Delay){
case positive: 
  baudTimer++;
    break; 
  
default: break; 
}

switch(adjustState){
case positive: 
  adjustmentCounter++; 
break; 
default: 
  break; 
}


switch(startCircle){
case positive:
  circleTimer++; 
  break;
default:
  break; 
}

switch(reAdjust){
case positive:
  reAdjustTime++; 
  break;
default:
  break; 
}

switch(totalTime){
case positive:
  timerTotal++;
  break; 
default:
  break; 
}





 TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0 
}

//----------------------------------------------------------------------------



// interrupt for timer B0, deals with debouncing 


//===========================================================================
// File Name : TIMER_B1_ISR
//
// Description: timerB1 ISR 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,overflow)){
case base: break; // No interrupt
case sw1Int: // CCR1 not used

if(SW1_Debounced == positive){
  debounceTimerSW1++; 
  
}
if(debounceTimerSW1 == turnOnDB){
  SW1_Debounced = clear; 
  
  
}
if(SW1_Debounced == clear & SW2_Debounced == clear){
  
  P4IE |= SW1;
  SW1_Debounced = clear; 
  debounceTimerSW1 = clear; 
  TB0CCTL1 &= ~CCIE;
  TB0CCTL0 |= CCIE;
}
TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
break;
case sw2Int: // CCR2 not used

if(SW2_Debounced == positive){
  debounceTimerSW2++; 
  
}
if(debounceTimerSW2 == turnOnDB){
  SW2_Debounced = clear; 
  P2IE |= SW2; 
 TB0CCTL2 &= ~CCIE;
 TB0CCTL0 |= CCIE;
}
if(SW1_Debounced == clear & SW2_Debounced == clear){
  
  debounceTimerSW2 = clear;
  
}
TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
break;
case overflow: // overflow
//...... Add What you need happen in the interrupt ......
break;
default: break;
}
}//--------

//===========================================================================
// File Name : iTc
//
// Description: converts counter from Main into display characters 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void iTc(int timetravel){
 ts100 = clear; 
ts10 = clear; 
ts1 = clear; 
tempDisplayCount = timetravel; 

for(int i = clear; i < 11 ; i++){
	if(i == 10){
	timetoPos[i] = nullChar; 
	}else if(i == 3){
	ts100 = (tempDisplayCount/100);
	timetoPos[i] = ts100 + '0'; 
	tempDisplayCount = tempDisplayCount - (ts100*100);
	}else if(i == 4){
	ts10 = (tempDisplayCount/10);
	timetoPos[i] = ts10 + '0'; 
	tempDisplayCount = tempDisplayCount - (ts10*10);
	}else if(i == 5){
	ts1 = tempDisplayCount;
	timetoPos[i] = ts1 + '0'; 
	}else{
	timetoPos[i] = ' '; 
	}
}

}
