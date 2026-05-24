# Development & Contribution Guide

This document outlines the architecture, development workflow, and future embedded systems roadmap for the PID Motor Simulator & Telemetry Dashboard.

---

# Environment Setup

## Desktop Application
- Java 17+
- JavaFX
- jSerialComm

## Embedded Firmware
- Arduino IDE / PlatformIO
- UART serial transport @ 115200 baud

---

# Architecture Overview

The project is divided into two major subsystems:

## 1. Desktop Telemetry System

Responsible for:
- telemetry visualization,
- runtime graphing,
- command transmission,
- metric analysis,
- parser lifecycle management.

### Major Components

#### `SerialDashboard`
- JavaFX application lifecycle
- UI orchestration
- serial command transmission
- parser thread management

#### `SerialParser`
Dedicated UART telemetry parser thread:
- blocking serial reads,
- packet validation,
- telemetry DTO generation,
- graceful shutdown handling.

#### `GraphPane`
High-frequency telemetry rendering:
- target position,
- actual motor position,
- controller output.

#### `DataCalculations`
Computes:
- overshoot,
- settling time,
- rise time,
- telemetry normalization.

---

## 2. Embedded Firmware System

Responsible for:
- realtime control execution,
- physics simulation,
- telemetry transmission,
- runtime command parsing.

### Firmware Architecture

#### Physics Layer
- Second-order plant simulation
- Numerical integration
- Damping and friction modeling

#### Control Layer
- PID control loop
- EMA derivative filtering
- Anti-windup logic

#### Communication Layer
Implements:
- UART telemetry streaming
- runtime command reception
- streaming packet parser
- parser resynchronization logic

---

# Embedded Communication Design

## Telemetry Transport

Firmware continuously streams telemetry packets:

```text
target,error,lastError,currentPosition,kP,kD,percentComplete,power\n
```

## Runtime Command Packets

Desktop application transmits runtime controller gains:

```text
kP,kD\n
```

---

# Parser Design Notes

The embedded parser evolved through several iterations:
- naive string accumulation,
- blocking transport debugging,
- parser synchronization handling,
- malformed packet recovery,
- bounded packet protection,
- deterministic parser reset handling.

Current parser behavior:
- byte-stream processing,
- delimiter-driven field separation,
- newline packet framing,
- overflow recovery,
- parser resynchronization.

---

# Current Roadmap

## Completed
- [x] Second-order plant simulation
- [x] Realtime PID control
- [x] Telemetry dashboard
- [x] UART telemetry streaming
- [x] Bidirectional serial communication
- [x] Runtime PID tuning
- [x] Streaming UART parser
- [x] Parser recovery handling
- [x] Graceful parser thread shutdown

---

## In Progress
- [ ] Replace dynamic String parser with fixed-size buffer parser
- [ ] Add runtime kI tuning
- [ ] Improve parser state-machine architecture

---

## Planned
- [ ] CAN/J1939 communication layer
- [ ] Binary telemetry protocol
- [ ] STM32 firmware port
- [ ] Watchdog safety system
- [ ] Data logging subsystem
- [ ] Unit testing for parser synchronization edge cases
- [ ] Multi-controller simulation support
