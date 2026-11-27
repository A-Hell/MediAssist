#include "HospitalSystem.h"

// ---------------- PATIENT OPERATIONS ----------------

int HospitalSystem::registerPatient(string name,int age,string gender,string phone,string address,double height,double weight)
{ return patientManager.registerPatient(name, age, gender, phone, address, height, weight); }

const Patient* HospitalSystem::findPatient(int patientID) 
{ return patientManager.searchPatient(patientID);}

bool HospitalSystem::updatePatientName(int patientID, string name) 
{return patientManager.updateName(patientID, name);}

bool HospitalSystem::updatePatientAge(int patientID, int age) 
{return patientManager.updateAge(patientID, age); }

bool HospitalSystem::updatePatientGender(int patientID, string gender) 
{return patientManager.updateGender(patientID, gender); }

bool HospitalSystem::updatePatientPhone(int patientID, string phone) 
{ return patientManager.updatePhone(patientID, phone); }

bool HospitalSystem::updatePatientAddress(int patientID, string address) 
{ return patientManager.updateAddress(patientID, address); }

bool HospitalSystem::updatePatientHeight(int patientID, double height) 
{ return patientManager.updateHeight(patientID, height);}

bool HospitalSystem::updatePatientWeight(int patientID, double weight) 
{ return patientManager.updateWeight(patientID, weight); }

bool HospitalSystem::removePatient(int patientID) 
{ return patientManager.removePatient(patientID); }

void HospitalSystem::displayAllPatients() 
{ patientManager.displayPatients();}

bool HospitalSystem::patientExists(int patientID)
{
    Patient* p = patientManager.searchPatient(patientID);
    if (p)
        return true;
    else
        return false;
}

// ---------------- DEPARTMENT OPERATIONS ----------------

// Add retrieval and management operations here as needed.

// ---------------- DOCTOR OPERATIONS ----------------

// Add retrieval and management operations here as needed.

// ---------------- APPOINTMENT OPERATIONS ----------------

int HospitalSystem::createAppointment(int patientID, int departmentID, const vector<Symptom>& symptoms, const string& date, const string& time){
    return appointmentManager.createAppointment(patientID, departmentID, symptoms, date, time);
}

const Appointment* HospitalSystem::findAppointment(int appointmentID){
    return appointmentManager.searchAppointment(appointmentID);
}

bool HospitalSystem::updateAppointmentDate(int appointmentID, const string& newDate) {
    return appointmentManager.updateAppointmentDate(appointmentID, newDate);
}

bool HospitalSystem::updateAppointmentTime(int appointmentID, const string& newTime) {
    return appointmentManager.updateAppointmentTime(appointmentID, newTime);
}

bool HospitalSystem::updateAppointmentDepartment(int appointmentID, int newDepartmentID) {
    return appointmentManager.updateAppointmentDepartment(appointmentID, newDepartmentID);
}

bool HospitalSystem::cancelAppointment(int appointmentID) {
    return appointmentManager.cancelAppointment(appointmentID);
}

bool HospitalSystem::completeAppointment(int appointmentID) {
    return appointmentManager.completeAppointment(appointmentID);
}

bool HospitalSystem::setAppointmentWaiting(int appointmentID) {
    return appointmentManager.setAppointmentWaiting(appointmentID);
}

bool HospitalSystem::addSymptomToAppointment(int appointmentID, Symptom symptom) {
    return appointmentManager.addSymtomToAppointment(appointmentID, symptom);
}

bool HospitalSystem::removeSymptomFromAppointment(int appointmentID, Symptom symptom) {
    return appointmentManager.removeSymptomFromAppointment(appointmentID, symptom);
}

void HospitalSystem::displayAllAppointments() {
    appointmentManager.displayAppointments();
}

// ---------------- TRIAGE OPERATIONS ----------------

// Waiting-list and doctor-assignment workflows will go here.