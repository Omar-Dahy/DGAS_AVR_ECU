# 🚗 Embedded Automotive ECUs – DGAS Project

This repository is part of the **Drowsy Guard Autopilot System (DGAS)** graduation project. It contains the firmware, design files, and simulation for the following ECUs:

* 🧭 **Gateway ECU**
  Handles communication between all subsystems using I2C bus and other protocols. It routes messages, filters data, and ensures reliable data exchange between ECUs.

* 💡 **Lighting ECU**
  Controls external lighting (e.g., headlights, indicators, brake lights). Receives signals from the Gateway ECU and responds accordingly based on system status.

* 🛞 **Motion ECU**
  Manages vehicle movement including motor control (forward, reverse, stop). Receives movement commands via I2C and executes motor driver control logic.

* 🧪 **Simulation File**
  A simulation environment to test ECU communication and control logic without needing physical hardware. Useful for debugging and validation.

---
🖼️ System Design Diagram
Inline-style: 

![alt text](https://github.com/Omar-Dahy/DGAS_AVR_ECU/blob/main/desgin%20photo.png "desgin")
---
## 🔧 Tools & Technologies

* Microcontrollers: ATmega32A
* Communication: I2C, GPIO
* IDEs: Atmel Studio
* Simulation: Proteus 

---

## 🧠 Key Objectives

* Integrate multiple ECUs for a modular, scalable vehicle architecture
* Enable real-time communication and control
