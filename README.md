# eM-Brace Codes

**Author:** Chezter Pescadero Vargas, Mark Vincent Salupado  
**Email:** cheztervargas353@gmail.com  
**Date:** 25/08/2025  
**Version:** v17.0  
**License:** GNU General Public License v3.0 (GPLv3)

## Overview

Carpal Tunnel Syndrome (CTS) is a prevalent musculoskeletal disorder caused by median nerve compression, leading to pain, numbness, and weakened grip strength. Conventional wrist splints often restrict wrist motion and lack therapeutic functions that promote recovery.

The **eM-Brace** is an autonomous wrist splint that integrates a surface electromyography (sEMG)-activated myofascial release massage system. The device detects rest conditions through sEMG sensors positioned on the Abductor Pollicis Brevis muscle, triggering the massage mechanism only when the wrist is inactive.

### Key Features

- **Integrated Massager:** Calibrated to deliver 1.36 kPa of therapeutic pressure
- **Auto-Fit Module:** Maintains consistent support pressure of approximately 3.68 kPa
- **Motion Support Module:** Loosens during activity, allowing up to 10° flexion and 30° extension
- **sEMG-Based Activation:** Intelligent muscle state detection for targeted relief

### Clinical Results

Functional testing verified **100% accuracy** in classifying muscle states and **80% accuracy** in delivering target pressure. In beta testing with 15 participants subjected to induced CTS symptoms:
- **73%** showed grip strength improvements exceeding 2.2 kg
- **Mean pain scores** dropped from 3.27 to 0.33

The eM-Brace demonstrates a lightweight, non-invasive, and adaptive alternative to static splints.

### Keywords

Carpal Tunnel Syndrome, sEMG, Myofascial Release, Wrist Splint, Rehabilitation

## Quick Start

### Step 1: Installation

1. Clone or download this repository to your local machine.
2. Open the main `.ino` file in the Arduino IDE.
3. Ensure the required libraries are installed (`Arduino.h`, `Wire.h`, `SPI.h`, etc.).
4. Connect your development board via USB.
5. Verify and upload the sketch.

### Step 2: Assemble the Circuit

Follow the wiring connections in `layout.png`. All connections must be double-checked for polarity and voltage compatibility before powering the board.

### Step 3: Load the Code

Upload the sketch to your board via Arduino IDE. Once uploaded, open the Serial Monitor to confirm initialization messages and sensor readings.

## Project Structure
```
eM-Brace/
├── eM-Brace.ino         # Main Arduino sketch
├── schematics.png       # Circuit schematic diagram
├── layout.png           # Breadboard/prototype layout
├── README.md            # This file
└── BOM.md               # Bill of Materials
```

## Bill of Materials

| ID | Part Name | Part Number | Quantity |
|----|-----------|-------------|----------|
| R1 | 10k Resistor | Generic | 10 |
| R2 | 220Ω Resistor | Generic | 5 |
| L1 | Red LED | Generic | 5 |
| A1 | Arduino Nano 33 IoT | ABX00033 | 1 |
| S1 | Surface EMG Electrodes | Custom | 3 |
| M1 | Micro Servo Motor (SG90) | SG90-001 | 2 |
| M2 | Vibration Motor | 310-102 | 1 |
| C1 | Capacitor 100nF | Generic | 5 |
| W1 | Jumper Wires | Generic | 20 |
| B1 | Breadboard | Generic | 1 |
| P1 | Li-Po Battery (3.7V, 500mAh) | LP-500 | 1 |

## License

This project is released under the **GNU General Public License v3.0 (GPLv3)**.

You are free to:
- Use this code for any purpose
- Study and modify the code
- Distribute modified versions

**Provided that you:**
- Include the original copyright notice
- Disclose your modifications
- Release derivative works under GPLv3

For the complete license text, see the [LICENSE](LICENSE) file in this repository.

## Contributing

Contributions are welcome! You can:
- Fork the repository and submit a pull request
- Open GitHub issues for feature requests or bug reports
- Contact via email for questions

## Resources

- [Arduino IDE Documentation](https://docs.arduino.cc/)
- [MyoWare sEMG Sensor Advanced Guide](https://myoware.com/wp-content/uploads/2022/03/MyoWare_v2_AdvancedGuide-Updated.pdf)
- [ESP32 WROOM Pinout & Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf)
- [Carpal Tunnel Syndrome Information](https://www.mayoclinic.org/diseases-conditions/carpal-tunnel-syndrome/)

---

*For questions or feedback, please open an issue or contact the author.*
