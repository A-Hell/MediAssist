#include "HospitalSystem.h"
#include "../Storage/FileManager.h"
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

int HospitalSystem::createDepartment(const string& name, const string& description, const string& location){
    return departmentManager.createDepartment(name, description, location);
}

Department* HospitalSystem::findDepartment(int departmentID){
    return departmentManager.searchDepartment(departmentID);
}

bool HospitalSystem::removeDepartment(int departmentID){
    return departmentManager.removeDepartment(departmentID);
}

bool HospitalSystem::departmentExists(int departmentID){
    return departmentManager.departmentExists(departmentID);
}

bool HospitalSystem::updateDepartmentName(int departmentID, const string& newName){
    return departmentManager.updateDepartmentName(departmentID, newName);
}

bool HospitalSystem::updateDepartmentDescription(int departmentID, const string& newDescription){
    return departmentManager.updateDepartmentDescription(departmentID, newDescription);
}

bool HospitalSystem::updateDepartmentLocation(int departmentID, const string& newLocation){
    return departmentManager.updateDepartmentLocation(departmentID, newLocation);
}

bool HospitalSystem::addDoctorToDepartment(int departmentID, int doctorID){
    return departmentManager.addDoctorToDepartment(departmentID, doctorID);
}

bool HospitalSystem::removeDoctorFromDepartment(int departmentID, int doctorID){
    return departmentManager.removeDoctorFromDepartment(departmentID, doctorID);
}

bool HospitalSystem::isDoctorFromDepartment(int departmentID, int doctorID){
    return departmentManager.isDoctorFromDepartment(departmentID, doctorID);
}

int HospitalSystem::findDoctorsDepartment(int doctorID){
    return departmentManager.findDoctorsDepartment(doctorID);
}

void HospitalSystem::displayAllDepartments(){
    departmentManager.displayDepartments();
}

void HospitalSystem::displayDepartmentDoctors(int departmentID){
    departmentManager.displayDepartmentDoctors(departmentID);
}

// ---------------- DOCTOR OPERATIONS ----------------

int HospitalSystem::registerDoctor(int departmentID, const string& name, const string& phone, const string& specialization, bool availability){
    int ID =  doctorManager.registerDoctor(departmentID, name, phone, specialization, availability);
    if (ID != -1) {
        departmentManager.addDoctorToDepartment(departmentID, ID);
	}
	return ID;
}

bool HospitalSystem::removeDoctor(int doctorID){
    int departmentID = departmentManager.findDoctorsDepartment(doctorID);
    if (departmentID != -1) {
        departmentManager.removeDoctorFromDepartment(departmentID, doctorID);
    }
    return doctorManager.removeDoctor(doctorID);
}

bool HospitalSystem::doctorExists(int doctorID){
    return doctorManager.doctorExists(doctorID);
}

Doctor* HospitalSystem::findDoctor(int doctorID){
    return doctorManager.searchDoctor(doctorID);
}

bool HospitalSystem::updateDoctorDepartment(int doctorID, int newDepartmentID){
    int oldDepartmentID = departmentManager.findDoctorsDepartment(doctorID);
    if (oldDepartmentID != -1) {
        departmentManager.removeDoctorFromDepartment(oldDepartmentID, doctorID);
    }
    departmentManager.addDoctorToDepartment(newDepartmentID, doctorID);
    return doctorManager.updateDoctorDepartment(doctorID, newDepartmentID);
}

bool HospitalSystem::updateDoctorName(int doctorID, const string& newName){
    return doctorManager.updateDoctorName(doctorID, newName);
}

bool HospitalSystem::updateDoctorPhone(int doctorID, const string& newPhone){
    return doctorManager.updateDoctorPhone(doctorID, newPhone);
}

bool HospitalSystem::updateDoctorSpecialization(int doctorID, const string& newSpecialization){
    return doctorManager.updateDoctorSpecialization(doctorID, newSpecialization);
}

bool HospitalSystem::updateDoctorAvailability(int doctorID, bool newAvailability){
    return doctorManager.updateDoctorAvailability(doctorID, newAvailability);
}

void HospitalSystem::displayAllDoctors(){
    doctorManager.displayDoctors();
}

void HospitalSystem::displayAvailableDoctors(){
    doctorManager.displayAvailableDoctors();
}

void HospitalSystem::displayDoctorsByDepartment(int departmentID){
    doctorManager.displayDoctorsByDepartment(departmentID);
}

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

// ---------------- SYMPTOM OPERATIONS ----------------

vector<Symptom> HospitalSystem::getAvailableSymptoms(const string& departmentName){
	return ::getAvailableSymptoms(departmentName);
}

string HospitalSystem::symptomToString(Symptom symptom) {
	return ::symptomToString(symptom);
}


// ---------------- FILE OPERATIONS ----------------

bool HospitalSystem::saveHospitalData()
{
    return FileManager::saveAll(departmentManager, doctorManager);
}

bool HospitalSystem::loadHospitalData()
{
    return FileManager::loadAll(departmentManager, doctorManager);
}
