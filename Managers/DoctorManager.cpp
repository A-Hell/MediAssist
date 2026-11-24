#include "DoctorManager.h"

// Doctor Management Functions

int DoctorManager::registerDoctor(int departmentId, const string& name, const string& phone, const string& specialization, bool availability) 
{
	Doctor newDoctor(departmentId, name, phone, specialization, availability);
	doctors.push_back(newDoctor);
	return newDoctor.getDoctorId();
}

bool DoctorManager::removeDoctor(int doctorId) 
{
	int size = doctors.size();

	for (int i = 0; i < size; ++i)
		if (doctors[i].getDoctorId() == doctorId)
		{
			doctors.erase(doctors.begin() + i);
			return true;
		}
	return false;
}

bool DoctorManager::doctorExists(int doctorId) const
{
	int size = doctors.size();
	for (int i = 0; i < size; ++i)
		if (doctors[i].getDoctorId() == doctorId)
			return true;
	return false;
}

Doctor* DoctorManager::searchDoctor(int doctorId)
{
	int size = doctors.size();
	for (int i = 0; i < size; ++i) 
		if (doctors[i].getDoctorId() == doctorId)
			return &doctors[i];
	return nullptr;
}


// Update Functions for Doctor Attributes

bool DoctorManager::updateDoctorDepartment(int doctorId, int newDepartmentId) 
{
	Doctor* doctor = searchDoctor(doctorId);
	if (doctor)
	{
		doctor->setDepartmentId(newDepartmentId);
		return true;
	}
	return false;
}

bool DoctorManager::updateDoctorName(int doctorId, const string& newName) 
{
	Doctor* doctor = searchDoctor(doctorId);
	if (doctor)
	{
		doctor->setName(newName);
		return true;
	}
	return false;
}

bool DoctorManager::updateDoctorPhone(int doctorId, const string& newPhone) 
{
	Doctor* doctor = searchDoctor(doctorId);
	if (doctor)
	{
		doctor->setPhone(newPhone);
		return true;
	}
	return false;
}

bool DoctorManager::updateDoctorSpecialization(int doctorId, const string& newSpecialization) 
{
	Doctor* doctor = searchDoctor(doctorId);
	if (doctor)
	{
		doctor->setSpecialization(newSpecialization);
		return true;
	}
	return false;
}

bool DoctorManager::updateDoctorAvailability(int doctorId, bool newAvailability) 
{
	Doctor* doctor = searchDoctor(doctorId);
	if (doctor)
	{
		doctor->setAvailability(newAvailability);
		return true;
	}
	return false;
}

// Display Functions

void DoctorManager::displayDoctors() 
{
	if (doctors.empty())
	{
		cout << RED << "No doctors registered." << RESET << endl;
		return;
	}

	int size = doctors.size();
	for (int i = 0; i < size; ++i) 
		cout << doctors[i] << endl;
}

void DoctorManager::displayAvailableDoctors() 
{
	bool found = false;
	int size = doctors.size();
	for (int i = 0; i < size; ++i) 
		if (doctors[i].isAvailable()) 
		{
			cout << doctors[i] << endl;
			found = true;
		}
	if (!found)
		cout << RED << "No available doctors found." << RESET << endl;
}

void DoctorManager::displayDoctorsByDepartment(int departmentID) 
{
	bool found = false;
	int size = doctors.size();
	for (int i = 0; i < size; ++i) 
		if (doctors[i].getDepartmentId() == departmentID) 
		{
			cout << doctors[i] << endl;
			found = true;
		}
	if (!found)
		cout << RED << "No doctors found in department ID " << departmentID << "." << RESET << endl;
}