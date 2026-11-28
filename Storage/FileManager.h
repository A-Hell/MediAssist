#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "../Managers/DepartmentManager.h"
#include "../Managers/DoctorManager.h"

class FileManager
{
public:

    // Department file handling
    static bool saveDepartments(const DepartmentManager& departmentManager, const string& filename = "Data/departments.txt");
    static bool loadDepartments(DepartmentManager& departmentManager, const string& filename = "Data/departments.txt");

    // Doctor file handling
    static bool saveDoctors(const DoctorManager& doctorManager, const string& filename = "Data/doctors.txt");
    static bool loadDoctors(DoctorManager& doctorManager, const string& filename = "Data/doctors.txt");

    // Save and load both together
    static bool saveAll(const DepartmentManager& departmentManager, const DoctorManager& doctorManager);
    static bool loadAll(DepartmentManager& departmentManager, DoctorManager& doctorManager);
};

#endif
