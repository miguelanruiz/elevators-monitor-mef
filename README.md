# STM32 Elevators Monitor System

## Overview
Diving deep into the world of real-time systems, the STM32 Elevators Monitor System stands as a testament to the agility and robustness of embedded systems engineering. This project is a masterful blend of precision timing, intricate USB UART communication, and the versatile prowess of C programming, all combined to create a system that not only manages elevator logistics but does so with the assurance of scalability and reliability.

## Core Features

### Precise Time Management
At the heart of this system lies the nuanced timing mechanism, ensuring millisecond precision. With timers meticulously calibrated to a 32 MHz clock and a 16-bit value of 35999, each tick is a step in synchronized perfection, further refined by an internal `TIME_STEP`.

### USB UART Communication
The USB UART interface serves as the system's communication backbone, enabling seamless data transfer with the Qt application. This integration showcases the seamless bridging of low-level hardware control with high-level application management.

### Data Integrity with CRC-8
To fortify communication against errors, a CRC-8 checksum adds a layer of data integrity, ensuring that each command and status report is as accurate as it is reliable.

### Advanced Data Structures
The software architecture employs comprehensive data structures, bringing order and clarity to the complex state management of multiple elevators. This structure is further augmented by `__weak` methods, paving the way for effortless data deserialization.

### Scalability
Designed with future growth in mind, the system architecture allows for the introduction of additional elevators without the need for a fundamental redesign. This inherent scalability signifies a project ready to evolve with every new requirement.

## Technical Specifications

- **Microcontroller Configuration**: Based on CubeIDE version 1.8.0, the system is initialized with the crystal oscillator set to the rising edge, harnessing the full potential of the STM32 microcontroller.
- **Operational Oscillator**: Utilizes the HSE (High-Speed External) oscillator, ensuring stable and precise clock signals for the MCU's operations.
- **Communication Protocols**: Implements UART over USB with a 48 MHz clock, conforming to the stringent specifications outlined in the microcontroller's datasheet.
- **Peripheral Utilization**: The microcontroller's native ADCs and DMAs stand ready for integration, hinting at a system that can transcend beyond its current capabilities.

## Potential Expansions

- **Analog to Digital Conversion**: With onboard ADCs, the system is ripe for applications requiring sensor integration, expanding its reach into domains like environmental monitoring within elevator cabins.
- **Direct Memory Access**: The incorporation of DMA can elevate the system's efficiency, allowing for direct data transfers that bypass the CPU, optimizing resource usage.
- **Real-Time Operating Systems**: For those looking to push the boundaries, the microcontroller's compatibility with FreeRTOS offers a foray into multitasking, resource management, and real-time task scheduling.

## Getting Started

Clone this repository and ensure that your development environment matches the CubeIDE version 1.8.0 or later. Follow the setup instructions to configure the crystal oscillator and UART settings to align with your hardware specifications.

## Contributing

Contributors are invited to enrich the system's capability, whether it be through the integration of additional hardware features, the refinement of real-time operations, or the enhancement of the system's core functionality. Your contributions will be part of a collaborative effort to advance the field of embedded systems.

## Acknowledgements

This project owes its inception to the vibrant community surrounding STM32 and the invaluable resources provided by STMicroelectronics. The open-source nature of this endeavor is a tribute to the collective wisdom and spirit of innovation that propels the world of embedded systems forward.

Join us in this journey of embedded excellence, where precision, reliability, and scalability converge to create not just a system, but a cornerstone of technological advancement.

