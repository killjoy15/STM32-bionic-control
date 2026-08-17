# STM32 Bionic Finger Control

Simple motor control with two buttons on STM32.

## Control

- **Button 1** (PA0) → Motor Forward (hold)
- **Button 2** (PA1) → Motor Backward (hold)
- **Release** → Motor Stop

## GPIO Configuration

| Pin | Function |
|-----|----------|
| PA0 | Input - Button 1 (Pull-up) |
| PA1 | Input - Button 2 (Pull-up) |
| PB0 | Output - Motor IN1 |
| PB1 | Output - Motor IN2 |
| PB2 | Output - Motor Enable |

## Usage

1. Open project in STM32CubeIDE
2. Build and flash to your board
3. Connect motor driver as shown in `main.c`
4. Press and hold buttons to control motor

## Features

- Software debouncing
- Ready for STM32CubeIDE
- Simple and clean code
