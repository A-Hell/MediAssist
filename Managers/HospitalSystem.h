#pragma once
#include "Common.h"
#include "../Managers/PatientManager.h"
#include "../Managers/DoctorManager.h"
#include "../Managers/AppointmentManager.h"
#include "../Managers/TriageManager.h"
#include "../Managers/DepartmentManager.h"

class HospitalSystem
{
	PatientManager patientManager;
	AppointmentManager appointmentManager;


public:

	HospitalSystem(int patientCapacity = 25); // initializes the hospital system
	bool registerPatient(); // register a new patient 

};