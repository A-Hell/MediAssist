#include "DepartmentManager.h"

int DepartmentManager::createDepartment(const string& name, const string& description, const string& location)
{
	Department newDep(name, description, location);
	departments.push_back(newDep);
	return newDep.getDepartmentId();
}

bool DepartmentManager::removeDepartment(int departmentID)
{
	size_t size = departments.size();

	for (size_t i = 0; i < size; i++)
	{
		if (departments[i].getDepartmentId() == departmentID)
		{
			departments.erase(departments.begin() + i);
			return true;
		}
	}
	return false;
}

bool DepartmentManager::departmentExists(int departmentID)
{
	if (searchDepartment(departmentID) != nullptr)
		return true;
	return false;
}

Department* DepartmentManager::searchDepartment(int departmentID)
{
	size_t size = departments.size();

	for (size_t i = 0; i < size; i++)
		if (departments[i].getDepartmentId() == departmentID)
			return &departments[i];

	return nullptr;
}

// Update Functions

bool DepartmentManager::updateDepartmentName(int departmentID, const string& newName)
{
	Department* department = searchDepartment(departmentID);
	if (department)
	{
		department->setName(newName);
		return true;
	}
	return false;
}

bool DepartmentManager::updateDepartmentDescription(int departmentID, const string& newDescription)
{
	Department* department = searchDepartment(departmentID);
	if (department)
	{
		department->setDescription(newDescription);
		return true;
	}
	return false;
}

bool DepartmentManager::updateDepartmentLocation(int departmentID, const string& newLocation)
{
	Department* department = searchDepartment(departmentID);
	if (department)
	{
		department->setLocation(newLocation);
		return true;
	}
	return false;
}

// Doctor Functions
int DepartmentManager::findDoctorsDepartment(int doctorID)
{
	size_t size = departments.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (departments[i].isInDepartment(doctorID))
			return departments[i].getDepartmentId();
	}
	return -1;
}

bool DepartmentManager::isDoctorFromDepartment(int departmentID, int doctorID)
{
	Department* department = searchDepartment(departmentID);
	if (department)
		return department->isInDepartment(doctorID);
	return false;
}

bool DepartmentManager::addDoctorToDepartment(int departmentID, int doctorID)
{
	Department* department = searchDepartment(departmentID);
	if (department)
		return department->addDoctorId(doctorID);
	return false;
}

bool DepartmentManager::removeDoctorFromDepartment(int departmentID, int doctorID)
{
	Department* department = searchDepartment(departmentID);
	if (department)
		return department->removeDoctorId(doctorID);
	return false;
}

// Data Retrieval Functions
vector<Department*> DepartmentManager::getAllDepartments()
{
	vector<Department*> departmentPointers;
	size_t size = departments.size();
	for (size_t i = 0; i < size; ++i)
		departmentPointers.push_back(&departments[i]);
	return departmentPointers;
}

// Display Functions
void DepartmentManager::displayDepartments()
{
	if (departments.empty())
	{
		cout << RED << "No departments registered." << RESET << endl;
		return;
	}

	size_t size = departments.size();

	for (size_t i = 0; i < size; ++i)
		cout << departments[i] << endl;
}

void DepartmentManager::displayDepartmentDoctors(int departmentID)
{
	Department* department = searchDepartment(departmentID);

	if (!department)
	{
		cout << RED << "Department not found." << RESET << endl;
		return;
	}

	cout << BOLD << "Doctors in Department: "
		<< department->getName() << RESET << endl;

	const vector<int>& doctorIds = department->getDoctorIds();

	if (doctorIds.empty())
	{
		cout << RED << "No doctors assigned to this department."
			<< RESET << endl;
		return;
	}

	for (int id : doctorIds)
		cout << id << endl;
}