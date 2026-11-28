#pragma once
#include "Common.h"
#include "../models/Appointment.h"
#include "../structures/BST.h"

class AppointmentManager
{
    BST appointmentTree;
    friend class FileManager;
    // Private helper functions
 
    // Check if an appointment with the given ID exists in the BST
    bool appointmentExists(int appointmentID);

public:

    // Appointment operations
    int createAppointment(int patientID, int departmentID, const vector<Symptom> symptoms, const string& appointmentDate, const string& appointmentTime);

    Appointment* searchAppointment(int appointmentID);

    bool updateAppointmentDate(int appointmentID, const string& newDate);
	bool updateAppointmentTime(int appointmentID, const string& newTime);
	bool updateAppointmentDepartment (int appointmentID, int newDepartmentID);

	bool addSymtomToAppointment(int appointmentID, Symptom symptom);
    bool removeSymptomFromAppointment(int appointmentID, Symptom symptom);

    bool setAppointmentWaiting(int appointmentID);
    bool cancelAppointment(int appointmentID);
    bool completeAppointment(int appointmentID);

    void displayAppointments(); 
};