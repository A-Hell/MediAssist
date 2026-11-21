# MediAssist

## Overview

This project is organized into several key directories:

- **Interface**: Contains CLI and GUI components for user interaction
- **Managers**: Handles business logic for different entities (Appointments, Doctors, Departments, Patients, Triage)
- **Structures**: Implements various data structures (BST, Graph, HashTable, Heap, Queue)
- **Storage**: Manages file I/O operations
- **Data & Models**: Contains data models and entity definitions

---

## Directory Structure

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

---

## Core Classes Documentation

### Model Classes

#### **Doctor Class** (`Models/Doctor.h`)
Represents a healthcare professional in the hospital system.

**Key Attributes:**
- `doctorId`: Unique identifier (auto-generated)
- `departmentId`: ID of the department the doctor belongs to
- `name`: Doctor's full name
- `phone`: Contact phone number
- `specialization`: Medical specialization
- `availability`: Boolean flag indicating if the doctor is available

**Key Features:**
- Automatic ID generation using a static counter
- Getters for retrieving doctor information
- Friend class relationship with `DoctorManager` for secure data management
- Operator overloading for console output with formatted display

---

#### **Department Class** (`Models/Department.h`)
Represents a hospital department managing doctors and services.

**Key Attributes:**
- `departmentId`: Unique identifier (auto-generated)
- `name`: Department name
- `description`: Department description
- `location`: Physical location within hospital
- `doctorIds`: Vector storing IDs of associated doctors

**Key Features:**
- Automatic ID generation using a static counter
- Methods to add/remove doctors from the department
- Getters for retrieving department information
- Maintains relationships with multiple doctors
- Friend class relationship with `DepartmentManager`

---

#### **Patient Class** (`Models/Patient.h`)
Represents a patient in the healthcare system.

**Key Attributes:**
- `patientID`: Unique identifier (auto-generated)
- `name`: Patient's full name
- `age`: Patient's age
- `gender`: Patient's gender
- `phone`: Contact phone number
- `address`: Residential address
- `height`: Patient's height (in appropriate units)
- `weight`: Patient's weight (in appropriate units)

**Key Features:**
- Automatic ID generation using a static counter
- Constructor with default and parameterized options
- Getters for all patient attributes
- Friend class relationship with `PatientManager`

---

#### **Appointment Class** (`Models/Appointment.h`)
Represents a scheduled appointment between patient and doctor.

**Key Attributes:**
- `appointmentID`: Unique identifier (auto-generated)
- `patientID`: ID of the patient
- `doctorId`: ID of the assigned doctor
- `appointmentDate`: Date of appointment
- `appointmentTime`: Time of appointment
- `status`: Appointment status (e.g., "Scheduled", "Completed", "Cancelled")

**Key Features:**
- Automatic ID generation using a static counter
- Constructor with default and parameterized options
- Getters for retrieving appointment details
- Friend class relationship with `AppointmentManager`
- Status tracking for appointment lifecycle management

---

### Data Structure Classes

#### **Binary Search Tree (BST)** (`Structures/BST.h`)
A self-balancing tree structure for efficient appointment management.

**Node Structure:**
- `appointmentID`: ID of the appointment
- `date`: Appointment date
- `time`: Appointment time
- `left` and `right`: Pointers to child nodes

**Key Operations:**
- **insert()**: Add a new appointment to the tree (O(log n) average)
- **remove()**: Delete an appointment from the tree
- **search()**: Find an appointment by ID, date, and time; returns appointmentID if found, -1 otherwise
- **display()**: Print tree structure
- **displayInorder()**: Print appointments in sorted order

**Use Case:** Efficient scheduling and retrieval of appointments based on date and time

---

#### **Max Heap** (`Structures/Heap.h`)
An array-based max heap implementation for priority-based appointment management.

**Node Structure:**
- `appointmentID`: ID of the appointment
- `triageScore`: Priority score based on medical urgency

**Key Operations:**
- **insert()**: Add an appointment with a triage score (O(log n))
- **remove()**: Delete an appointment from the heap
- **extractMax()**: Retrieve and remove the appointment with the highest triage score (returns -1 if empty)
- **display()**: Print heap contents
- **heapifyUp()**: Restore heap property by moving element up
- **heapifyDown()**: Restore heap property by moving element down

**Use Case:** Prioritize patient appointments based on medical urgency and triage scores, ensuring critical cases are handled first

---