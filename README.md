:Author: Chezter Pescadero Vargas, Mark Vincent Salupado

:Email: cheztervargas353@gmail.com

:Date: 25/08/2025

:Revision: v17.0

:License: GNU GPLv3

# Project: eM-Brace Codes

eMBrace is a wearable prototype designed to explore muscle activity monitoring and responsive support.  
The device integrates EMG-based sensing with dynamic actuation modules, providing both biofeedback and adaptive control.  
This repository contains the source code, schematics, and documentation required to replicate or extend the project.

## Step 1: Installation

1. Clone or download this repository to your local machine.  
2. Open the main `.ino` file in the Arduino IDE.  
3. Ensure the required libraries are installed (`Arduino.h`, `Wire.h`, `SPI.h`, etc.).  
4. Connect your development board via USB.  
5. Verify and upload the sketch.

## Step 2: Assemble the circuit

Follow the wiring connections in `layout.png`.  
All connections must be double-checked for polarity and voltage compatibility before powering the board.  

## Step 3: Load the code

Upload the sketch to your board via Arduino IDE.  
Once uploaded, open the Serial Monitor to confirm initialization messages and sensor readings.

### Folder structure

....
 eMBrace                  => Arduino sketch folder
  ├── eMBrace.ino         => main Arduino file
  ├── schematics.png      => circuit schematic diagram
  ├── layout.png          => breadboard/prototype layout
  └── ReadMe.adoc         => this file
....

### License

This thesis project is protected under the GNU General Public License v3.0 (GPLv3).
You may use and study this code freely, but any derivative works must be released under the same GPLv3 license. Full license terms available in LICENSE.

### Contributing

Contributions are welcome. Fork the repository and submit a pull request, or contact via GitHub issues for feature requests or bug reports.  

### BOM

|###
| ID | Part name                 | Part number | Quantity
| R1 | 10k Resistor              | Generic     | 10       
| R2 | 220Ω Resistor             | Generic     | 5        
| L1 | Red LED                   | Generic     | 5        
| A1 | Arduino Nano 33 IoT       | ABX00033    | 1        
| S1 | Surface EMG Electrodes    | Custom      | 3        
| M1 | Micro Servo Motor (SG90)  | SG90-001    | 2        
| M2 | Vibration Motor           | 310-102     | 1        
| C1 | Capacitor 100nF           | Generic     | 5        
| W1 | Jumper Wires              | Generic     | 20       
| B1 | Breadboard                | Generic     | 1        
| P1 | Li-Po Battery (3.7V, 500mAh) | LP-500    | 1        
|###

### Help

This document is written in the _AsciiDoc_ format.  
For more details:  
* http://www.methods.co.nz/asciidoc[AsciiDoc homepage]  
* http://powerman.name/doc/asciidoc[AsciiDoc cheatsheet]  
