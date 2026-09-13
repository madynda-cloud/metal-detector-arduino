# Arduino Pulse-Induction Metal Detector

A simple metal detector built with an Arduino Nano, a hand-wound coil, and a handful of passive components. It detects nearby metal objects by measuring changes in the discharge time of a capacitor charged through the coil, and gives feedback via a buzzer and LED.

![Circuit diagram](docs/circuit-diagram.png)

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
| ![Breadboard](docs/breadboard-build.jpg) | ![Coil](docs/hand-wound-coil.jpg) | ![Enclosure](docs/enclosure.png) |

## Code

[`detektor_2_0.ino`](detektor_2_0.ino) — the full Arduino sketch.

## Result

A working handheld pulse-induction detector that reliably signals nearby metal objects through audible tone changes, housed in a repurposed PVC pipe enclosure.

## Credits / sources

This project was built as a personal learning project, based on and adapted from:
- Circuit design reference: [CircuitDigest — Arduino Metal Detector](https://circuitdigest.com/microcontroller-projects/arduino-metal-detector-circuit-code)
- Concept inspiration: [Arduino Blog — Minimal metal detector with a coil of wire](https://blog.arduino.cc/2020/10/21/minimal-metal-detector-made-with-an-arduino-and-a-coil-of-wire/)

## Author

Matej Dynda — [LinkedIn](https://linkedin.com/in/matej-dynda)
