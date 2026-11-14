#pragma once
#include "Common.h"

class DoctorManager; // Forward declaration of DoctorManager class

class Doctor
{
	int doctorId;
	int departmentId;
	string name;
	string phone;
	string specialization;
	bool availability;

	inline static int counter = 0; // Static counter to generate unique doctor IDs
	friend class DoctorManager; // Declare DoctorManager as a friend class

	// Setters for friend classes
	void setDoctorId(int doctorId) { this->doctorId = doctorId; }
	void setAvailability(bool availability) { this->availability = availability; }
	void setDepartmentId(int departmentId) { this->departmentId = departmentId; }
	void setName(string name) { this->name = name; }
	void setPhone(string phone) { this->phone = phone; }

	int generateDoctorId() { return ++counter; } // Function to generate unique doctor ID

public:
	//constructor
	Doctor(int departmentId = 0, string name = "N/A", string phone = "N/A", string specialization = "N/A", bool availability = false)
		: departmentId(departmentId), name(name), phone(phone), specialization(specialization), availability(availability) {doctorId = generateDoctorId();}

	// getters
	int getDoctorId() const { return doctorId; }
	int getDepartmentId() const { return departmentId; }
	string getName() const { return name; }
	string getPhone() const { return phone; }
	bool isAvailable() const { return availability; }

	friend ostream& operator<<(ostream& out, const Doctor& doctor)
	{
		out << BOLD + "Doctor ID: " + RESET << doctor.doctorId << endl;
		out << BOLD + "Name: " + RESET << doctor.name << endl;
		out << BOLD + "Phone: " + RESET << doctor.phone << endl;
		out << BOLD + "Specialization: " + RESET << doctor.specialization << endl;
		out << BOLD + "Availability: " + RESET << (doctor.availability ? GREEN + "Available" + RESET : RED + "Not Available" + RESET) << endl;
		return out;
	}
};