# PID Motor Simulator & Telemetry Dashboard

A real-time control system simulator designed to model second-order physical systems and analyze how PID controllers behave under realistic constraints.

---

## Why This Project Matters
This project explores how software interacts with physical systems. Instead of ideal conditions, it models inertia, damping, and actuator limits to show how control algorithms behave in real-world scenarios.

---

## Key Features
- **Second-Order Physics Simulation** — Models mass, inertia, and damping using numerical integration  
- **Real-Time PID Controller** — Full PID loop with adjustable kP, kI, and kD gains  
- **Integral Anti-Windup** — Prevents instability from accumulated error  
- **Derivative Filtering (EMA)** — Reduces noise and jitter in the control signal  
- **Dynamic Load Scaling** — Adjustable mass to test system robustness  
- **Live Telemetry Dashboard** — Real-time graphing of position, setpoint, and control output  
- **Performance Metrics** — Calculates rise time, settling time, and overshoot automatically  
- **Static Friction Simulation** — Models breakaway torque behavior  

---

## Key Insight
The system reveals a hard performance limit: with a fixed motor constant and mass, a 2-second rise time is physically unattainable. Increasing responsiveness leads to instability due to momentum exceeding available damping.

This highlights a fundamental tradeoff in control systems:

> Faster response vs system stability

---

## How It Works (Simplified)

### Physics Model
- Acceleration depends on force, damping, and mass  
- Velocity and position are updated each frame (~60Hz)  

### Control Loop
- **Proportional (kP):** reacts to current error  
- **Integral (kI):** removes steady-state error  
- **Derivative (kD):** dampens motion and prevents overshoot  

---

## Tech Stack
- Java / JavaFX  
- Real-time simulation loop (~60Hz)  
- Object-oriented design  

---

## Architecture
- `TelemetryDashboard` — UI + control loop  
- `VirtualMotor` — physics simulation model  

---

## Current Status
Fully functional real-time control system simulator with second-order physics and performance profiling.

---

## Future Work
- Port control loop to C for embedded systems  
- Add CSV export for analysis  
- Implement frequency response (Bode plots)  
