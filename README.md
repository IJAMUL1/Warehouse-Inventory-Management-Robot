# Autonomous Warehouse Inventory Assitance Robot (AGV)

This project aims to create a warehouse assistive robot controlled by a Raspberry Pi 3B and a Parallax Propeller multicore Microcontroller. The robot was designed to navigate the warehouse and identify defective and non-defective widgets in the warehouse using image processing to identify directional aids and Aruco tag markers to identify defective and non-defective inventory.

# Warehouse Layout
![warehouse layout](https://github.com/IJAMUL1/Warehouse-Inventory-Management-Robot/assets/60096099/f6ec4f6d-da96-4e24-85f9-ae792edc9d51)

# Robot Demo
![Untitled video - Made with Clipchamp (1)](https://github.com/IJAMUL1/Warehouse-Inventory-Management-Robot/assets/60096099/c6173f7b-1845-4d30-968d-3258a48b0690)

## Table of Contents

- [Introduction](#introduction)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Setup Instructions](#setup-instructions)
- [Usage](#usage)
- [Contributing](#contributing)

## Introduction

The project encompasses hardware integration, navigation, object identification, electrical connections, and control logic. It involves navigating a predefined map to assist warehouse management in widget identification. The project objectives include accurate line following, intersection detection, handling directional aids, managing widget stations, counting widgets, reaching the docking station, and displaying the total widget count. These objectives guide the robot's functionality.

## Hardware Requirements

The hardware components required for the project include:
- Chassis and mechanical components
- Raspberry Pi 3B
- Raspberry PI Camera
- Parallax Propeller microcontroller
- Aruco Tag Markers
- 2 x Continous Servo Motors
- Pulolo Reflecance Sensor
- 2 x Ultrasonic Sensors
- Parallax 2 X 16 Serial LCD With Piezo Speaker 
- Power supply
- Breadboard
- Wires
- Leds
- Etc.

## Software Requirements

Specify all the software dependencies needed to run the project, including but not limited to:
- Parallax Propeller Toolchain
- SimpleIDE or PropellerIDE for development
- Propeller C libraries (simpletools, servo, ping)
- Raspbian OS
- Python 3.9 installed on the Raspberry Pi
- Python Library (OpenCv, Numpy)
- RPi.GPIO library for controlling GPIO pins (RPi.GPIO)

## Setup Instructions
# Raspberry Pi Setup
- Connect the camera module to the Raspberry Pi.
- Install Python 3.x on the Raspberry Pi if not already installed.
- Install OpenCV and NumPy libraries for Python on the Raspberry Pi.
- Install the RPi.GPIO library for controlling GPIO pins.
- Clone or download the project repository to the Raspberry Pi.
- Connect the GPIO pins to external devices such as LEDs and motor drivers as per the circuit diagram provided.
- Adjust the circuit connections and GPIO pin configurations in the code based on your use case.

# Parallax Properller Setup
- Connect the Parallax Propeller microcontroller to your computer.
- Install the Parallax Propeller Toolchain and SimpleIDE or PropellerIDE.
- Clone or download the project repository to local device.
- Open the project in SimpleIDE or PropellerIDE.
- Compile and upload the properller code to the Parallax Propeller microcontroller.

# Integration
- Connect raspberry pi to properller based on pin connection in code files respectively. 

## Usage

Once the code is uploaded to the microcontroller and the hardware is assembled, follow these steps to use the robot:

- Power on the robot.
- The robot will perform initialization routines, including sensor calibration.
- Depending on the mode of operation, the robot will perform tasks such as line following, obstacle avoidance, or intersection handling.
- Monitor the status LEDs to understand the system's behavior.
- Refer to the code documentation for specific functionality and control options.

## Contributing

Include guidelines for contributing to the project, such as how to report bugs, submit patches, or suggest improvements. Mention any coding standards or conventions to follow.
