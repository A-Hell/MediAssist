#pragma once

#include "Common.h"

#include "PatientManager.h"
#include "DoctorManager.h"
#include "DepartmentManager.h"
#include "AppointmentManager.h"
#include "TriageManager.h"
#include "Models/Symptoms.h"

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

	int createDepartment(
        const string& name,
        const string& description,
        const string& location
    );

	Department* findDepartment(int departmentID);
	bool removeDepartment(int departmentID);
	bool departmentExists(int departmentID);

	// Department update operations
	bool updateDepartmentName(int departmentID, const string& newName);
	bool updateDepartmentDescription(int departmentID, const string& newDescription);
	bool updateDepartmentLocation(int departmentID, const string& newLocation);

	// Department doctor management
	bool addDoctorToDepartment(int departmentID, int doctorID);
	bool removeDoctorFromDepartment(int departmentID, int doctorID);
	bool isDoctorFromDepartment(int departmentID, int doctorID);
	int findDoctorsDepartment(int doctorID);

	// Department Display operations
	void displayAllDepartments();
	void displayDepartmentDoctors(int departmentID);

    // ---------------- DOCTOR OPERATIONS ----------------

    int registerDoctor(
        int departmentID,
        const string& name,
        const string& phone,
        const string& specialization,
        bool availability = true
	);

	bool removeDoctor(int doctorID);
	bool doctorExists(int doctorID);
	Doctor* findDoctor(int doctorID);

	// Doctor update operations
	bool updateDoctorDepartment(int doctorID, int newDepartmentID);
	bool updateDoctorName(int doctorID, const string& newName);
	bool updateDoctorPhone(int doctorID, const string& newPhone);
	bool updateDoctorSpecialization(int doctorID, const string& newSpecialization);
	bool updateDoctorAvailability(int doctorID, bool newAvailability);

	// Doctor Display operations
	void displayAllDoctors();
	void displayAvailableDoctors();
	void displayDoctorsByDepartment(int departmentID);

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

    // ---------------- SYMPTOM OPERATIONS ----------------

	vector<Symptom> getAvailableSymptoms(const string& departmentName); // Wrapper for CLI
	string symptomToString(Symptom symptom); // Wrapper for CLI

    // ---------------- FILE OPERATIONS ----------------

    bool saveHospitalData();
    bool loadHospitalData();

};