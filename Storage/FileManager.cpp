
#include "FileManager.h"
#include <fstream>
#include <iomanip>

// ---------------- DEPARTMENT FILE OPERATIONS ----------------

// Save all department details in the file
bool FileManager::saveDepartments(const DepartmentManager& departmentManager, const string& filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    file << "MEDIASSIST_DEPARTMENTS_V1" << endl;
    file << "DepartmentCount " << departmentManager.departments.size() << endl;

    for (size_t i = 0; i < departmentManager.departments.size(); i++)
    {
        const Department& department = departmentManager.departments[i];

        file << endl;
        file << "DepartmentID " << department.departmentId << endl;
        file << "Name " << quoted(department.name) << endl;
        file << "Description " << quoted(department.description) << endl;
        file << "Location " << quoted(department.location) << endl;
        file << "DoctorCount " << department.doctorIds.size() << endl;

        for (size_t j = 0; j < department.doctorIds.size(); j++)
        {
            file << "DoctorID " << department.doctorIds[j] << endl;
        }
    }

    return file.good();
}


// Load all department details from the file
bool FileManager::loadDepartments(DepartmentManager& departmentManager, const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    string header, label;
    int count;

    if (!(file >> header))
    {
        return false;
    }

    if (header != "MEDIASSIST_DEPARTMENTS_V1")
    {
        return false;
    }

    if (!(file >> label >> count) || label != "DepartmentCount" || count < 0)
    {
        return false;
    }

    struct DepartmentData
    {
        int id;
        string name;
        string description;
        string location;
        vector<int> doctorIds;
    };

    vector<DepartmentData> loadedData;
    int highestID = 0;

    for (int i = 0; i < count; i++)
    {
        DepartmentData data;
        int doctorCount;

        if (!(file >> label >> data.id) || label != "DepartmentID" || data.id <= 0)
        {
            return false;
        }

        if (!(file >> label >> quoted(data.name)) || label != "Name")
        {
            return false;
        }

        if (!(file >> label >> quoted(data.description)) || label != "Description")
        {
            return false;
        }

        if (!(file >> label >> quoted(data.location)) || label != "Location")
        {
            return false;
        }

        if (!(file >> label >> doctorCount) || label != "DoctorCount" || doctorCount < 0)
        {
            return false;
        }

        for (int j = 0; j < doctorCount; j++)
        {
            int doctorID;

            if (!(file >> label >> doctorID) || label != "DoctorID" || doctorID <= 0)
            {
                return false;
            }

            // Check for duplicate doctor IDs in one department
            for (size_t k = 0; k < data.doctorIds.size(); k++)
            {
                if (data.doctorIds[k] == doctorID)
                {
                    return false;
                }
            }

            data.doctorIds.push_back(doctorID);
        }

        // Check for duplicate department IDs
        for (size_t j = 0; j < loadedData.size(); j++)
        {
            if (loadedData[j].id == data.id)
            {
                return false;
            }
        }

        if (data.id > highestID)
        {
            highestID = data.id;
        }

        loadedData.push_back(data);
    }

    vector<Department> loadedDepartments;

    for (size_t i = 0; i < loadedData.size(); i++)
    {
        Department department(loadedData[i].name, loadedData[i].description, loadedData[i].location);

        department.departmentId = loadedData[i].id;
        department.doctorIds = loadedData[i].doctorIds;

        loadedDepartments.push_back(department);
    }

    departmentManager.departments.swap(loadedDepartments);

    if (highestID > Department::counter)
    {
        Department::counter = highestID;
    }

    return true;
}


// ---------------- DOCTOR FILE OPERATIONS ----------------

// Save all doctor details in the file
bool FileManager::saveDoctors(const DoctorManager& doctorManager, const string& filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    file << "MEDIASSIST_DOCTORS_V1" << endl;
    file << "DoctorCount " << doctorManager.doctors.size() << endl;

    for (size_t i = 0; i < doctorManager.doctors.size(); i++)
    {
        const Doctor& doctor = doctorManager.doctors[i];

        file << endl;
        file << "DoctorID " << doctor.doctorId << endl;
        file << "DepartmentID " << doctor.departmentId << endl;
        file << "Name " << quoted(doctor.name) << endl;
        file << "Phone " << quoted(doctor.phone) << endl;
        file << "Specialization " << quoted(doctor.specialization) << endl;
        file << "Availability " << doctor.availability << endl;
    }

    return file.good();
}


// Load all doctor details from the file
bool FileManager::loadDoctors(DoctorManager& doctorManager, const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    string header, label;
    int count;

    if (!(file >> header))
    {
        return false;
    }

    if (header != "MEDIASSIST_DOCTORS_V1")
    {
        return false;
    }

    if (!(file >> label >> count) || label != "DoctorCount" || count < 0)
    {
        return false;
    }

    vector<Doctor> loadedDoctors;
    int highestID = 0;

    for (int i = 0; i < count; i++)
    {
        int id, departmentID, availability;
        string name, phone, specialization;

        if (!(file >> label >> id) || label != "DoctorID" || id <= 0)
        {
            return false;
        }

        if (!(file >> label >> departmentID) || label != "DepartmentID" || departmentID <= 0)
        {
            return false;
        }

        if (!(file >> label >> quoted(name)) || label != "Name")
        {
            return false;
        }

        if (!(file >> label >> quoted(phone)) || label != "Phone")
        {
            return false;
        }

        if (!(file >> label >> quoted(specialization)) || label != "Specialization")
        {
            return false;
        }

        if (!(file >> label >> availability) || label != "Availability" ||
            (availability != 0 && availability != 1))
        {
            return false;
        }

        // Check for duplicate doctor IDs
        for (size_t j = 0; j < loadedDoctors.size(); j++)
        {
            if (loadedDoctors[j].doctorId == id)
            {
                return false;
            }
        }

        Doctor doctor(departmentID, name, phone, specialization, availability == 1);

        doctor.doctorId = id;

        if (id > highestID)
        {
            highestID = id;
        }

        loadedDoctors.push_back(doctor);
    }

    doctorManager.doctors.swap(loadedDoctors);

    if (highestID > Doctor::counter)
    {
        Doctor::counter = highestID;
    }

    return true;
}


// ---------------- SAVE AND LOAD BOTH ----------------

// Save both departments and doctors
bool FileManager::saveAll(const DepartmentManager& departmentManager, const DoctorManager& doctorManager)
{
    if (!saveDepartments(departmentManager))
    {
        return false;
    }

    if (!saveDoctors(doctorManager))
    {
        return false;
    }

    return true;
}


// Load both departments and doctors
bool FileManager::loadAll(DepartmentManager& departmentManager, DoctorManager& doctorManager)
{
    int oldDepartmentCounter = Department::counter;
    int oldDoctorCounter = Doctor::counter;

    DepartmentManager tempDepartments;
    DoctorManager tempDoctors;

    if (!loadDepartments(tempDepartments))
    {
        Department::counter = oldDepartmentCounter;
        Doctor::counter = oldDoctorCounter;
        return false;
    }

    if (!loadDoctors(tempDoctors))
    {
        Department::counter = oldDepartmentCounter;
        Doctor::counter = oldDoctorCounter;
        return false;
    }

    // Check whether every doctor belongs to an existing department
    for (size_t i = 0; i < tempDoctors.doctors.size(); i++)
    {
        int departmentID = tempDoctors.doctors[i].departmentId;
        bool found = false;

        for (size_t j = 0; j < tempDepartments.departments.size(); j++)
        {
            if (tempDepartments.departments[j].departmentId == departmentID)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            Department::counter = oldDepartmentCounter;
            Doctor::counter = oldDoctorCounter;
            return false;
        }
    }

    // Check whether department doctor IDs match doctor records
    for (size_t i = 0; i < tempDepartments.departments.size(); i++)
    {
        for (size_t j = 0; j < tempDepartments.departments[i].doctorIds.size(); j++)
        {
            int doctorID = tempDepartments.departments[i].doctorIds[j];
            bool found = false;

            for (size_t k = 0; k < tempDoctors.doctors.size(); k++)
            {
                if (tempDoctors.doctors[k].doctorId == doctorID &&
                    tempDoctors.doctors[k].departmentId == tempDepartments.departments[i].departmentId)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                Department::counter = oldDepartmentCounter;
                Doctor::counter = oldDoctorCounter;
                return false;
            }
        }
    }

    // Check whether every doctor is also listed in its department
    for (size_t i = 0; i < tempDoctors.doctors.size(); i++)
    {
        int doctorID = tempDoctors.doctors[i].doctorId;
        int departmentID = tempDoctors.doctors[i].departmentId;
        bool found = false;

        for (size_t j = 0; j < tempDepartments.departments.size(); j++)
        {
            if (tempDepartments.departments[j].departmentId == departmentID)
            {
                for (size_t k = 0; k < tempDepartments.departments[j].doctorIds.size(); k++)
                {
                    if (tempDepartments.departments[j].doctorIds[k] == doctorID)
                    {
                        found = true;
                        break;
                    }
                }
                break;
            }
        }

        if (!found)
        {
            Department::counter = oldDepartmentCounter;
            Doctor::counter = oldDoctorCounter;
            return false;
        }
    }

    // Find highest department ID
    int highestDepartmentID = 0;

    for (size_t i = 0; i < tempDepartments.departments.size(); i++)
    {
        if (tempDepartments.departments[i].departmentId > highestDepartmentID)
        {
            highestDepartmentID = tempDepartments.departments[i].departmentId;
        }
    }

    // Find highest doctor ID
    int highestDoctorID = 0;

    for (size_t i = 0; i < tempDoctors.doctors.size(); i++)
    {
        if (tempDoctors.doctors[i].doctorId > highestDoctorID)
        {
            highestDoctorID = tempDoctors.doctors[i].doctorId;
        }
    }

    // Replace existing data after successful loading
    departmentManager.departments.swap(tempDepartments.departments);
    doctorManager.doctors.swap(tempDoctors.doctors);

    // Restore counters
    Department::counter = highestDepartmentID;
    Doctor::counter = highestDoctorID;

    return true;
}
