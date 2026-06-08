# Development & Contribution Guide

This document outlines the architecture, development workflow, design decisions, and future roadmap for the STM32 Motor Control Platform & Telemetry Dashboard.

---

# Development Environment

## Desktop Application

Requirements:

* Java 17+
* JavaFX
* jSerialComm
* IntelliJ IDEA (recommended)

---

## Embedded Firmware

Requirements:

* STM32 Nucleo-F103RB
* PlatformIO
* STM32 Arduino Framework
* ST-LINK Debugger

Communication:

* UART @ 115200 baud

---

# System Architecture

The project is organized into two major subsystems:

1. Desktop Telemetry Application
2. Embedded Firmware Platform

The systems communicate through a custom bidirectional UART protocol.

---

# Desktop Telemetry Application

Responsible for:

* Telemetry visualization
* Runtime graphing
* Controller tuning
* Performance analysis
* Serial communication

## Major Components

### SerialDashboard

Application entry point responsible for:

* JavaFX lifecycle management
* Dashboard initialization
* Communication startup
* UI coordination

### SerialParser

Dedicated telemetry processing thread.

Responsibilities:

* Blocking serial reads
* Telemetry packet parsing
* Data validation
* DTO creation
* Graceful shutdown handling

### GraphPane

Responsible for:

* Real-time graph rendering
* Target visualization
* Position visualization
* Controller output visualization

### CommandPane

Responsible for:

* Runtime gain tuning
* Command packet generation
* User interaction

### DataCalculations

Computes:

* Rise time
* Settling time
* Overshoot
* Derived telemetry metrics

---

# Embedded Firmware Platform

Responsible for:

* Control-loop execution
* Physics simulation
* Telemetry generation
* Runtime command processing

## Firmware Architecture

### MotionCoordinator

High-level system coordinator.

Responsibilities:

* Execute control loop
* Update simulation
* Generate telemetry
* Coordinate subsystem interaction

### PIDController

Responsibilities:

* Error calculation
* Integral accumulation
* Derivative filtering
* Control output generation

Features:

* Anti-windup protection
* Exponential moving average derivative filtering

### VirtualMotor

Plant simulation layer.

Models:

* Position
* Velocity
* Inertia
* Damping
* Actuator response

### PacketParser

Streaming parser responsible for:

* Byte-by-byte processing
* Packet assembly
* Field validation
* Error handling
* Parser recovery

### SerialManager

Communication transport layer.

Responsibilities:

* UART data acquisition
* Transport abstraction
* Timeout monitoring

### TelemetryManager

Responsible for:

* Telemetry packet creation
* UART telemetry transmission

---

# Communication Design

## Command Packets

Desktop → Firmware

Format:

```text
$target,kP,kI,kD
```

Example:

```text
$500,0.65,0.10,0.25
```

---

## Telemetry Packets

Firmware → Desktop

Format:

```text
target,error,lastError,currentPosition,kP,kI,kD,percentComplete,output
```

Example:

```text
500.0,12.3,15.4,487.7,0.65,0.10,0.25,97.5,0.42
```

---

# Parser Design Notes

The communication subsystem evolved through several iterations:

1. Basic string accumulation
2. Delimiter-based packet parsing
3. Stateful parser implementation
4. Packet validation framework
5. Parser resynchronization logic
6. Packet timeout detection
7. Runtime communication debugging

Current parser capabilities:

* Streaming byte processing
* Delimiter-driven field extraction
* Packet framing
* Invalid packet rejection
* Packet timeout detection
* Recovery from malformed packets
* Parser state management

---

# Debugging Workflow

Primary debugging tools:

* ST-LINK debugger
* PlatformIO debugging
* Breakpoints
* Runtime telemetry inspection
* Serial communication tracing

Common debugging focus areas:

* PID tuning behavior
* Packet synchronization
* Communication reliability
* Telemetry validation
* Runtime control response

---

# Current Project Status

## Completed

* [x] STM32 firmware migration
* [x] Real-time PID controller
* [x] Second-order plant simulation
* [x] Runtime target updates
* [x] Runtime kP tuning
* [x] Runtime kI tuning
* [x] Runtime kD tuning
* [x] JavaFX telemetry dashboard
* [x] Bidirectional UART communication
* [x] Streaming packet parser
* [x] Packet validation framework
* [x] Parser recovery handling
* [x] ST-LINK debugging workflow
* [x] Telemetry visualization
* [x] Performance metric calculations

---

# Future Roadmap

## Near-Term Improvements

* [ ] Telemetry logging
* [ ] CSV export support
* [ ] Additional parser stress testing
* [ ] Communication performance benchmarking

---

## Long-Term Goals

* [ ] Binary packet protocol
* [ ] CAN transport layer
* [ ] Hardware-in-the-loop testing
* [ ] Watchdog and fault management
* [ ] Multi-axis control support
* [ ] RTOS-based scheduling
* [ ] Native STM32 HAL implementation
* [ ] Advanced control algorithms beyond PID

---

# Design Philosophy

The project emphasizes:

* Modular architecture
* Separation of responsibilities
* Deterministic communication behavior
* Debuggability
* Embedded-systems best practices
* Real-world control-system constraints

The goal is not simply to simulate a PID controller, but to build an embedded control platform that mirrors the communication, debugging, and architectural challenges encountered in professional firmware development.
