# Autonomous Warehouse Inventory Assitance Robot (AGV)

This project aims to create a warehouse assistive robot controlled by a Raspberry Pi 3B and a Parallax Propeller multicore Microcontroller. The robot was designed to navigate the warehouse and identify defective and non-defective widgets in the warehouse using image processing to identify directional aids and Aruco tag markers to identify defective and non-defective inventory.

# Warehouse Layout
![warehouse layout](https://github.com/IJAMUL1/Warehouse-Inventory-Management-Robot/assets/60096099/f6ec4f6d-da96-4e24-85f9-ae792edc9d51)

# Robot Demo
<div style="text-align:center;">
    <img src="https://github.com/IJAMUL1/Warehouse-Inventory-Management-Robot/assets/60096099/c6173f7b-1845-4d30-968d-3258a48b0690" alt="Your Image Description">
</div>

## Table of Contents

- [Introduction](#introduction)
- [Project Requirements](#Project-requirements)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Setup Instructions](#setup-instructions)
- [Usage](#usage)

## Introduction

The project encompasses hardware integration, navigation, object identification, electrical connections, and control logic. It involves navigating a predefined map to assist warehouse management in widget identification. The project objectives include accurate line following, intersection detection, handling directional aids, managing widget stations, counting widgets, reaching the docking station, and displaying the total widget count. These objectives guide the robot's functionality.

## Project Requirements: 

The robot must:
- Utilizes two controllers (Raspberry Pi and Propeller Activity Board).
- Follow the path (black tape) until reaching position 'C3' on the warehouse layout.
- Detect and respond to directional aids at odd intersections to navigate to the correct widget station.
- Detect and count defective and non-defective widgets at each station using computer vision algorithms with a camera.
- Navigate through each section, detecting widget stations on both sides.
- Reach the docking station at the end of the course based on the direction indicated by the directional aid at 'C3'.
- Display the total count of defective and non-defective widgets upon reaching the docking station.

## Hardware Requirements

The hardware components required for the project include:
- Chassis and mechanical components
- Raspberry Pi 3B
- Raspberry Pi Camera
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

## Software Requirements

The software tools, library and frame work for this project include:
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
