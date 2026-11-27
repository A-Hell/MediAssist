#pragma once

#include "Common.h"

#include "PatientManager.h"
#include "DoctorManager.h"
#include "DepartmentManager.h"
#include "AppointmentManager.h"
#include "TriageManager.h"

class HospitalSystem
{
private:
    // Core managers
    PatientManager patientManager;
    DoctorManager doctorManager;
    DepartmentManager departmentManager;
    AppointmentManager appointmentManager;
    TriageManager triageManager;

public:
    // Constructor
    HospitalSystem(int patientCapacity = 25) : patientManager(patientCapacity), triageManager(patientCapacity) {}

    // ---------------- PATIENT OPERATIONS ----------------

    int registerPatient(
        string name,
        int age,
        string gender,
        string phone,
        string address,
        double height,
        double weight
    );

    const Patient* findPatient(int patientID);

    bool updatePatientName(int patientID, string name);
    bool updatePatientAge(int patientID, int age);
    bool updatePatientGender(int patientID, string gender);
    bool updatePatientPhone(int patientID, string phone);
    bool updatePatientAddress(int patientID, string address);
    bool updatePatientHeight(int patientID, double height);
    bool updatePatientWeight(int patientID, double weight);

    bool patientExists(int patientID);
    bool removePatient(int patientID);

    void displayAllPatients();

    // ---------------- DEPARTMENT OPERATIONS ----------------

    // Add retrieval and management operations here as needed.

    // ---------------- DOCTOR OPERATIONS ----------------

    // Add retrieval and management operations here as needed.

    // ---------------- APPOINTMENT OPERATIONS ----------------

    int createAppointment(
        int patientID,
        int departmentID,
        const vector<Symptom>& symptoms,
        const string& date,
        const string& time
    );

    const Appointment* findAppointment(int appointmentID);

    // Appointment update operations
    bool updateAppointmentDate(int appointmentID, const string& newDate);
    bool updateAppointmentTime(int appointmentID, const string& newTime);
    bool updateAppointmentDepartment(int appointmentID, int newDepartmentID);

    bool addSymptomToAppointment(int appointmentID, Symptom symptom);
    bool removeSymptomFromAppointment(int appointmentID, Symptom symptom);

    // Appointment status management
    bool cancelAppointment(int appointmentID);
    bool completeAppointment(int appointmentID);
    bool setAppointmentWaiting(int appointmentID);

    void displayAllAppointments();

    // ---------------- TRIAGE OPERATIONS ----------------

    // Waiting-list and doctor-assignment workflows will go here.
};