# PID Motor Simulator & Telemetry Dashboard

A high-fidelity **control system workbench** developed in JavaFX to simulate, visualize, and profile a discrete PID controller. This tool provides a real-time graphical interface for tuning control gains and analyzing system stability under various load conditions.

## Key Features
*   **Second-Order Plant Simulation:** Accurately models physical hardware by simulating **Mass**, **Inertia**, and **Damping** through numerical integration ($F=ma$).
*   **Dynamic Load Scaling:** Includes a real-time "Mass" slider and label to adjust motor inertia on the fly, allowing for robustness testing against variable physical loads.
*   **Discrete PID Controller:** Implements a full Proportional-Integral-Derivative (PID) loop with **Integral Anti-Windup** to prevent actuator saturation issues.
*   **Signal Processing:** Utilizes an **Exponential Moving Average (EMA) filter** on the derivative term to suppress high-frequency noise and jitter.
*   **Performance Profiling:** Automated calculation of **Rise Time (10-90%)**, **Settling Time (2% criterion)**, and **Overshoot percentage**.
*   **Interactive Telemetry:** Real-time multi-lane graphing of **Process Variable (PV)**, **Setpoint (SP)**, and **Control Effort (Output)**.
*   **Static Friction (Stiction) Simulation:** Logic handles minimum power thresholds to simulate real-world motor breakaway torque.

## Technical Implementation

### The Physics Model (Second-Order)
The simulator utilizes a discrete-time physics engine to calculate motor motion:
1.  **Acceleration**: $a = \frac{(Power \times Scale) - (Velocity \times Damping)}{Mass}$
2.  **Velocity Integration**: $v_{n} = v_{n-1} + (a \times dt)$
3.  **Position Integration**: $p_{n} = p_{n-1} + (v \times dt)$

### The Control Logic
The firmware logic calculates motor effort using discrete-time integration and differentiation:
1.  **Proportional ($k_P$):** Immediate response to current error.
2.  **Integral ($k_I$):** Eliminates steady-state error with a software-capped summation to prevent windup.
3.  **Derivative ($k_D$):** Predicts future error to dampen oscillations, smoothed via a low-pass filter. In second-order mode, this acts as the primary braking force against simulated inertia.

### Transient Response Diagnostics
The dashboard includes a **Step Response Trigger**. By injecting a sudden step input into the system, the tool benchmarks:
*   **Rise Time:** Speed of the system response from 10% to 90% of the target.
*   **Settling Time:** Time required for the system to reach a steady state within a 2% tolerance band.
*   **Stability:** Visualization of the damping ratio and oscillation frequency.

## Project Structure
*   **`Simulator.TelemetryDashboard`**: The central controller managing the high-frequency loop and UI events.
*   **`Simulator.VirtualMotor`**: A physics-based model of a DC motor's position and velocity, including mutable mass and damping variables.
*   **Hardware-Agnostic Design:** The PID logic is written to be easily portable to embedded C for microcontrollers (e.g., STM32, Arduino).

## Controls & Tuning Ranges
| Parameter | Range | Description |
| :--- | :--- | :--- |
| **$k_P$** | 0.0 - 0.05 | Primary gain for error correction. |
| **$k_I$** | 0.0 - 0.001 | Accumulates error to reach the exact setpoint. |
| **$k_D$** | 0.0 - 0.5 | Dampens movement to prevent overshoot. |
| **Mass** | Variable | Adjusts system inertia; higher values require higher $k_D$ for stability. |

---

**Current Status:** Fully functional tuning workbench with second-order physics support.

**Future Development:**
- [ ] Port the core control logic to C for hardware integration.
- [ ] Add CSV export functionality for post-test data analysis.
- [ ] Implement Frequency Response (Bode Plot) generation.
