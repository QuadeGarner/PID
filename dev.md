# Development & Contribution Guide

This document outlines the environment setup, project architecture, and the roadmap for integrating the C-based firmware pipeline.

## Environment Setup
*   **Java Version**: OpenJDK 17+ (Required for JavaFX compatibility).
*   **UI Framework**: JavaFX for telemetry rendering and real-time graphing.
*   **Build System**: Maven or Gradle, ensuring all dependencies for signal processing and UI components are resolved.

## Project Architecture
The project follows a modular structure to maintain a clear separation between physics simulation and the user interface:
*   **Physics Engine**: Located in `Simulator.VirtualMotor`, utilizing numerical integration for second-order plant modeling.
*   **Control Layer**: Implements the discrete PID logic, including EMA filtering for the derivative term and anti-windup logic.
*   **View/Controller**: Located in `Simulator.TelemetryDashboard`, handling the high-frequency UI refresh loop (typically 60Hz) and event handling for sliders.

## Current Roadmap
- [x] Implement Second-Order Plant Logic (Inertia/Damping simulation).
- [x] Add Dynamic Mass Scaling with real-time UI updates.
- [x] Achieve system stability (Settling Time < 0.6s).
- [ ] **Phase 2: C-Pipeline Integration**
    - [ ] Port core PID calculations to a C source file.
    - [ ] Implement a JNI (Java Native Interface) bridge or socket-based communication layer.
    - [ ] Compare execution overhead between the JVM and Native C implementation.

## Development Standards
*   **Version Control**: Maintain a structured commit history with descriptive messages to track feature progression.
*   **Unit Testing**: Verify PID logic transitions and ensure the Step Response trigger consistently reports accurate Rise Time and Settling Time metrics.
*   **Documentation**: Ensure the README remains the source of truth for physical constants and current tuning ranges.
