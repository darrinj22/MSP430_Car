//===========================================================================
// File Name : Init_Serial.c 
//
// Description: Initializes serial ports on the MSP430 for serial communications
// also contains a wide variety of functions for serial communication use 
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
/////////////////////////////////////////////

#include "macros.h" 
#include "functions.h"
#include "msp430.h" 
#include <string.h>
#include <stdlib.h>

//////////////////////////////////////////////

///////////////////////////////////////////////
//              GLOBAL VARIABLES            //
/////////////////////////////////////////////
extern char display_line[numLines][numChars];
extern char *display[numLines];

extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;

volatile unsigned int usb_rx_ring_wr; 
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_wr; 
volatile unsigned int usb_tx_ring_rd;
volatile char USB_Char_Rx[SMALL_RING_SIZE]; 
volatile char USB_Char_Tx[LARGE_RING_SIZE];
char receiveChar[SMALL_RING_SIZE]; 

volatile unsigned int usb_rx_ring_wr1; 
volatile unsigned int usb_rx_ring_rd1;
volatile unsigned int usb_tx_ring_wr1; 
volatile unsigned int usb_tx_ring_rd1;
volatile char USB_Char_Rx1[SMALL_RING_SIZE]; 
volatile char USB_Char_Tx1[LARGE_RING_SIZE];

extern char array1[SMALL_RING_SIZE];
extern char array2[SMALL_RING_SIZE];

extern char Processbuff[SMALL_RING_SIZE]; 
extern char Processbuff_IOT[SMALL_RING_SIZE];
extern int pb_wr = clear; 
extern int pb_wr_iot = clear; 

extern int recogCommand = clear; 
extern char password[4]; 
extern char carComs[1]; 
extern char carTime[3]; 
extern int commandFound = clear; 
extern int commTime; 
int offset[9];
int offsetMax; 
//int wait_2_transmit = clear; 



//===========================================================================
// Function Name : Init_Serial_UCA0
// Arguments: baudRate_A0
// Return: None 
// Called From: Main 
//
// Globals: usb_rx_ring_wr, usb_rx_ring_rd, USB_Char_Rx, usb_tx_ring_wr, 
// usb_tx_ring_rd 
// Locals: i
// 
// Description: Initializes baud rate and MSP430 ports 
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

void Init_Serial_UCA0(int baudRate_A0){
int i;

for(i=clear; i<SMALL_RING_SIZE; i++){
USB_Char_Rx[i] = clear; // USB Rx Buffer
}
usb_rx_ring_wr = BEGINNING;
usb_rx_ring_rd = BEGINNING;

for(i=clear; i<LARGE_RING_SIZE; i++){ // May not use this
USB_Char_Tx[i] = clear; // USB Tx Buffer
}
usb_tx_ring_wr = BEGINNING;
usb_tx_ring_rd = BEGINNING;
// Configure UART 0

UCA0CTLW0 = clear; // Use word register
UCA0CTLW0 |= UCSWRST; // Set Software reset enable
UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK

if(baudRate_A0 == positive){
UCA0BRW = baud_115200_BRW; // 115200 Baud
UCA0MCTLW = baud_115200_MCTLW ;
}else if(baudRate_A0 == clear){
  UCA0BRW = baud_460800_BRW; // 460800 Baud
UCA0MCTLW = baud_460800_MCTLW ;
} else{
    UCA0BRW = baud_9600_BRW; // 460800 Baud
UCA0MCTLW = baud_9600_MCTLW ;
}

UCA0CTLW0 &= ~UCSWRST; // Set Software reset enable
UCA0IE |= UCRXIE; // Enable RX Interrupt 
}



//===========================================================================
// Function Name : InitSerial_UCA1
// Arguments: int baudRate_A1 
// Return: None 
// Called From: Main
//
// Globals: usb_rx_ring_wr, usb_rx_ring_rd, USB_Char_Rx, usb_tx_ring_wr, 
// usb_tx_ring_rd 
// Locals: i
// 
// Description: Initializes baud rate and MSP430 ports 
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

void Init_Serial_UCA1(int baudRate_A1){
int i;

for(i=clear; i<SMALL_RING_SIZE; i++){
USB_Char_Rx1[i] = clear; // USB Rx Buffer
}
usb_rx_ring_wr1 = BEGINNING;
usb_rx_ring_rd1 = BEGINNING;

for(i=clear; i<LARGE_RING_SIZE; i++){ // May not use this
USB_Char_Tx1[i] = clear; // USB Tx Buffer
}
usb_tx_ring_wr1 = BEGINNING;
usb_tx_ring_rd1 = BEGINNING;
// Configure UART 0
UCA1CTLW0 = clear; // Use word register
UCA1CTLW0 |= UCSWRST; // Set Software reset enable
UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK

if(baudRate_A1 == positive){
UCA1BRW =  baud_115200_BRW; // 4
UCA1MCTLW = baud_115200_MCTLW ; // 0x5551
}else if(baudRate_A1 == clear){
  UCA1BRW = baud_460800_BRW; // 
UCA1MCTLW = baud_460800_MCTLW ; // 0x49
}else{
  UCA1BRW = baud_9600_BRW; // 
UCA1MCTLW = baud_9600_MCTLW ;
}

UCA1CTLW0 &= ~UCSWRST; // Set Software reset enable
UCA1IE |= UCRXIE; // Enable RX Interrupt 
}


//===========================================================================
// Function Name : out_character
// Arguments: char character
// Return: None 
// Called From: Main
//
// Globals: UCA0TXBUF
// Locals: None
// 
// Description: Transmits a character to the IOT Port   
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void out_character(char character){
//------------------------------------------------------------------------------
// The while loop will stall as long as the Flag is not set [port is busy]
while (!(UCA0IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
UCA0TXBUF = character;
//------------------------------------------------------------------------------
}

//===========================================================================
// Function Name : out_character_A1
// Arguments: char character
// Return: None 
// Called From: Main
//
// Globals: UCA1TXBUF
// Locals: None
// 
// Description: Tranmist character to the USB Serial Port 
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

void out_character_A1(char character){
//------------------------------------------------------------------------------
// The while loop will stall as long as the Flag is not set [port is busy]
  while (!(UCA1IFG & UCTXIFG)); // USCI_A0 TX buffer ready?
    UCA1TXBUF = character;
//------------------------------------------------------------------------------
}



//===========================================================================
// Function Name : transmitUSB
// Arguments: None
// Return: None 
// Called From: 
//
// Globals: usb_tx_ring_wr1
// Locals: None
// 
// Description: Transmits to USB  
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void transmitUSB(void){
  usb_tx_ring_wr1 = clear; 
  UCA1IE |= UCTXIE; 
}

//===========================================================================
// Function Name : transmitIOT
// Arguments: None
// Return: None 
// Called From:
//
// Globals: usb_tx_ring_wr1,usb_rx_ring_rd1,pb_wr,USB_Char_Rx1, usb_rx_ring_rd1, 
// Locals: None
// 
// Description: Tranmits to IOT Serial Port 
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void receiveUSB(void){

  int usbwr = usb_rx_ring_wr1;
  if (usbwr != usb_rx_ring_rd1){
Processbuff[pb_wr++] = USB_Char_Rx[usb_rx_ring_rd1++] ;
 if (pb_wr >= (sizeof(Processbuff))){
 pb_wr = BEGINNING; // Circular buffer back to beginning
 }
 if (usb_rx_ring_rd1 >= (sizeof(USB_Char_Rx1))){
 usb_rx_ring_rd1 = BEGINNING; // Circular buffer back to beginning
}
} 
}

//===========================================================================
// Function Name : transmitIOT
// Arguments: None
// Return: None 
// Called From:
//
// Globals: usb_tx_ring_wr 
// Locals: None
// 
// Description: Tranmits to IOT Serial Port 
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void transmitIOT(void){
  usb_tx_ring_wr = clear; 
  UCA0IE |= UCTXIE; 
}


//===========================================================================
// Function Name : receiveIOT
// Arguments: None
// Return: None 
// Called From: Main
//
// Globals: usb_rx_ring_wr, usb_rx_ring_rd, USB_Char_Rx, usb_tx_ring_wr, 
// usb_tx_ring_rd 
// Locals: i
// 
// Description: Initializes baud rate and MSP430 ports 
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void receiveIOT(void){
  int iotwr = usb_rx_ring_wr; 
  if (iotwr != usb_rx_ring_rd){
Processbuff_IOT[pb_wr_iot++] = USB_Char_Rx[usb_rx_ring_rd++] ;
 if (pb_wr_iot >= (sizeof(Processbuff))){
 pb_wr_iot = BEGINNING; // Circular buffer back to beginning
 }
 if (usb_rx_ring_rd >= (sizeof(USB_Char_Rx))){
 usb_rx_ring_rd = BEGINNING; // Circular buffer back to beginning
}
} 
}


//===========================================================================
// Function Name : parseData
// Arguments: char* string 
// Return: None
// Called From: Main
//
// Globals:  None
// Locals: i,y
// 
// Description: Checks if incoming message is a command and then finds location of 
// command description
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void parseData(char *string){
  
  for(int i = clear; i < SMALL_RING_SIZE ; i++){
    if(string[i] == '^'){
      recogCommand = positive;
      commandFound = i;
      i++;
      for(int y = clear; y < offsetMax ; y++){
        offset[y] = i; 
        i++;
        if(i > SMALL_RING_SIZE){
          i = clear; 
        }
      }
      }
    }
  }

//===========================================================================
// Function Name : checkPassword
// Arguments: char* string
// Return: None 
// Called From: Main
//
// Globals: None
// Locals: None
// 
// Description: checks if password is correct 
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
int checkPassword(char *string){
  if(string[clear] != '4'){
    return clear; 
  }
  if(string[digit2] != '2'){
    return clear; 
  }
  if(string[digit3] != '9'){
    return clear; 
  }
  if(string[digit4] != '7'){
    return clear; 
  }
  
  return positive; 
  
}

//===========================================================================
// Function Name : convertTime
// Arguments: *string
// Return: None 
// Called From: Main
//
// Globals: commTime
// Locals: None
// 
// Description: Converts incoming message into the parsed data and converts 
// to an integer value in order to be modified and messed with in main 
// 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================

void convertTime(char *string){
 commTime = hundo*(string[clear] - '0' );
 commTime = commTime + (Hammy*(string[positive] - '0'));
 commTime = commTime + (string[digit3] - '0');
// commTime = atoi(string); 
}





  
  


                               
                               

