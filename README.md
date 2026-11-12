# MediAssist

## Directory Structure

## Overview

This project is organized into several key directories:

- **Interface**: Contains CLI and GUI components for user interaction
- **Managers**: Handles business logic for different entities (Appointments, Doctors, Departments, Patients, Triage)
- **Structures**: Implements various data structures (BST, Graph, HashTable, Heap, Queue)
- **Storage**: Manages file I/O operations
- **Data & Models**: Contains data models and entity definitions

```
MediAssist/
├── 📁 Data/
│   ├── appointments.txt
│   ├── departments.txt
│   ├── doctors.txt
│   └── patients.txt
├── 📁 Interface/
│   ├── CLI.h
│   └── GUI.h
├── 📁 Managers/
│   ├── AppointmentManager.h
│   ├── DepartmentManager.h
│   ├── DoctorManager.h
│   ├── HospitalSystem.h
│   ├── PatientManager.h
│   └── TriageManager.h
├── 📁 Models/
│   ├── Appointment.h
│   ├── Department.h
│   ├── Doctor.h
│   └── Patient.h
├── 📁 Storage/
│   ├── FileManager.cpp
│   └── FileManager.h
├── 📁 Structures/
│   ├── BST.h
│   ├── Graph.h
│   ├── HashTable.h
│   ├── Heap.h
│   └── Queue.h
├── 📄 main.cpp
├── 📄 MediAssist.sln
└── 📄 MediAssist.vcxproj
```