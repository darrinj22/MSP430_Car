//===========================================================================
// File Name : main.c
//
// Description: contains the almight while loop  
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

  // Global Variables
volatile char slow_input_down;
extern char display_line[numLines][numChars];
extern char *display[numLines];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
extern int myTime; 
extern int clockwiseTime; 
extern int triTime; 
extern int stateTriangle; 
extern int numTurns; 
extern int buttonPress; 
extern int shapesCase; 
extern int motionCount; 
int ADC_Left_Detect; 
int ADC_Right_Detect;
extern int startForward; 
extern int detectBlack = clear; 
extern int delayTime; 
extern int delayForward;
extern int adjustState = clear; 
extern int driveTowardLine = clear; 
extern int finishAlign = clear; 
extern int adjustEnabled;
extern int process = clear; 
extern int adjustDelay; 
extern int adjustmentCounter; 
int startAdjust = clear; 
extern int emitter;
int direction;
extern int startCircle = clear; 
extern int circleTimer;
extern int reAdjust; 
extern int reAdjustTime;
int variable = clear; 
extern int totalTime; 
extern int timerTotal;
extern int timerDisplay; 
char timerLCD[positive]; 
int j; 
char black[numSpaces] = "BLACK    ";
char white[numSpaces] = "WHITE    ";
extern int UCA0_index; 
extern char test_command[12];
extern int UCA1_index; 
extern char test_command1[12]; 
extern int transmit_go = clear; 
extern int transmit_large = clear; 
int h = clear;
int m = clear;
extern char baudRate1[11] = "  115,200 ";
extern char baudRate2[11] = "  460,800 ";
extern char baud[11] = "   Baud   "; 
extern char ncsu[11] = "  NCSU #1 "; 
extern char ncsu1[11] ="  NCSU #1 "; 
extern int splashTime; 
extern int splash;
int baudMenu = positive; 
extern int baud_Delay;
extern int baudTimer;
int transmit_460 = positive; 
int transmit_115 = positive; 
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx[LARGE_RING_SIZE];
extern char receiveChar[SMALL_RING_SIZE];
extern volatile char USB_Char_Rx1[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx1[LARGE_RING_SIZE];
extern volatile unsigned int usb_rx_ring_rd;
extern int gtg; 
char array1[SMALL_RING_SIZE];
char array2[SMALL_RING_SIZE];
int useA0 = clear; 
int useA1 = clear; 
int tempRead = clear; 
extern int gotMessage; 
int setb1 = positive; 
int setb2 = clear; 
int returnWait = clear; 
extern int iotStart; 
extern int iotDelay; 
char command; 
extern int commandFound; 
char transmit_array_A1[SMALL_RING_SIZE]; 
//char messageToFrom[11] ={0}; 
char Processbuff[SMALL_RING_SIZE];
char Processbuff_IOT[SMALL_RING_SIZE];
extern int pb_wr; 
extern int pb_wr_iot;
int g = clear; 
extern int framCommand; 
extern int recogCommand; 
 char password[4]; 
char carComs[1]; 
char carTime[3]; 
extern int passGood = clear;
extern int newVar; 
extern int ONTIME = clear; 
extern int ONTIMER; 
int lightOn = clear; 
extern int commTime = clear; 
int commDuration = clear;
extern int ipAddressFound; 
extern char keepConnect[23] = "AT+WSYNCINTRL=50000\r\n"; 
extern char connectPort[20] = "AT+NSTCP=5555,1\r\n";
extern char getInfo[15] = "AT+NSTAT=?\r\n"; 
extern int startConnect; 
extern int doneConnect; 
char IPADDRESS[SMALL_RING_SIZE]; 
char firstLineIP[11]; 
char secLineIP[3]; 
int ipfound = clear; 
extern int bootUpDone = clear; 
extern int doneIP = clear;
extern int readyPort = clear; 
extern int sentCommand; 
int firstThing = positive; 
extern int alreadyDone; 
extern int keepConnectFlag = clear; 
extern int keepConnectIE = clear; 
extern int offset[9]; 
extern int positionNum = clear; 
extern int timetravel = clear; 
extern char timetoPos[11] = "    00    ";
char currentSituation[11] = "Waiting  0";
int moveOn = clear; 
extern int starttimetravel = clear; 
extern int tempTrav; 
char blackLineCommand[11] = "          "; 
int firstTimethru = clear; 
int readyToExit = clear; 
void main(void){

  
 // -----------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
   PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timer_B0();                       // Initialize Timers
  Init_Timer_B3();
  Init_LCD();                          // Initialize LCD
  //Init_ADC();
  Init_Serial_UCA0(positive);
  Init_Serial_UCA1(positive); 
  
  iotStart = positive; 
  
  
  
  
  

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//----------------------------------------------------------------------------
   strcpy(display_line[string1], "          ");
  update_string(display_line[string1], string1);
  strcpy(display_line[string2], " WELCOME  ");
  update_string(display_line[string2], string2);
  strcpy(display_line[string3], "          ");
  update_string(display_line[string3], string3);
  strcpy(display_line[string4], "          ");
  update_string(display_line[string4], string4);
  
  display_changed = positive;
  
  
  while(ALWAYS) { 
    
    switch(firstThing){
    case iotwait: 
      if(iotDelay > wait4IOT){
        //iotStart = clear; 
        iotDelay = clear; 
        P5OUT |= IOT_RESET; 
        firstThing = iotport;
      }
      break; 
    case iotport:
      if(iotDelay > wait2connect){
        iotDelay = clear;  
        UCA0IE |= UCTXIE; 
        readyPort = positive; 
        firstThing = iotip; 
      }
      break;
    case iotip: 
      if(iotDelay > wait4ip){
        iotDelay = clear; 
        iotStart = clear; 
        firstThing = getIPadd; 
      }
      break; 
    case getIPadd:
    if((readyPort == clear) && (ipfound == clear)&& (sentCommand == clear)&&(alreadyDone != positive)){
      UCA0IE |= UCTXIE; 
      bootUpDone = positive; 
    }
    
    if(keepConnectFlag == positive){
      UCA0IE |= UCTXIE; 
     keepConnectIE = positive; 
     keepConnectFlag = clear; 
    }
    
   if(IPADDRESS[clear] != nullChar){
     ipfound = positive; 
   }
   
   if((ipfound == positive)){
     
     for(int u = clear; u < lenIP ; u++){
       firstLineIP[u] = IPADDRESS[u]; 
     }
     firstLineIP[amtIP] = nullChar; 
      secLineIP[clear] = IPADDRESS[amtIP];
      secLineIP[positive] = IPADDRESS[amtIPlus]; 
     secLineIP[secondary] = nullChar; 
   
     strcpy(display_line[string1], currentSituation);
  update_string(display_line[string1], string1);
  strcpy(display_line[string2], firstLineIP);
  update_string(display_line[string2], string2);
  if(firstTimethru == clear){
  
  strcpy(display_line[string3], secLineIP);
  update_string(display_line[string3], string3);
  }else{
    
  strcpy(display_line[string3], blackLineCommand);
  update_string(display_line[string3], string3);
  }
 // strcpy(display_line[string4], timeToPos);
  //update_string(display_line[string4], string4);
  display_changed = positive;
  ipfound = throwaway; 
  moveOn = positive; 
  doneIP = positive; 
   }
   
   if(doneIP == positive){
     if(readyToExit == positive){
        if(ADC_Left_Detect > border1 && ADC_Right_Detect > border1 && variable != positive ){
        // turn both forward  
        RIGHT_FORWARD_SPEED = R_SLOW_DOWN1; 
        LEFT_FORWARD_SPEED = L_SLOW_DOWN1;
        variable = positive; 
      }
      if(ADC_Left_Detect < border1 && ADC_Right_Detect > border1 && variable != var2){
        // turn right wheel off 
        RIGHT_FORWARD_SPEED = WHEEL_OFF; 
        LEFT_FORWARD_SPEED = L_SLOW_DOWN1;
        variable = var2; 
      }
      if(ADC_Left_Detect >  border1  && ADC_Right_Detect < border1 && variable != var3){
        // turn left wheel off 
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_FORWARD_SPEED = R_SLOW_DOWN1;
        variable = var3; 
      }
     }
     
    
// if a new line is found, gotMessage is triggered saying something has been sent
    if(gotMessage == positive){
// clears the array pointer for Processbuff_IOT
      pb_wr_iot = clear; 
// receives all the characters needed into Processbuff_IOT
      for(int h = clear; h < sizeof(Processbuff_IOT); h++){
     receiveIOT(); 
      }
// this doesn't actually parse data, it just looks for the ^      
      parseData(Processbuff_IOT);
// if a ^ is found, then recogCommand is positive 
      if(recogCommand == positive){
// once it's found, it knows where to search for the proper command 
        password[clear] = Processbuff_IOT[offset[cs0]];
        currentSituation[cs0] = Processbuff_IOT[offset[cs0]]; 
        password[digit2] = Processbuff_IOT[offset[cs1]];
        currentSituation[cs1] = Processbuff_IOT[offset[cs1]]; 
        password[digit3] = Processbuff_IOT[offset[cs2]];
        currentSituation[cs2] = Processbuff_IOT[offset[cs2]]; 
        password[digit4] = Processbuff_IOT[offset[cs3]];
        currentSituation[cs3] = Processbuff_IOT[offset[cs3]]; 
        carComs[clear] = Processbuff_IOT[offset[cs4]];
        currentSituation[cs4] = Processbuff_IOT[offset[cs4]]; 
        carTime[clear] = Processbuff_IOT[offset[cs5]];
        currentSituation[cs5] = Processbuff_IOT[offset[cs5]]; 
        carTime[digit2] = Processbuff_IOT[offset[cs6]];
        currentSituation[cs6] = Processbuff_IOT[offset[cs6]]; 
        carTime[digit3] = Processbuff_IOT[offset[cs7]];
        currentSituation[cs7] = Processbuff_IOT[offset[7]];
      }
// converts array to decimal for time intervals 
      
     convertTime(carTime); 
      
// checks if password is correct and if a command has been recognized 
      if((recogCommand == positive) && checkPassword(password)){
// flags that command duration has started 
      commDuration = positive; 
// once we know it's a command and we have the password correct 
// we just switch on the actual command value
      switch(carComs[clear]){
      case 'F':
        ONTIME = positive;
       // lightOn = clear; 
        // flags timer to start
        switch(lightOn){   // switches on/off the function 
        case clear: 
         // P6OUT |= LCD_BACKLITE;
            
          forward(); 
          lightOn = positive;
          
          break;
        case positive:
          if(ONTIMER > commTime){
           // P6OUT &= ~LCD_BACKLITE; 
            off(); 
            ONTIME = clear;
            ONTIMER = clear; 
            lightOn = clearVars; 
          }
          break;
        case clearVars:
          lightOn = clear; 
          commDuration = clear; 
          ONTIMER = clear; 
          ONTIME = clear; 
          recogCommand = clear; 
          
          break; 
        default:
          break; 
        }
        //P6OUT |= LCD_BACKLITE; 
        break;
          
      case 'E': 
      readyToExit = clear;  
      ONTIME = positive;
        switch(lightOn){
        case clear: 
     strcpy(blackLineCommand,"BL  EXIT  ");
          cntClkWse();
          lightOn = positive; 
              
          break;
        case positive:
          if(ONTIMER > wait16){
             
             off(); 
            ONTIME = clear;
            ONTIMER = clear; 
            lightOn = end; 
          }
          break;
        case end:
          forward(); 
          lightOn = stop; 
          break;
        case stop:
          if(ONTIMER > wait2){
            
            off(); 
             strcpy(blackLineCommand,"BL  STOP  "); 
            ONTIME = clear; 
            ONTIMER = clear;
            lightOn = clearVars; 
            
          }
          break; 
        case clearVars:
          lightOn = clear; 
          commDuration = clear; 
          ONTIMER = clear; 
          ONTIME = clear; 
          recogCommand = clear; 
          
          break; 
        default:
          break; 
        }
        break; 
        
      case 'R': 
      ONTIME = positive;
        switch(lightOn){
        case clear: 
     
          reverse(); 
          lightOn = positive; 
              
          break;
        case positive:
          if(ONTIMER > commTime){
             
            off(); 
            ONTIME = clear;
            ONTIMER = clear; 
            lightOn = clearVars; 
          }
          break;
        case clearVars:
          lightOn = clear; 
          commDuration = clear; 
          ONTIMER = clear; 
          ONTIME = clear; 
          recogCommand = clear; 
          
          break; 
        default:
          break; 
        }
        break; 
        
        case 'N': 
      ONTIME = positive;
        switch(lightOn){
        case clear: 
          
          clkwse();
          lightOn = positive; 
                 
          break;
        case positive:
          if(ONTIMER > commTime){
             
            off(); 
            ONTIME = clear;
            ONTIMER = clear; 
            lightOn = clearVars; 
          }
          break;
        case clearVars:
          lightOn = clear; 
          commDuration = clear; 
          ONTIMER = clear; 
          ONTIME = clear; 
          recogCommand = clear; 
          
          break; 
        default:
          break; 
        }
        break; 
        
        case 'D': 
      ONTIME = positive;
        switch(lightOn){
        case clear: 
          
          cntClkWse(); 
          lightOn = positive;      
           
          break;
        case positive:
          if(ONTIMER > commTime){
             
            off(); 
            ONTIME = clear;
            ONTIMER = clear; 
            lightOn = clearVars; 
          }
          break;
        case clearVars:
          lightOn = clear; 
          commDuration = clear; 
          ONTIMER = clear; 
          ONTIME = clear; 
          recogCommand = clear; 
          
          break; 
        default:
          break; 
        }
        break; 
      
            case 'I': 
      ONTIME = positive;
        switch(lightOn){
        case clear: 
          
          positionNum++;  
          currentSituation[9] = positionNum + '0'; 
         // starttimetravel = clear; 
          //timetravel = clear;
          //tempTrav = clear; 
          lightOn = positive;      
           
          break;
        case positive:
          if(ONTIMER > commTime){
             
            
            ONTIME = clear;
            ONTIMER = clear; 
            lightOn = clearVars; 
          }
          break;
        case clearVars:
          lightOn = clear; 
          commDuration = clear; 
          ONTIMER = clear; 
          ONTIME = clear; 
          recogCommand = clear; 
          
          break; 
        default:
          break; 
        }
        break; 
        
        
            case 'B': 
      ONTIME = positive;
        switch(lightOn){
        case clear: 
          starttimetravel = positive; 
          lightOn = positive;      
           
          break;
        case positive:
          if(ONTIMER > commTime){
             
            
            ONTIME = clear;
            ONTIMER = clear; 
            lightOn = clearVars; 
          }
          break;
        case clearVars:
          lightOn = clear; 
          commDuration = clear; 
          ONTIMER = clear; 
          ONTIME = clear; 
          recogCommand = clear; 
          
          break; 
        default:
          break; 
        }
        break; 
        
           case 'Y': 
     //  P5OUT &= ~IOT_RESET; 
      firstTimethru = positive; 
      ONTIME = positive;
        switch(lightOn){
        case clear: 
          strcpy(blackLineCommand,"BL   START"); 
          forward(); 
          lightOn = positive;      
           
          break;
        case positive:
          if(ONTIMER > OneSecInterval){
             
            off(); 
            ONTIME = clear;
            ONTIMER = clear; 
            lightOn = turnRightWait;
            ONTIME = positive; 
          }
          break;
        case turnRightWait:
          if(ONTIMER > TwoSecInterval){
            
            ONTIME = clear; 
            ONTIMER = clear; 
            lightOn = turnRight; 
          }
          break; 
        case turnRight:
          clkwse();
          lightOn = finishTurn;
          break; 
        case finishTurn:
          if(ONTIMER > 12){
            off(); 
              ONTIME = clear;
            ONTIMER = clear; 
            lightOn = approachBoard;
            ONTIME = positive; 
          }
        case approachBoardWait:
          if(ONTIMER > TwoSecInterval){
            
            ONTIME = clear; 
            ONTIMER = clear; 
            lightOn = approachBoard; 
          }
          break;
        case approachBoard:
          forward(); 
          lightOn = finishApproach; 
          break; 
        case finishApproach:
          if(ONTIMER > 70){
            off(); 
              ONTIME = clear;
            ONTIMER = clear; 
            lightOn = turnRightAgainWait;
            ONTIME = positive; 
          }
          break; 
        case turnRightAgainWait:
            if(ONTIMER > TwoSecInterval){
            
            ONTIME = clear; 
            ONTIMER = clear; 
            lightOn = turnRightAgain; 
          }
          break;
        case turnRightAgain:
          clkwse(); 
          lightOn = finishAgain; 
          break; 
        case finishAgain:
           if(ONTIMER > 13){
            off(); 
              ONTIME = clear;
            ONTIMER = clear; 
            lightOn = readyADC;
            ONTIME = positive; 
          }
          break; 
        case readyADC:
          Init_ADC();
          lightOn = interceptionWait; 
          break; 
        case interceptionWait:
          if(ONTIMER > 30){
             ONTIME = clear; 
            ONTIMER = clear; 
            lightOn = interceptionPath; 
          }
          break; 
        case interceptionPath:
          forward(); 
          lightOn = findWhitePage;
          break; 
        case findWhitePage:
          if(ADC_Left_Detect < findWHITE && ADC_Right_Detect < findWHITE){
            off(); 
            lightOn = project7code; 
            process = positive; 
          }
          break; 
        case project7code:
              
    switch(process){
    case positive: 
      if(ADC_Left_Detect < border || ADC_Right_Detect < border){
        slowForward(); 
      }
      if(ADC_Left_Detect > border || ADC_Right_Detect > border){
        strcpy(blackLineCommand,"INTERCEPT "); 
        off(); 
        process = waitToAlign; 
      }
      break; 
    case waitToAlign: 
       adjustState = positive; 
       
      if(adjustmentCounter == delayAdjust){
        adjustState = clear; 
        process = adjustment; 
      }
      break; 
    case adjustment: 
      if(ADC_Left_Detect < border || ADC_Right_Detect < border){
         cntClkWse(); 
          
      }
      if(ADC_Left_Detect > border && ADC_Right_Detect > border){
      
        off(); 
        finishAlign = positive; 
        adjustEnabled = clear; 
      }
      if(finishAlign == positive){
        process = finish; 
        reAdjust = positive; 
      }
      break;
    case finish:
    /*  if(reAdjustTime > 20){
      if(ADC_Left_Detect < border || ADC_Right_Detect < border){
        cntClkWse(); 
      }else{
        off(); 
      }
      }*/
     process = pp5;
       
      break;
    case pp5:
       startCircle = positive; 
      if(circleTimer == circleDelay){
        startCircle = clear; 
        process = pp6; 
      }
      
      break; 
    case pp6:
    
      off(); 
      process = pp7; 
      totalTime = positive; 
      break; 
    case 7: 
      if(timerTotal < wait1andhalf){
         strcpy(blackLineCommand,"BL  TRAVEL"); 
      }else{
         strcpy(blackLineCommand,"BL  CIRCLE"); 
      }
      if(timerTotal < findWHITE){
      if(ADC_Left_Detect > border && ADC_Right_Detect > border && variable != positive ){
        // turn both forward  
        RIGHT_FORWARD_SPEED = R_SLOW_DOWN1; 
        LEFT_FORWARD_SPEED = L_SLOW_DOWN1;
        variable = positive; 
      }
      if(ADC_Left_Detect < border && ADC_Right_Detect > border && variable != var2){
        // turn right wheel off 
        RIGHT_FORWARD_SPEED = WHEEL_OFF; 
        LEFT_FORWARD_SPEED = L_SLOW_DOWN1;
        variable = var2; 
      }
      if(ADC_Left_Detect >  border  && ADC_Right_Detect < border && variable != var3){
        // turn left wheel off 
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_FORWARD_SPEED = R_SLOW_DOWN1;
        variable = var3; 
      }
      }else{
        totalTime = clear; 
        timerTotal = clear;
        readyToExit = positive;
        // off();
        process = lenIP ; 
         
      }
      
    break; 
    case lenIP: 
     // off();
      process = intermediate;
      lightOn = clearVars; 
      break;
    default:
       
      break; 
    }
    
  
          break; 
        case clearVars:
          lightOn = clear; 
          commDuration = clear; 
          ONTIMER = clear; 
          ONTIME = clear; 
          recogCommand = clear; 
          
          break; 
        default:
          break; 
        }
        break; 
        
      default:
        commDuration = clear; 
        recogCommand = clear; 
        break; 
      }
      //recogCommand = clear; 
      }else{
      
     // gotMessage = clear; 
      }
      if(commDuration == clear){
gotMessage = clear; 
for(int u = clear; u < SMALL_RING_SIZE; u++){
  Processbuff_IOT[u] = nullChar; 
}
      }
    }else{
        currentSituation[cs0] = 'W'; 
        currentSituation[cs1] = 'A';
        currentSituation[cs2] = 'I';
        currentSituation[cs3] = 'T';
        currentSituation[cs4] = 'I';
        currentSituation[cs5] = 'N';
        currentSituation[cs6] = 'G';
        currentSituation[cs7] = ' ';
        
    
      }
  }
  break;
  default:
    break;
  }
    Display_Process();
  }
  
  
  }
//------------------------------------------------------------------------------





