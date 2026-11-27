#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include "Common.h"
#include "../Models/Symptoms.h"

class AppointmentManager;

class Appointment
{
    int appointmentID;
    int departmentID;
    int patientID;
	vector<Symptom> symptoms;
    string appointmentTime;
    string appointmentDate;
    string status;

    inline static int counter = 1;

    friend class AppointmentManager;

    int generateAppointmentID()
    {
        return counter++;
    }

public:

    Appointment() : appointmentID(0), patientID(0), departmentID(0), appointmentDate("N/A"), appointmentTime("N/A"), status("Scheduled")
    {
        appointmentID = generateAppointmentID();
    }

    Appointment(int patientID, int departmentID, const vector<Symptom> symptoms, string appointmentDate, string appointmentTime, string status = "Scheduled") : appointmentID(0), patientID(patientID), departmentID(departmentID), symptoms(symptoms), appointmentDate(appointmentDate), appointmentTime(appointmentTime), status(status)
    { appointmentID = generateAppointmentID(); }

    string getStatus() const { return status; }
    int getPatientID() const { return patientID; }
    int getDepartmentID() const { return departmentID; }
    int getAppointmentID() const { return appointmentID; }
    string getAppointmentDate() const { return appointmentDate; }
    string getAppointmentTime() const { return appointmentTime; }
    const vector<Symptom>& getSymptoms() const { return symptoms; }

    friend ostream& operator<<(ostream& out, const Appointment& appointment)
    {
        out << BOLD + "Appointment ID: " + RESET << appointment.appointmentID << endl;
        out << BOLD + "Patient ID: " + RESET << appointment.patientID << endl;
        out << BOLD + "Department ID: " + RESET << appointment.departmentID << endl;
        out << BOLD + "Date: " + RESET << appointment.appointmentDate << endl;
        out << BOLD + "Time: " + RESET << appointment.appointmentTime << endl;
		out << BOLD + "Symptoms: " + RESET;
        out << BOLD + "Status: " + RESET << appointment.status << endl;
        return out;
    }
};

#endif
