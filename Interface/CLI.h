#pragma once
#include "Common.h"
#include "../Managers/HospitalSystem.h"
#include "../Models/Patient.h"
#include "../Models/Appointment.h"

class CLI
{
private:
    HospitalSystem& hospital;

    // Menu functions
    void handleMainMenu();
    void showMainMenu();

    // ---------- Patient Menu Functions ----------
    void handlePatientMenu();
    void showPatientMenu();

    void registerPatient();
    void displayPatientDetails();
    void handlePatientUpdation();
    void removePatient();

    // ---------- Appointment Menu Functions ----------
    void handleAppointmentMenu();

    // ---------- Doctor Menu Functions ----------
    void handleDoctorMenu();
	void showDoctorMenu();

	void registerDoctor();
	void displayDoctorDetails();
	void handleDoctorUpdation();
	void removeDoctor();

	// ---------- Department Menu Functions ----------
	void handleDepartmentMenu();
	void showDepartmentMenu();

    void registerDepartment();
	void displayDepartmentDetails();
	void handleDepartmentUpdation();
	void removeDepartment();

	void addDoctorToDepartment();
	void removeDoctorFromDepartment();

	// ---------- Utility Functions ----------
    void clearInputBuffer();
    void createPause(const string& message);
    void clearScreen();
    void Exit();
public:
    // Receive the existing HospitalSystem instance
    CLI(HospitalSystem& hospital);

    // Starts the CLI application
    void run();
};