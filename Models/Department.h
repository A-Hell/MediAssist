#pragma once
#include "Common.h"

class DepartmentManager; // Forward declaration of DepartmentManager class

class Department
{
	int departmentId;
	string name, description, location;
	vector<int> doctorIds; // Store doctor IDs associated with this department

	inline static int counter = 0; // Static counter to generate unique department IDs
	friend class DepartmentManager;

	// Setters for friends
	void setDepartmentId(int departmentId) { this->departmentId = departmentId; }
	void setName(string name) { this->name = name; }
	void setDescription(string description) { this->description = description; }
	void setLocation(string location) { this->location = location; }

	// Functions to manage doctor IDs
	void addDoctorId(int doctorId) { if (!isInDepartment(doctorId)) doctorIds.push_back(doctorId); }
	bool removeDoctorId(int doctorId)
	{
		int size = doctorIds.size();
		for (int i = 0; i < size; i++)
		{
			if (doctorIds[i] == doctorId)
			{
				doctorIds.erase(doctorIds.begin() + i);
				return true;
			}
		}
		return false;
	}

	int generateDepartmentId() { return ++counter; } // Function to generate unique department ID

public:
	// Constructor
	Department(string name = "N/A", string description = "N/A", string location = "N/A")
		: name(name), description(description), location(location) {departmentId = generateDepartmentId();}

	// Getters
	int getDepartmentId() const { return departmentId; }
	string getName() const { return name; }
	string getDescription() const { return description; }
	string getLocation() const { return location; }
	const vector<int>& getDoctorIds() const { return doctorIds; }

	bool isInDepartment(int doctorId) const // Check if a doctor ID is in the department
	{
		int size = doctorIds.size();
		for (int i = 0; i < size; i++)
		{
			if (doctorIds[i] == doctorId)
				return true;
		}
		return false;
	}

	// Display Functions
	friend ostream& operator<<(ostream& out, const Department& department)
	{
		out << BOLD + "Department ID: " + RESET << department.departmentId << endl;
		out << BOLD + "Name: " + RESET << department.name << endl;
		out << BOLD + "Description: " + RESET << department.description << endl;
		out << BOLD + "Location: " + RESET << department.location << endl;
		out << BOLD + "Doctor IDs: " + RESET;
		if (department.doctorIds.empty())
			out << RED + "No doctors assigned" + RESET << endl;
		else
		{
			for (int id : department.doctorIds)
				out << id << " -- ";
			out << endl;
		}
		return out;
	}
};
