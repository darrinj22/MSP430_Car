
//===========================================================================
// File Name : serial_interupt
//
// Description: ISR's used to interrupt main whenever a message is received 
// or transmitted through the IOT or USB 
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
extern char *display[numLines];

extern volatile unsigned char display_changed;

extern volatile unsigned int usb_rx_ring_wr; 
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_tx_ring_wr; 
extern volatile unsigned int usb_tx_ring_rd; 

extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx[LARGE_RING_SIZE];

extern char receiveChar[SMALL_RING_SIZE]; 

extern volatile unsigned int usb_rx_ring_wr1; 
extern volatile unsigned int usb_rx_ring_rd1;
extern volatile unsigned int usb_tx_ring_wr1; 
extern volatile unsigned int usb_tx_ring_rd1; 

extern volatile char USB_Char_Rx1[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx1[LARGE_RING_SIZE];


extern int UCA0_index = clear;
extern char test_command[testLength] = "NCSU ROCKS";
extern char test_command1[testLength] = "NCSU ROCKS"; 
extern int UCA1_index = clear; 
extern char ncsu[numChars]; 
extern char ncsu1[numChars];
extern char receiveChar[SMALL_RING_SIZE]; 
extern int gtg = clear; 
extern char transmit_array_A1[SMALL_RING_SIZE]; 
char transmit_array_A0[SMALL_RING_SIZE]; 
extern int gotMessage = clear;
extern int gotMessage1 = clear; 
extern int framCommand = clear;
extern int message = clear; 
extern int message1 = clear; 
extern int newVar = clear;
extern int ipAddressFound = clear; 

extern int wait_2_transmit = clear;
extern int wait_2_transmit_USB = clear; 
extern char Processbuff[SMALL_RING_SIZE];
extern char Processbuff_IOT[SMALL_RING_SIZE];

int setUp = clear; 
int setUp1 = clear;
int setUp2 = clear; 
int parsethedata=clear;
extern char IPADDRESS[SMALL_RING_SIZE];
int IPPTR = clear; 
extern int bootUpDone; 
extern int doneIP; 
extern int readyPort;  
extern char connectPort[20];
extern char getInfo[15];
extern char keepConnect[23]; 
extern int sentCommand = positive; 
extern int alreadyDone = clear; 
extern int keepConnectFlag; 
extern int keepConnectIE; 

//===========================================================================
// File Name : eUSCI_A0_ISR 
//
// Description:  IOT ISR 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
//------------------------------------------------------------------------------
#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
char temp;
int temporary; 
//unsigned short backDoor; 
//unsigned int tempRead; 
switch(__even_in_range(UCA0IV,endCase)){
case noInt: // Vector 0 - no interrupt
break;
case ReceiveCase: // Vector 2 – RXIFG
 //wait_2_transmit = positive;
  
  if(setUp == clear){
    temp = UCA0RXBUF;
    if((setUp1 == clear) && (setUp2 == clear))
    {
      if(temp == 'r')
      {
        setUp1 = positive; 
      }
    }else if((setUp1 == positive) && (setUp2 == clear))
    {
      parsethedata++; 
      if(parsethedata == positive)
      {
        if(temp == '=')
        {
          setUp2 = positive; 
          parsethedata = clear; 
        }
      }else{
        setUp1 = clear;
        parsethedata = clear; 
      }
    }else{
      if(temp != ' ')
      {
        IPADDRESS[IPPTR] = temp;
        IPPTR++;
      }else if(temp == ' ')
      {
        IPADDRESS[IPPTR] = '\0'; 
        setUp = positive; 
      }
    }
    UCA1TXBUF = temp;
  }else{
    temporary = usb_rx_ring_wr++;

USB_Char_Rx[temporary] = UCA0RXBUF; // RX -> USB_Char_Rx character
if (usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
}
temp = UCA0RXBUF;
UCA1TXBUF = temp;
 if(UCA0RXBUF == '\n'){
 gotMessage = positive; 
 newVar = positive; 
 }
    
  }

break;
case TransmitCase: 
   if(bootUpDone){
    UCA0TXBUF = getInfo[UCA0_index];
    UCA0_index++;
    if(getInfo[UCA0_index] == nullChar){
      bootUpDone = clear; 
      UCA0_index = clear;
      UCA0IE &= ~UCTXIE; 
      alreadyDone = positive; 
      keepConnectFlag = positive; 
    }
  }
  if(readyPort){
    UCA0TXBUF = connectPort[UCA0_index];
    UCA0_index++;
    if(connectPort[UCA0_index] == nullChar){
      readyPort = clear; 
      UCA0_index = clear; 
      UCA0IE &= ~UCTXIE; 
      sentCommand = clear; 
    }
  }
  if(keepConnectIE){
    UCA0TXBUF = keepConnect[UCA0_index];
    UCA0_index++;
    if(keepConnect[UCA0_index] == nullChar){
      keepConnectIE = clear; 
      UCA0_index = clear; 
      UCA0IE &= ~UCTXIE; 
      sentCommand = clear; 
    }
  }
  /*
 UCA0TXBUF = Processbuff[usb_tx_ring_wr++];
if (Processbuff[usb_tx_ring_wr] == NULL){
UCA0IE &= ~UCTXIE;
}*/
  
  
  break;
default: break; 
}
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//===========================================================================
// File Name : eUSCI_A1_ISR
//
// Description: USB ISR serial communications 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
unsigned int temp1;

//unsigned short backDoor1; 
switch(__even_in_range(UCA1IV,endCase)){
case noInt: // Vector 0 - no interrupt
break;
case ReceiveCase: // Vector 2 – RXIFG
  //wait_2_transmit_USB = positive;
temp1 = usb_rx_ring_wr1++;
USB_Char_Rx1[temp1] = UCA1RXBUF; // RX -> USB_Char_Rx character

if (usb_rx_ring_wr1 >= (sizeof(USB_Char_Rx1))){
usb_rx_ring_wr1 = BEGINNING; // Circular buffer back to beginning
}
if(USB_Char_Rx1[temp1] == '.'){
 framCommand = positive; 
 message1 = started; 
}



if(message1 == started){
  switch(gotMessage1){
    case 0:
      if(USB_Char_Rx1[temp1] == '\r'){
       gotMessage1 = positive; 
      }
      break; 
  default:
    break;
  }
  
}

if(USB_Char_Rx1[temp1] != '^'){
  wait_2_transmit_USB = positive; 
}

UCA0TXBUF = USB_Char_Rx1[temp1]; 

//backDoor1 = UCA1RXBUF;
//UCA1TXBUF = backDoor1;

break;
case TransmitCase:
 
  /*
  if(wait_2_transmit_USB == positive){
UCA1TXBUF = transmit_array_A1[usb_tx_ring_wr1++];
if (transmit_array_A1[usb_tx_ring_wr1] == NULL){
UCA1IE &= ~UCTXIE;
}
//gotMessage1 = clear;
wait_2_transmit_USB = clear; 
  }
*/
break;
default: break; 

}
}
//------------------------------------------------------------------------------