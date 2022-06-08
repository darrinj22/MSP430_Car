//===========================================================================
// File Name : ports.c
//
// Description: initializes all ports on the MSP430
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
#include "macros.h" 
#include "functions.h" 
#include "msp430.h" 

//===========================================================================
// File Name : Init_Ports
//
// Description: initializes all ports 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void Init_Ports(void){
Init_Port1();
Init_Port2();
Init_Port3(USE_GPIO);
Init_Port4();
Init_Port5();
Init_Port6();
}

//===========================================================================
// File Name : Init_Port1
//
// Description: initializes  port 1 
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void Init_Port1(void){
//-------------------------------------------------------
// RED_LED (0x01) // 0 RED LED 0
// A1_SEEED (0x02) // 1 A1_SEEED
// V_DETECT_L (0x04) // 2 A2
// V_DETECT_R (0x08) // 3 A3
// V_BAT (0x10) // 4 A4
// V_THUMB (0x20) // 5 A5
// UCA0TXD (0x40) // 6 Back Channel UCA0TXD
// UCA0RXD (0x80) // 7 Back Channel UCA0RXD
//-------------------------------------------------------
 P1DIR = 0xFF; // Set P1 direction to output
 P1OUT = 0x00; // P1 set Low
 P1SEL0 &= ~RED_LED; // Set RED_LED as GP I/O
 P1SEL1 &= ~RED_LED; // Set RED_LED as GP I/O
 
 P1OUT |= RED_LED; // Set Red LED On
 P1DIR |= RED_LED; // Set Red LED to output
 P1SEL0 |= A1_SEEED; // ADC input for A1_SEEED
 P1SEL1 |= A1_SEEED; // ADC input for A1_SEEED
 P1SEL0 |= V_DETECT_L; // ADC input for V_DETECT_L
 P1SEL1 |= V_DETECT_L; // ADC input for V_DETECT_L
 P1SEL0 |= V_DETECT_R; // ADC input for V_DETECT_R
 P1SEL1 |= V_DETECT_R; // ADC input for V_DETECT_R
 P1SEL0 |= V_BAT; // ADC input for V_BAT
 P1SEL1 |= V_BAT; // ADC input for V_BAT
 P1SEL0 |= V_THUMB; // ADC input for V_THUMB
 P1SEL1 |= V_THUMB; // ADC input for V_THUMB
 
 P1SEL0 |= UCA0TXD; // UCA0TXD pin
 P1SEL1 &= ~UCA0TXD; // UCA0TXD pin
 
 
 P1SEL0 |= UCA0RXD; // UCA0RXD pin
 P1SEL1 &= ~UCA0RXD; // UCA0RXD pin
 
 //----------------------------------------------------
}

//==============================================================================
//==============================================================================
//===========================================================================
// File Name : Init_Port2
//
// Description: initializes  port 2
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void Init_Port2(void){
P2DIR = def_out; // Set P1 direction to output
P2OUT = def_low; // P1 set Low

P2SEL0 &= ~P2_0; // P2_0 GPIO operation
P2SEL1 &= ~P2_0; // P2_0 GPIO operation
P2DIR &= ~P2_0; // Direction = input

P2SEL0 &= ~P2_1; // P2_1 GPIO operation
P2SEL1 &= ~P2_1; // P2_1 GPIO operation
P2DIR &= ~P2_1; // Direction = input

P2SEL0 &= ~P2_2; // P2_2 GPIO operation
P2SEL1 &= ~P2_2; // P2_2 GPIO operation
P2DIR &= ~P2_2; // Direction = input

P2SEL0 &= ~SW2; // SW2 Operation
P2SEL1 &= ~SW2; // SW2 Operation
P2DIR &= ~SW2; // Direction = input
P2OUT |= SW2; // Configure pullup resistor
P2REN |= SW2; // Enable pullup resistor
 P2IES |= SW2; // P2.0 Hi/Lo edge interrupt
 P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
 P2IE |= SW2; // P2.6 interrupt enabled

P2SEL0 &= ~P2_4; // P2_4 GPIO operation
P2SEL1 &= ~P2_4; // P2_4 GPIO operation
P2DIR &= ~P2_4; // Direction = input

P2SEL0 &= ~P2_5; // P2_5 GPIO operation
P2SEL1 &= ~P2_5; // P2_5 GPIO operation
P2DIR &= ~P2_5; // Direction = input

P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
P2SEL1 |= LFXOUT; // LFXOUT Clock operation

P2SEL0 &= ~LFXIN; // LFXIN Clock operation
P2SEL1 |= LFXIN; // LFXIN Clock operation

}
//===========================================================
//===========================================================
//===========================================================================
// File Name : Init_Port3
//
// Description: initializes  port 3
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void Init_Port3(int x){
  P3DIR = def_out; // Set P1 direction to output 
  P3OUT = def_low; // P1 set Low 
  
  P3SEL0 &= ~TEST_PROBE;
  P3SEL1 &= ~TEST_PROBE;
  P3DIR  |= TEST_PROBE; 
    
  P3SEL0 |= CHECK_BAT; 
  P3SEL1 |= CHECK_BAT; 
  
  P3SEL0 |= OA2N; 
  P3SEL1 |= OA2N;
  
  P3SEL0 |= OA2P; 
  P3SEL1 |= OA2P;
  
  if(x == USE_SMCLK){
  P3SEL0 |= SMCLK_OUT; 
  P3SEL1 &= ~SMCLK_OUT;
  P3DIR  |= SMCLK_OUT; 
  }else{
    P3SEL0 &= ~SMCLK_OUT; 
  P3SEL1 &= ~SMCLK_OUT;
  P3DIR  |= SMCLK_OUT; 
  }
  P3SEL0 &= ~IR_LED;
  P3SEL1 &= ~IR_LED; 
  P3DIR  |= IR_LED; 
  P3OUT |= IR_LED;
  
  P3SEL0 &= ~IOT_LINK;
  P3SEL1 &= ~IOT_LINK;
  P3DIR  &= ~IOT_LINK; // p3.6 input 
  P3OUT &= ~IOT_LINK; // initial condition 0
  
  P3SEL0 &= ~P3_7;
  P3SEL1 &= ~P3_7;
  P3DIR  &= ~P3_7; 
  
}


//==============================================================================
//==============================================================================

//===========================================================================
// File Name : Init_Port4
//
// Description: initializes  port 4
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void Init_Port4(void){
//------------------------------------------------------------------------------
// Configure PORT 4
P4DIR = def_out; // Set P1 direction to oitput
P4OUT = def_low; // P1 set Low

P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
P4DIR |= RESET_LCD; // Set RESET_LCD direction to output
P4OUT |= RESET_LCD; // Set RESET_LCD Off [High]

P4SEL0 &= ~SW1; // SW1 GPIO operation
P4SEL1 &= ~SW1; // SW1 GPIO operation
P4DIR &= ~SW1; // Direction = input
P4OUT |= SW1; // Configure pullup resistor
P4REN |= SW1; // Enable pullup resistor
P4IES |= SW1; // P2.0 Hi/Lo edge interrupt
P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
P4IE |= SW1; // P2.6 interrupt enabled

P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation


P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation


P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output
P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]

P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation

P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation

P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation

}

//=============================================================================
//=============================================================================
//===========================================================================
// File Name : Init_Port5
//
// Description: initializes  port 5
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void Init_Port5(void){
  P5DIR = def_out; // Set P1 direction to output 
  P5OUT = def_low; // P1 set Low 
  
  P5SEL0 &= ~IOT_RESET; 
  P5SEL1 &= ~IOT_RESET;
  P5DIR  |= IOT_RESET; // P5.0 output
  P5OUT &= ~IOT_RESET; // initial condition 0 
 
  
  P5SEL0 &= ~V_BAT; 
  P5SEL1 &= ~V_BAT;
  P5DIR  &= ~V_BAT;
  
  P5SEL0 &= ~IOT_PROGRAM_SELECT; 
  P5SEL1 &= ~IOT_PROGRAM_SELECT; 
  P5DIR  &= ~IOT_PROGRAM_SELECT; // p5.2 input
  
  P5SEL0 &= ~V_33; 
  P5SEL1 &= ~V_33;
  P5DIR  &= ~V_33; 
  
  P5SEL0 &= ~IOT_PROGRAM_MODE; 
  P5SEL1 &= ~IOT_PROGRAM_MODE;
  P5DIR  &= ~IOT_PROGRAM_MODE; // p5.4 input 
  
}

//=============================================================================
//=============================================================================
//===========================================================================
// File Name : Init_Port6
//
// Description: initializes  port 6
//
// Author: DJ Hansen 
// Date: April 2020
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================
void Init_Port6(void){
  P6DIR = def_out; // Set P1 direction to output 
  P6OUT = def_low; // P1 set Low 
  
  P6SEL0 |= R_FORWARD;
  P6SEL1 &= ~R_FORWARD; 
  P6DIR  |= R_FORWARD; 
   
    
  P6SEL0 |= L_FORWARD;
  P6SEL1 &= ~L_FORWARD; 
  P6DIR  |= L_FORWARD; 
 
  
  P6SEL0 |= R_REVERSE;
  P6SEL1 &= ~R_REVERSE; 
  P6DIR  |= R_REVERSE; 
  
  P6SEL0 |= L_REVERSE;
  P6SEL1 &= ~L_REVERSE; 
  P6DIR  |= L_REVERSE; 
  
  P6SEL0 &= ~LCD_BACKLITE;
  P6SEL1 &= ~LCD_BACKLITE;
  P6DIR  |= LCD_BACKLITE;
  P6OUT &= ~LCD_BACKLITE; 
  
  P6SEL0 &= ~P6_5;
  P6SEL1 &= ~P6_5; 
  
  P6SEL0 &= ~GRN_LED;
  P6SEL1 &= ~GRN_LED;
  P6DIR  |= GRN_LED;
  
  
  
}


