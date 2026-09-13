# Arduino Pulse-Induction Metal Detector

A simple metal detector built with an Arduino Nano, a hand-wound coil, and a handful of passive components. It detects nearby metal objects by measuring changes in the discharge time of a capacitor charged through the coil, and gives feedback via a buzzer and LED.

<img width="1126" height="680" alt="Metal-Detector-using-Arduino-circuit-diagram" src="https://github.com/user-attachments/assets/93f0dc58-ddae-436b-a3c0-db41cb859c2e" />


## How it works

The coil (L1) and a capacitor form an RLC circuit. The Arduino repeatedly:
1. Discharges the capacitor and sends a short pulse through the coil.
2. Reads the resulting analog voltage on the capacitor pin (256 samples per cycle, with min/max spike rejection for noise reduction).
3. Compares the running average against the current reading — when metal is near the coil, it changes the coil's electromagnetic field and shifts the discharge curve.
4. Converts the deviation into a buzzer tone/LED signal: higher pitch for one direction of change, lower pitch for the other.

## Hardware

- Arduino Nano
- Hand-wound search coil (~5 m of enameled copper wire)
- 1N4148 diode
- 330 Ω and 1 kΩ resistors
- 10 nF capacitor
- Piezo buzzer
- LED
- 9V battery
- PVC pipe enclosure for the coil housing

## Build photos

| Breadboard prototype | Hand-wound coil | Final enclosure |
|---|---|---|
| <img width="3024" height="4032" alt="20231216_235302" src="https://github.com/user-attachments/assets/4934ece4-a0e6-4471-9958-235110fad47b" /> | <img width="3024" height="4032" alt="civka" src="https://github.com/user-attachments/assets/4eebb0d4-f6b0-4f0d-992e-6eb5313c7bd0" /> | <img width="230" height="391" alt="Snímek obrazovky 2023-12-17 002719" src="https://github.com/user-attachments/assets/e6345b9d-0b84-44d8-a690-22c5b96f59dc" /> |

## Result

A working handheld pulse-induction detector that reliably signals nearby metal objects through audible tone changes, housed in a repurposed PVC pipe enclosure.

## Credits / sources

This project was built as a personal learning project, based on and adapted from:
- Circuit design reference: [CircuitDigest — Arduino Metal Detector](https://circuitdigest.com/microcontroller-projects/arduino-metal-detector-circuit-code)
- Concept inspiration: [Arduino Blog — Minimal metal detector with a coil of wire](https://blog.arduino.cc/2020/10/21/minimal-metal-detector-made-with-an-arduino-and-a-coil-of-wire/)

## Author

Matej Dynda
