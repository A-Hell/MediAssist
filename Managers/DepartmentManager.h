#pragma once
#include "Common.h"
#include "../Models/Department.h"

class FileManager;

class DepartmentManager
{
	vector<Department> departments;
	friend class FileManager;

public:
	// Department Management Functions
	int createDepartment(const string& name, const string& description, const string& location);
	bool removeDepartment(int departmentID);
	bool departmentExists(int departmentID);
	Department* searchDepartment(int departmentID);

	// Update Functions
	bool updateDepartmentName(int departmentID, const string& newName);
	bool updateDepartmentDescription(int departmentID, const string& newDescription);
	bool updateDepartmentLocation(int departmentID, const string& newLocation);

	// Doctor Functions
	int	 findDoctorsDepartment(int doctorID);
	bool  isDoctorFromDepartment(int departmentID, int doctorID);	
	bool addDoctorToDepartment(int departmentID, int doctorID);
	bool removeDoctorFromDepartment(int departmentID, int doctorID);

	// Data Retrieval Functions
	vector<Department*> getAllDepartments();

	// Display functions
	void displayDepartments();
	void displayDepartmentDoctors(int departmentID);
};