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