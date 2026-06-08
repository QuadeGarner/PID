# STM32 Motor Control Platform & Telemetry Dashboard

A telemetry-driven embedded control platform that combines real-time motor simulation, PID control, bidirectional UART communication, and live desktop visualization.

The project consists of two integrated systems:

* Embedded firmware running on an STM32 Nucleo-F103RB microcontroller
* A JavaFX desktop application for telemetry visualization, runtime tuning, and performance analysis

The platform was developed to explore many of the challenges found in real embedded control systems, including closed-loop control, serial communication reliability, parser synchronization, telemetry streaming, timing management, and system stability.

---

# Why This Project Matters

Many control-system projects stop at simulation.

This project extends beyond simulation by implementing a complete desktop-to-firmware communication pipeline capable of:

* Runtime PID tuning
* Live telemetry streaming
* Stateful packet parsing
* Embedded command processing
* Real-time performance visualization
* Firmware and desktop synchronization

The result is a complete embedded control platform that demonstrates both control-system fundamentals and embedded software architecture.

---

# Key Features

## Real-Time Control System

* Real-time PID controller implementation
* Runtime adjustable kP, kI, and kD gains
* Integral anti-windup protection
* Exponential moving average derivative filtering
* Output saturation and clamping
* Closed-loop motor position control
* Runtime control parameter updates

## Physical System Simulation

The simulated plant models realistic physical behavior including:

* Inertia
* Damping
* Friction
* Actuator limitations
* Saturation effects

System behavior is updated through numerical integration to approximate real-world motion.

## Telemetry & Visualization

* Live telemetry streaming
* Real-time graph rendering
* Target position tracking
* Motor position tracking
* Controller output visualization

Performance metrics include:

* Rise Time
* Overshoot
* Settling Time

## Embedded Communication Pipeline

* Bidirectional UART communication
* Runtime parameter updates from desktop application
* Embedded telemetry generation
* Custom packet protocol
* Stateful parser implementation
* Packet validation
* Parser resynchronization
* Malformed packet recovery

---

# System Architecture

## Desktop Application (Java / JavaFX)

The desktop application is responsible for:

* Telemetry visualization
* Runtime graphing
* PID tuning
* Serial communication
* Performance analysis

### Core Components

#### SerialDashboard

Main application entry point responsible for:

* UI lifecycle
* Communication initialization
* Dashboard coordination

#### GraphPane

Provides:

* Real-time graph rendering
* Position tracking visualization
* Controller output visualization

#### DataCalculations

Calculates:

* Rise time
* Settling time
* Overshoot
* Additional control metrics

#### SerialParser

Responsible for:

* Telemetry packet parsing
* Data validation
* DTO generation

#### CommandPane

Responsible for:

* Runtime gain adjustment
* Command packet generation

---

## Embedded Firmware (STM32)

The firmware is organized into independent subsystems with clearly defined responsibilities.

### MotionCoordinator

Coordinates:

* Control loop execution
* Telemetry generation
* System updates

### PIDController

Responsible for:

* Error calculation
* Integral accumulation
* Derivative filtering
* Control output generation

### VirtualMotor

Models:

* System dynamics
* Position updates
* Force response

### PacketParser

Responsible for:

* Byte-by-byte packet parsing
* Packet assembly
* Validation
* Error detection
* Parser resynchronization

### SerialManager

Responsible for:

* UART communication
* Data transport
* Serial interface abstraction

### TelemetryManager

Responsible for:

* Telemetry packet generation
* Runtime data transmission

---

# UART Communication Protocol

## Command Packet Format

Desktop-to-Firmware communication:

```text
$target,kP,kI,kD
```

Example:

```text
$500,0.65,0.10,0.25
```

The command parser performs:

* Packet framing
* Field validation
* Range checking
* Timeout detection
* Parser recovery

---

## Telemetry Packet Format

Firmware-to-Desktop communication:

```text
target,error,lastError,currentPosition,kP,kI,kD,percentComplete,output
```

Example:

```text
500.0,25.4,26.8,474.6,0.65,0.10,0.25,94.9,0.72
```

Telemetry is streamed continuously during controller execution.

---

# Engineering Challenges Solved

## UART Synchronization

Implemented a stateful parser capable of:

* Processing streaming serial data
* Recovering from malformed packets
* Maintaining synchronization after communication errors

## Runtime Control Tuning

Designed a communication protocol that allows:

* Live gain updates
* Continuous telemetry streaming
* Runtime controller adjustment without restarting firmware

## Embedded Debugging

Migrated development from Arduino Uno to STM32 to support:

* ST-LINK debugging
* Breakpoint-based analysis
* Runtime inspection
* Improved development workflow

## Communication Reliability

Investigated and resolved:

* Packet corruption
* Parser desynchronization
* Serial buffering issues
* Runtime synchronization problems

---

# Technologies Used

## Embedded

* STM32 Nucleo-F103RB
* C++
* STM32 Arduino Framework
* UART Communication
* ST-LINK Debugging

## Desktop

* Java
* JavaFX
* jSerialComm

## Engineering Concepts

* Embedded Systems
* Real-Time Software
* PID Control
* Numerical Integration
* UART Protocol Design
* Telemetry Systems
* Streaming Parser Design
* State Machines
* Fault Detection
* Software Architecture

---

# Current Status

Implemented and operational:

* STM32 firmware platform
* Real-time PID controller
* Physical system simulation
* JavaFX telemetry dashboard
* Bidirectional UART communication
* Runtime PID tuning
* Stateful packet parser
* Live telemetry visualization
* Embedded debugging workflow

---

# Future Work

* CAN bus transport layer
* Binary packet protocol
* Telemetry logging and playback
* CSV export support
* Hardware-in-the-loop testing
* Multi-axis control support
* Watchdog and fault-management systems
* Advanced control algorithms beyond PID
* RTOS-based task scheduling
* Native STM32 HAL implementation
