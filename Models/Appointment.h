#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include "Common.h"

class AppointmentManager;

class Appointment
{
    int appointmentID;
    int patientID;
    int doctorId;
    string appointmentDate;
    string appointmentTime;
    string status;

    inline static int counter = 1;

    friend class AppointmentManager;

    int generateAppointmentID()
    {
        return counter++;
    }

public:

    Appointment() : appointmentID(0), patientID(0), doctorId(0), appointmentDate("N/A"), appointmentTime("N/A"), status("Scheduled")
    {
        appointmentID = generateAppointmentID();
    }

    Appointment(int patientID, int doctorId, string appointmentDate, string appointmentTime, string status = "Scheduled") : appointmentID(0), patientID(patientID), doctorId(doctorId), appointmentDate(appointmentDate), appointmentTime(appointmentTime), status(status)
    {
        appointmentID = generateAppointmentID();
    }

    int getAppointmentID() const
    {
        return appointmentID; 
    }

    int getPatientID() const
    { 
        return patientID; 
    }

    int getDoctorId() const
    { 
        return doctorId; 
    }

    string getAppointmentDate() const
    { 
        return appointmentDate; 
    }

    string getAppointmentTime() const
    {
        return appointmentTime; 
    }

    string getStatus() const
    {
        return status; 
    }

    friend ostream& operator<<(ostream& out, const Appointment& appointment)
    {
        out << BOLD + "Appointment ID: " + RESET << appointment.appointmentID << endl;
        out << BOLD + "Patient ID: " + RESET << appointment.patientID << endl;
        out << BOLD + "Doctor ID: " + RESET << appointment.doctorId << endl;
        out << BOLD + "Date: " + RESET << appointment.appointmentDate << endl;
        out << BOLD + "Time: " + RESET << appointment.appointmentTime << endl;
        out << BOLD + "Status: " + RESET << appointment.status << endl;
        return out;
    }
};

#endif
