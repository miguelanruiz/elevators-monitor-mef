
# Elevators Monitor MEF (Finite State Machine)

## Description
**Elevators Monitor MEF** synergizes cutting-edge software engineering with embedded systems, showcasing a sophisticated simulation of elevator operations using a Finite State Machine (FSM). This project uniquely combines a Qt-based application and an STM32F103C8T6 microcontroller, embodying advanced concepts in computer science and engineering.

### Key Components
1. **Qt Application**: Developed in C++, this application benefits from the language's robustness and versatility, making it ideal for high-performance GUI applications. C++ is renowned for its efficiency and control, crucial for real-time systems and complex simulations.

2. **STM Microcontroller**: This component utilizes the STM32F103C8T6, a microcontroller celebrated for its reliability in embedded systems. The microcontroller executes the FSM, managing the dynamics of elevator movements with precision.

## Technical Highlights
- **C++ and Embedded Systems**: The choice of C++ for the Qt application stems from its high performance and object-oriented capabilities, essential for developing complex GUI applications. The integration with the microcontroller highlights the versatile application of C++ in both software and embedded systems.

- **FSM Implementation**: The project employs a Finite State Machine, a concept fundamental in automata theory and computational models. FSMs are instrumental in representing sequential logic and controlling execution flow, making them ideal for simulating elevator operations. Reference: Hopcroft, J., Motwani, R., Ullman, J.D.: Introduction to Automata Theory, Languages, and Computation, 3rd ed. Pearson, Boston (2007).

- **Peripheral Synchronization**: Utilizing USART for communication, the system exemplifies complex synchronization requirements in embedded systems. This aspect underscores the importance of precise timing and resource management in microcontroller programming.

- **Real-Time Data Handling**: The implementation includes meticulous data management to ensure seamless real-time communication between the microcontroller and the Qt application, showcasing the advanced use of buffers and data streams. For an in-depth look at the microcontroller part of the project, please see the [STM Project Repository](https://github.com/miguelanruiz/elevators-mcu-stm32) on GitHub.


## Objectives
- To develop a technically advanced program that reflects state-of-the-art practices in software and embedded systems.
- To demonstrate the practical application of FSM in simulating real-world systems.
- To provide a comprehensive interface for visualizing and controlling the FSM-based elevator simulation.

## Practical Conclusions
- Communication protocols are optimized for each state, ensuring data integrity and real-time performance.
- A 34-byte buffer in Qt is strategically implemented to prevent reading errors and maintain data consistency.
- Detailed parameter definitions facilitate modular programming in the embedded system, allowing for flexible and scalable code architecture.

## References – Bibliography
1. Hopcroft, J., Motwani, R., Ullman, J.D.: Introduction to Automata Theory, Languages, and Computation, 3rd edn. Pearson, Boston (2007).
2. You, J. (2013). Software-based Finite State Machine (FSM) with general-purpose processors [PDF].
3. CRC Computation in C. Pololu. [Available here](https://www.pololu.com/docs/0J44/6.7.6)

## Annexes
**Annex 1.** Finite State Machine Diagram
![](./img/MEF.jpeg)
