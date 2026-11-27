#include "HospitalSystem.h"

// ---------------- PATIENT OPERATIONS ----------------

int HospitalSystem::registerPatient(string name,int age,string gender,string phone,string address,double height,double weight)
{
    return patientManager.registerPatient(name, age, gender, phone, address, height, weight);
}

const Patient* HospitalSystem::findPatient(int patientID)
{
    return patientManager.searchPatient(patientID);
}

// ---------------- DEPARTMENT OPERATIONS ----------------

// Add retrieval and management operations here as needed.

// ---------------- DOCTOR OPERATIONS ----------------

// Add retrieval and management operations here as needed.

// ---------------- APPOINTMENT OPERATIONS ----------------

int HospitalSystem::createAppointment(int patientID,int departmentID,const vector<Symptom>& symptoms,const string& date,const string& time)
{
	return appointmentManager.createAppointment(patientID, departmentID, symptoms, date, time);
}

const Appointment* HospitalSystem::findAppointment(int appointmentID)
{
	return appointmentManager.searchAppointment(appointmentID);
}

bool HospitalSystem::cancelAppointment(int appointmentID)
{
	return appointmentManager.cancelAppointment(appointmentID);
}

bool HospitalSystem::completeAppointment(int appointmentID)
{
	return appointmentManager.completeAppointment(appointmentID);
}

// ---------------- TRIAGE OPERATIONS ----------------

// Waiting-list and doctor-assignment workflows will go here.