# MSP430_Car
Remote control car built from scratch using an MSP430FR2355. 

## Introduction

This car was built in a semester long project using an [MSP430FR2355.](https://linktodocumentation) All configuration and 
programming was done by me unless otherwise stated within the files of the project. Projection includes configuration of clocks, timers, interrupts,
internet connectivity, PWM controller, ADC converters, and other peripherals/sensors. At the end of the project,
the car was capable of being controlled via a remote control that was programmed to send commands to a TCP telnet terminal. The car is also programmed to be able to follow a black line course using UV sensors. 

## Browsing this Repository 
The .eww file contained on the home screen of this repository and is the main project file for use of this project with the IAR IDE. The other files (.ewt,.ewp,.ewd) are project and debug files. 
The Compiled folder contains a single file used for configuration of the LCD display. 
By clicking into the Source folder, be sure to view the following noteworthy files: 

* [main.c](https://github.com/darrinj22/MSP430_Car/blob/main/Source/main.c)
    * This is the main program. It initializes the configuration of ports, clocks, conditions, timers, LCD Screen and Serial functionality. It also contains a state machine that executes various tests on the system, including internet connectivity, driving, reversing, turning, and following lines.
* [macros.h](https://github.com/darrinj22/MSP430_Car/blob/main/Source/macros.h)
    * An exhaustive effort to remove all "magic numbers" from the program by utilizing macros. 
* [serial_interrupt.c](https://github.com/darrinj22/MSP430_Car/blob/main/Source/serial_interrupt.c)
    * Writing this file took a large development effort. There was a lot of learning how internet and data transfer protocols work and how to send and receive data both locally and over wifi. By implementing a ring buffer, I was able to receive and parse a large set of incoming data.
* [clocks.c](https://github.com/darrinj22/MSP430_Car/blob/main/Source/clocks.c)
    * This was the first time that I understood fully how to implement code based purely off of a datasheet. By studying and identifying what functionality I wanted my system to have, I was able to configure the clocks on the MSP430 to run at my desired speeds. 

## Setup 
This project was developed using the [IAR Embedded Workbench IDE](https://www.iar.com/products/architectures/arm/iar-embedded-workbench-for-arm/). Setup and install this IDE according to the documentation in the link.


