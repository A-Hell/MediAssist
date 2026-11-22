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
A binary search tree for efficient chronological appointment management, sorted by date and time.

**Node Structure:**
- `appointment`: Complete Appointment object (stores full appointment data)
- `left` and `right`: Pointers to child nodes

**Key Operations:**
- **insert()**: Add a new Appointment object to the tree (O(log n) average) - takes `const Appointment&`
- **remove()**: Delete an appointment by ID, date, and time (O(log n) average)
- **search(ID, date, time)**: BST search returning `Appointment*` (O(log n) average)
- **search(ID)**: BFS search by ID alone (O(n), returns `Appointment*`)
- **display()**: Print all appointments in chronological order using inorder traversal
- **deleteTree()**: Clear entire tree and free memory

**Data Storage:**
- Stores complete `Appointment` objects, providing access to all appointment fields (patient ID, doctor ID, status, etc.)
- Ordered by `appointmentDate` and `appointmentTime` for efficient scheduling queries

**Search Strategies:**
1. **BST Search** (date/time based) - O(log n) average, leverages tree ordering
2. **BFS Search** (ID based) - O(n), uses queue-based breadth-first search since ID is not the sort key

**Use Case:** Efficient chronological scheduling and retrieval of appointments. Ideal for time-based queries like "find all appointments on 2024-01-15" or "get next appointment after 09:00 AM". Automatically maintains appointments in time order.

---

#### **Max Heap** (`Structures/Heap.h`)
An array-based max heap implementation for priority-based appointment management with arrival number tie-breaking.

**Node Structure:**
- `appointmentID`: ID of the appointment
- `triageScore`: Priority score based on medical urgency
- `arrivalNumber`: Automatic counter to track appointment arrival order (breaks ties in triage scores)

**Key Operations:**
- **insert()**: Add an appointment with a triage score (O(log n)) - auto-assigns arrival number
- **remove()**: Delete an appointment from the heap (O(n) for search, O(log n) for reheapify)
- **search()**: Find an appointment by ID (O(n) linear search)
- **extractMax()**: Retrieve and remove the appointment with the highest triage score (O(log n), returns -1 if empty)
- **peek()**: View the highest priority appointment without removing it (O(1), returns -1 if empty)
- **display()**: Print heap contents with AppointmentID, TriageScore, and ArrivalNumber
- **heapifyUp()**: Restore heap property by moving element up after insertion
- **heapifyDown()**: Restore heap property by moving element down after removal

**Priority Comparison Logic:**
- Primary: Higher triage score = higher priority
- Tie-breaker: Lower arrival number = higher priority (FIFO for equal urgency)
- Uses `hasHigherPriority()` helper function for consistent comparison across all operations

**Use Case:** Prioritize patient appointments based on medical urgency and triage scores. Ensures critical cases are handled first while maintaining fair FIFO ordering for patients with equal medical priority. Particularly useful for emergency departments and urgent care scenarios.

---

## Manager Classes

Managers implement the business logic and operations for each entity in the system. They act as intermediaries between the data models and the user interface.

### **AppointmentManager** (`Managers/AppointmentManager.h` / `AppointmentManager.cpp`)

Handles all appointment-related operations including creation, search, updates, and status management.

**Core Responsibilities:**
- Create and validate new appointments
- Search for appointments by ID or date/time
- Update appointment details (date, time, assigned doctor)
- Manage appointment lifecycle (status transitions)
- Display appointment information

**Key Data Structure:**
- Uses `BST` (Binary Search Tree) to store appointments sorted by date and time
- Provides dual search capabilities: efficient BST search by date/time, and BFS search by appointment ID

**Key Methods:**

| Method | Purpose | Return Type |
|--------|---------|-------------|
| `createAppointment(patientID, doctorID, date, time)` | Create new appointment with validation | `bool` |
| `appointmentExists(appointmentID)` | Check if appointment exists | `bool` |
| `searchAppointment(appointmentID)` | Find appointment by ID | `Appointment*` |
| `updateAppointmentDate(appointmentID, newDate)` | Update appointment date with validation | `bool` |
| `updateAppointmentTime(appointmentID, newTime)` | Update appointment time with validation | `bool` |
| `updateAppointmentDoctor(appointmentID, newDoctorID)` | Reassign doctor for appointment | `bool` |
| `setAppointmentWaiting(appointmentID)` | Mark appointment as "Waiting" | `bool` |
| `cancelAppointment(appointmentID)` | Cancel appointment (status = "Canceled") | `bool` |
| `completeAppointment(appointmentID)` | Mark appointment as completed | `bool` |
| `displayAppointments()` | Display all appointments in chronological order | `void` |

**Input Validation:**
- **Date Format**: Validates against `YYYY-MM-DD` using `isValidDate()`
- **Time Format**: Validates against `HH:MM` using `isValidTime()`
- **IDs**: Checks for valid positive appointment/patient/doctor IDs

**Appointment Status Flow:**
```
Scheduled → Waiting → Completed
         ↘           ↗
            Canceled
```

**Error Handling:**
- Returns `false` on validation failures
- Displays color-coded error messages (using RED/RESET formatting)
- Returns `nullptr` when appointment not found

**Example Usage:**
```cpp
AppointmentManager manager;

// Create appointment
bool success = manager.createAppointment(1, 5, "2024-01-15", "09:00");

// Search appointment
Appointment* apt = manager.searchAppointment(1);

// Update appointment details
manager.updateAppointmentTime(1, "10:00");

// Change appointment status
manager.setAppointmentWaiting(1);
manager.completeAppointment(1);

// Display all appointments
manager.displayAppointments();
```

**Integration with Other Components:**
- Works with `Appointment` model class for data representation
- Uses `BST` for efficient appointment storage and retrieval
- Interfaces with UI components for user interaction
- Coordinates with `DoctorManager` and `PatientManager` for validation

---