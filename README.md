# PID Motor Simulator & Telemetry Dashboard

A custom **JavaFX-based telemetry tool** designed to simulate and tune a PID control loop for a virtual motor. This project serves as a sandbox for testing control theory, transitioning from console-based logic to a real-time graphical interface.

##  Features
* **Virtual Hardware Simulation:** Implements a `VirtualMotor` class that simulates physics-based movement (position and velocity).
* **Real-time PID Controller:** Features a Proportional-Derivative (PD) loop running inside a 60Hz `AnimationTimer`.
* **Dynamic Input:** Uses a JavaFX `Slider` to set target positions in real-time.
* **Live Telemetry:** A dedicated data readout displaying current position, error, and motor power.
* **Java Module System:** Configured with `module-info.java` for modern OpenJFX compatibility.

## Project Structure
* **`Simulator.TelemetryDashboard`**: The main JavaFX application containing the UI, the `AnimationTimer`, and the PID logic.
* **`Simulator.VirtualMotor`**: The physics engine simulating the motor's behavior.
* **`module-info.java`**: Handles module exports and requirements for JavaFX.

##  The Control Logic
The controller calculates the motor power based on the following logic:
1.  **Proportional ($k_P$):** Pulls the motor toward the target based on the current error.
2.  **Derivative ($k_D$):** Acts as a "brake" to counteract momentum and reduce oscillation.
3.  **Loop Rate:** Synchronized with the screen refresh rate (~16.6ms per update) for smooth visual feedback.

##  Current Gains
| Parameter | Value | Description |
| :--- | :--- | :--- |
| **$k_P$** | 0.01 | Sensitivity/Strength of the correction |
| **$k_D$** | 0.10 | Damping/Braking to prevent bouncing |

---

**Current Status:** Stable MVP. The controller is tuned to be critically damped (no oscillation). 

**Next Steps:**
- [ ] Add real-time gain adjustment via UI text fields.
- [ ] Implement Integral ($k_I$) term to eliminate steady-state error.
- [ ] Add a real-time line graph for error over time.
