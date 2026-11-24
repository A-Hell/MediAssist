#pragma once
#include "Common.h"
#include "../models/Appointment.h"
#include "../structures/BST.h"

class AppointmentManager
{
    BST appointmentTree;

    // Private helper functions
 
    // Check if an appointment with the given ID exists in the BST
    bool appointmentExists(int appointmentID);

public:

    // Appointment operations
    int createAppointment(int patientID, int doctorId, const string& appointmentDate, const string& appointmentTime);

    Appointment* searchAppointment(int appointmentID);

    bool updateAppointmentDate(int appointmentID, const string& newDate);

	bool updateAppointmentTime(int appointmentID, const string& newTime);

	bool updateAppointmentDoctor (int appointmentID, int newDoctorId);

    bool setAppointmentWaiting(int appointmentID);

    bool cancelAppointment(int appointmentID);

    bool completeAppointment(int appointmentID);

    void displayAppointments(); 
};