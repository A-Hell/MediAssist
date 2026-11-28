#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Common.h"
#include "../Managers/DepartmentManager.h"
#include "../Managers/DoctorManager.h"
#include "../Managers/PatientManager.h"
#include "../Managers/AppointmentManager.h"

class FileManager
{
public:
    // Department file handling
    static bool saveDepartments(const DepartmentManager& departmentManager, const string& filename = "Data/departments.txt");
    static bool loadDepartments(DepartmentManager& departmentManager, const string& filename = "Data/departments.txt");

    // Doctor file handling
    static bool saveDoctors(const DoctorManager& doctorManager, const string& filename = "Data/doctors.txt");
    static bool loadDoctors(DoctorManager& doctorManager, const string& filename = "Data/doctors.txt");

    // Patient file handling
    static bool savePatients(const PatientManager& patientManager, const string& filename = "Data/patients.txt");
    static bool loadPatients(PatientManager& patientManager, const string& filename = "Data/patients.txt");

    // Appointment file handling
    static bool saveAppointments(const AppointmentManager& appointmentManager, const string& filename = "Data/appointments.txt");
    static bool loadAppointments(AppointmentManager& appointmentManager, const string& filename = "Data/appointments.txt");

    // Save and load all hospital data
    static bool saveAll(const PatientManager& patientManager, const DepartmentManager& departmentManager, const DoctorManager& doctorManager, const AppointmentManager& appointmentManager);
    static bool loadAll(PatientManager& patientManager, DepartmentManager& departmentManager, DoctorManager& doctorManager, AppointmentManager& appointmentManager);
};

#endif
