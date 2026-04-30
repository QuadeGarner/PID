# PID Motor Simulator & Telemetry Dashboard

A high-fidelity **control system workbench** developed in JavaFX to simulate, visualize, and profile a discrete PID controller. This tool provides a real-time graphical interface for tuning control gains and analyzing system stability under various load conditions.

## Key Features
*   **Discrete PID Controller:** Implements a full Proportional-Integral-Derivative (PID) loop with **Integral Anti-Windup** to prevent actuator saturation issues.
*   **Signal Processing:** Utilizes an **Exponential Moving Average (EMA) filter** on the derivative term to suppress high-frequency noise and jitter.
*   **Performance Profiling:** Automated calculation of **Rise Time (10-90%)**, **Settling Time (2% criterion)**, and **Overshoot percentage**.
*   **Interactive Telemetry:** Real-time multi-lane graphing of **Process Variable (PV)**, **Setpoint (SP)**, and **Control Effort (Output)**.
*   **Static Friction (Stiction) Simulation:** Logic handles minimum power thresholds to simulate real-world motor breakaway torque.

## Technical Implementation

### The Control Logic
The firmware logic calculates motor effort using discrete-time integration and differentiation:
1.  **Proportional ($k_P$):** Immediate response to current error.
2.  **Integral ($k_I$):** Eliminates steady-state error with a software-capped summation to prevent windup.
3.  **Derivative ($k_D$):** Predicts future error to dampen oscillations, smoothed via a low-pass filter.

### Transient Response Diagnostics
The dashboard includes a **Step Response Trigger**. By injecting a sudden step input into the system, the tool benchmarks:
*   **Rise Time:** Speed of the system response from 10% to 90% of the target.
*   **Settling Time:** Time required for the system to reach a steady state within a 2% tolerance band.
*   **Stability:** Visualization of the damping ratio and oscillation frequency.

## Project Structure
*   **`Simulator.TelemetryDashboard`**: The central controller managing the high-frequency loop and UI events.
*   **`Simulator.VirtualMotor`**: A physics-based model of a DC motor's position and velocity.
*   **Hardware-Agnostic Design:** The PID logic is written to be easily portable to embedded C for microcontrollers (e.g., STM32, Arduino).

## Controls & Tuning Ranges
| Parameter | Range | Description |
| :--- | :--- | :--- |
| **$k_P$** | 0.0 - 0.05 | Primary gain for error correction. |
| **$k_I$** | 0.0 - 0.001 | Accumulates error to reach the exact setpoint. |
| **$k_D$** | 0.0 - 0.5 | Dampens movement to prevent overshoot. |

---

**Current Status:** Fully functional tuning workbench.

**Future Development:**
- [ ] Implement a second-order plant model to simulate physical load and inertia.
- [ ] Port the core control logic to C for hardware integration.
- [ ] Add CSV export functionality for post-test data analysis.
