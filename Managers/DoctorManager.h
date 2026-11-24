#pragma once
#include "Common.h"
#include "../Models/Doctor.h"

class DoctorManager
{

	vector<Doctor> doctors;

public:
	// Doctor management functions
	int registerDoctor(int departmentId, const string& name, const string& phone, const string& specialization, bool availability = true);
	bool removeDoctor(int doctorId); 
	bool doctorExists(int doctorId) const;
	Doctor* searchDoctor(int doctorId) const;


	// Update functions for doctor attributes
	bool updateDoctorDepartment(int doctorId, int newDepartmentId);
	bool updateDoctorName(int doctorId, const string& newName);
	bool updateDoctorPhone(int doctorId, const string& newPhone);
	bool updateDoctorSpecialization(int doctorId, const string& newSpecialization);
	bool updateDoctorAvailability(int doctorId, bool newAvailability);


	// Display functions
	void displayDoctors();
	void displayAvailableDoctors();
	void displayDoctorsByDepartment(int departmentID);
};