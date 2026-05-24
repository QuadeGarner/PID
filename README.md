# PID Motor Simulator & Telemetry Dashboard

A real-time control system simulator and telemetry platform designed to model second-order physical systems, analyze PID controller behavior, and support live bidirectional firmware communication over UART.

---

## Why This Project Matters

This project explores how embedded software interacts with physical systems under realistic constraints.

Instead of idealized motion, the simulator models:
- inertia,
- damping,
- actuator saturation,
- friction,
- and transport latency.

The system evolved from a standalone PID simulator into a full telemetry + firmware communication platform capable of:
- real-time telemetry streaming,
- runtime PID tuning,
- bidirectional serial communication,
- and embedded parser synchronization.

---

## Key Features

### Real-Time Control & Simulation
- **Second-Order Physics Simulation** — Models inertia, damping, and force response using numerical integration
- **Real-Time PID Controller** — Runtime adjustable kP, kI, and kD gains
- **Integral Anti-Windup** — Prevents integral accumulation instability
- **Derivative EMA Filtering** — Reduces derivative noise and oscillation
- **Static Friction Modeling** — Simulates breakaway torque behavior
- **Dynamic Load Scaling** — Adjustable system mass for robustness testing

### Telemetry & Visualization
- **Live Telemetry Dashboard** — Real-time JavaFX telemetry visualization
- **Realtime Signal Graphing** — Plots:
  - target position,
  - motor position,
  - controller output
- **Performance Metrics**
  - Rise Time
  - Settling Time
  - Overshoot

### Embedded Communication Pipeline
- **Bidirectional UART Communication**
  - Java dashboard transmits runtime PID gain updates
  - Embedded firmware streams telemetry packets
- **Custom Serial Packet Protocol**
  - Comma-delimited packet framing
  - Newline packet termination
  - Runtime parser synchronization
- **Streaming UART Parser**
  - Stateful packet parsing
  - Malformed packet recovery
  - Overflow protection
  - Parser resynchronization logic
- **Realtime Runtime Tuning**
  - Live PID tuning from desktop dashboard to embedded firmware

---

## System Architecture

### Desktop Telemetry Application (Java / JavaFX)
Responsible for:
- telemetry visualization,
- runtime graphing,
- command transmission,
- performance analysis.

#### Core Components
- `SerialDashboard`
  - Main UI + application lifecycle
- `GraphPane`
  - Real-time telemetry rendering
- `DataCalculations`
  - Rise time / overshoot / settling-time calculations
- `SerialParser`
  - UART telemetry parser thread
- `CommandPane`
  - Runtime PID command generation

---

### Embedded Firmware Layer (Arduino / C++)
Responsible for:
- physics simulation,
- PID execution,
- telemetry generation,
- command packet parsing.

#### Embedded Features
- UART telemetry transmission
- Runtime command packet parsing
- Stateful serial parser
- Real-time PID gain updates
- LED-based system state visualization

---

## UART Communication Protocol

### Telemetry Packet Format

```text
target,error,lastError,currentPosition,kP,kD,percentComplete,power\n
```

### Command Packet Format

```text
kP,kD\n
```

### Parser Characteristics
- Streaming byte-by-byte UART parser
- Packet framing using newline termination
- Field separation using comma delimiters
- Malformed packet recovery through parser resynchronization
- Overflow protection to prevent runaway packet accumulation

---

## Key Insight

The simulator demonstrates a fundamental control-system limitation:

> Faster response increases instability when available damping and actuator authority are limited.

With fixed:
- motor force,
- damping,
- and mass,

a sufficiently aggressive rise time becomes physically unattainable without overshoot or instability.

---

## Tech Stack

### Desktop
- Java
- JavaFX
- jSerialComm

### Embedded
- Arduino C++
- UART Serial Communication

### Concepts
- PID Control Systems
- Real-Time Telemetry
- Embedded Communication Protocols
- Streaming Parser Design
- Numerical Integration
- Stateful Firmware Parsing

---

## Current Status

Fully functional:
- realtime PID simulator,
- telemetry dashboard,
- bidirectional UART communication pipeline,
- runtime embedded tuning system.

---

## Future Work

- Add CAN/J1939 transport layer
- Replace String-based parser with fixed-size char buffer parser
- Add binary packet protocol
- Add telemetry logging / CSV export
- Add frequency-response analysis (Bode plots)
- Port firmware to STM32 or ESP32
- Add watchdog + failsafe logic
- Add multi-threaded telemetry buffering
