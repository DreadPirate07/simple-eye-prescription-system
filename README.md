# Smart Eye Prescription Device

## Overview

The Smart Eye Prescription Device is an innovative, simplified approach to estimating eyeglass prescriptions. This project uses an 8051 microcontroller, an ultrasonic sensor, and an LCD display to measure distance and calculate a basic prescription value. While not a replacement for professional eye exams, this device demonstrates a novel concept in accessible eye care technology.

## Features

- Ultrasonic distance measurement
- Real-time prescription calculation
- LCD display of calculated prescription
- Compact and portable design

## Schematic 
![Schematic](https://github.com/DreadPirate07/simple-eye-prescription-system/blob/main/image.png)

## Hardware Requirements

- 8051 microcontroller
- Ultrasonic sensor (e.g., HC-SR04)
- 16x2 LCD display
- Power supply
- Necessary connecting wires and resistors

## Software Requirements

- 8051 C compiler (e.g., Keil µVision)
- Programmer for 8051 microcontroller

## How It Works

1. The ultrasonic sensor measures the distance to the user's eye.
2. The microcontroller calculates a simplified prescription based on this distance.
3. The calculated prescription is displayed on the LCD in the format "-XX.XX".

## Setup and Usage

1. Connect the hardware components according to the pin configurations in the code.
2. Compile and upload the code to the 8051 microcontroller.
3. Power on the device.
4. Position the device at a suitable distance from the user's eye.
5. Read the displayed prescription value.

## Limitations

This device uses a simplified model to estimate prescriptions and should not be considered a substitute for professional eye examinations. It is intended as a proof-of-concept or educational tool to explore innovative approaches in eye care technology.

## Future Improvements

- Implement more sophisticated prescription calculation algorithms
- Add calibration features for improved accuracy
- Integrate with a mobile app for data logging and analysis

## Disclaimer

This device is not a medical instrument and should not be used for diagnostic purposes. Always consult with a qualified eye care professional for accurate prescriptions and eye health assessments.

