# Remotely Operated Aquatic Surface Vehicle

This project demonstrates the design and development of a low-cost, remotely operated unmanned surface vehicle (USV) for aquatic weed cutting and floating debris collection in small to medium-sized freshwater bodies.

## 🚀 Features

- **RF-Controlled Operation**: 250-meter range using FlySky 8-channel transmitter.
- **Dual Propulsion**: Two 12V DC motors with 3D-printed propeller wheels for navigation.
- **Conveyor Mechanism**: Remotely controlled belt system to collect floating debris (up to 1 kg payload).
- **Weed Cutting System**: Sickle-type blades driven by a stepper motor for efficient weed removal.
- **Lightweight Design**: Constructed using acrylic sheets, 3D-printed parts, and hollow PVC tubes for buoyancy.

## 📂 Repository Structure

- `code/`: Arduino code controlling propulsion, conveyor, and cutting mechanisms.
- `hardware/`: CAD files and electrical schematics for mechanical and electronic systems.
- `images/`: Photos from field testing and component views.

## 🛠 Components Used

- Arduino UNO
- Cytron 10A Motor Driver
- FlySky 8-Channel RF Receiver/Transmitter
- 12V 6Ah Battery (sealed lead-acid)
- Stepper Motor (for cutter)
- 3D Printed Propellers and Structural Parts
- PVC Tubes for Buoyancy

## 📸 Sample Images

| Lake Testing | Conveyor Unit | 
|--------------|---------------|
| ![lake](images/lake_test.png) | ![conveyor](images/conveyor_unit.png) |

## 👨‍🔬 Developed By

**G. Lakshmi Vara Prasad**  
Junior Research Fellow (JRF)  
TIH-TIDF, Indian Institute of Technology Guwahati  
Under the guidance of **Prof. S. K. Dwivedy**

## ⚠️ Note

This repository contains only the **manually operated version** of the vehicle. Autonomous functionality and environmental monitoring modules (e.g., ROS-based navigation, pH/Turbidity sensors) were developed later but are **not included here**.

## 📄 License

This project is released under the [MIT License](LICENSE).
