# ⚙️ DC Motor Speed and Position Control

This repository contains the project report and implementation details for the **DC Motor Speed and Position Control** system, focusing on the application of classical control algorithms (PID) on a microcontroller.

---

## ✨ Project Summary

The main goal of this project was to design and implement a control system capable of accurately regulating the speed (RPM) and position of a DC gear motor using feedback from an encoder.

### 👥 Team Members

| Name | Role |
| :--- | :--- |
| Mohammad Amin Mohtashami | (Details in report) |
| Amir Ali Aghamohammadi | (Details in report) |

*Supervised by: Dr. Afshar*
*Term: Winter 1402 (2023/2024)*

---

## 🛠️ Hardware Specifications (Chapter 2)

The system relies on specific hardware components for feedback and actuation:

* **DC Motor:** A gear motor with an integrated encoder, model **5280-YGY6138** (Yuanruixin company).
    * **Voltage:** 12V
    * **No-load Speed:** 65 RPM
    * **Current:** 3A
* **Encoder:** Two-channel Hall-effect encoder integrated into the motor.
    * **Resolution:** 1080 Pulses Per Revolution (PPR) on the output shaft.
* **Motor Driver:** **L298N** module, used to interface between the microcontroller and the motor.
* **Microcontroller:** (Specific model is not explicitly named, but the platform is used for implementing the control algorithms).

---

## 🧠 Control Algorithms Implemented

The project focuses on two main control objectives:

### 1. Speed Control (RPM)

* **Algorithm:** PID Control is used to regulate the motor's speed against a setpoint (RPM).
* **Feedback:** The speed is calculated using the encoder data read through interrupts.
* **Results:** The report includes demonstration outputs for various setpoints: **15 RPM**, **30 RPM**, and **55 RPM**.

### 2. Position Control

* **Algorithm:** PID Control is adapted to control the motor's angular position.
* **Feedback:** Position is tracked directly from the encoder's pulse count using an Interrupt Service Routine (ISR).
* **Code Structure:** Includes pin selection, variable initialization, `setup` for initial configuration, and the main `loop` for continuous PID calculation and motor command adjustment.

---

## 💻 Code Structure

The microcontroller code is structured to prioritize timing and accuracy:

* **Interrupts:** Used for precise reading of the encoder data (position and velocity feedback).
* **PID Loop:** The main loop calculates the error, derivative, and integral terms and sets the motor parameters (likely PWM signal).
* **Functions:** Separate functions are used for setting motor parameters and reading the encoder.

---

## 📚 Final Report

The detailed theoretical analysis, hardware selection justification, and complete code listings are available in the project report:

* `report_of_projectdocx.pdf` (or similar, based on file name).

---

**Do you want to proceed with integrating this project into your GitHub repository or would you like to discuss the next steps?**
