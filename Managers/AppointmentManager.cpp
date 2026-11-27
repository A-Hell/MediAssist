#include "AppointmentManager.h"

// AppointmentManager implementation
// TODO: Implement appointment management functionality

bool AppointmentManager::appointmentExists(int appointmentID) 
{ return appointmentTree.search(appointmentID) != nullptr; }

int AppointmentManager::createAppointment( int patientID, int departmentID , const vector<Symptom> symptoms, const string& appointmentDate, const string& appointmentTime)
{
	if (!isValidDate(appointmentDate)) 
	{
		cout << RED << "Error: Invalid date format. Please use YYYY-MM-DD." << RESET << endl;
		return -1;
	}

	if (!isValidTime(appointmentTime)) 
	{
		cout << RED << "Error: Invalid time format. Please use HH:MM." << RESET << endl;
		return -1;
		return false;
	}

	// Create a new appointment
	Appointment newAppointment(patientID, departmentID, symptoms, appointmentDate, appointmentTime);
	
	// Insert the new appointment into the BST
	appointmentTree.insert(newAppointment);

	return newAppointment.getAppointmentID();
}

Appointment* AppointmentManager::searchAppointment(int appointmentID) 
{
	Appointment* appointment = appointmentTree.search(appointmentID);
	if (appointment) 
		return appointment;
	else
	{
		cout << RED << "Error: Appointment with ID " << appointmentID << " not found." << RESET << endl;
		return nullptr;
	}
}

bool AppointmentManager::updateAppointmentDate(int appointmentID, const string& newDate)
{
	if (!isValidDate(newDate))
	{
		cout << RED << "Error: Invalid date format. Please use YYYY-MM-DD." << RESET << endl;
		return false;
	}
	Appointment* appointment = appointmentTree.search(appointmentID);

	if (appointment)
	{
		// Update and reinsert appointment in the BST
		Appointment updatedAppointment = *appointment;
		appointmentTree.remove(appointmentID, appointment->getAppointmentDate(), appointment->getAppointmentTime());
		updatedAppointment.appointmentDate = newDate;
		appointmentTree.insert(updatedAppointment);

		return true;
	}
	else
	{
		cout << RED << "Error: Appointment with ID " << appointmentID << " not found." << RESET << endl;
		return false;
	}
}

bool AppointmentManager::updateAppointmentTime(int appointmentID, const string& newTime)
{
	if (!isValidTime(newTime))
	{
		cout << RED << "Error: Invalid time format. Please use HH:MM." << RESET << endl;
		return false;
	}

	Appointment* appointment = appointmentTree.search(appointmentID);

	if (appointment)
	{
		// Update and reinsert appointment in the BST
		Appointment updatedAppointment = *appointment;
		appointmentTree.remove(appointmentID, appointment->getAppointmentDate(), appointment->getAppointmentTime());
		updatedAppointment.appointmentTime = newTime;
		appointmentTree.insert(updatedAppointment);

		return true;
	}
	else
	{
		cout << RED << "Error: Appointment with ID " << appointmentID << " not found." << RESET << endl;
		return false;
	}
}

bool AppointmentManager::updateAppointmentDepartment(int appointmentID, int newDepartmentID)
{
	Appointment* appointment = appointmentTree.search(appointmentID);

	if (appointment)
	{
		appointment->departmentID = newDepartmentID;
		return true;
	}
	else
	{
		cout << RED << "Error: Appointment with ID " << appointmentID << " not found." << RESET << endl;
		return false;
	}
}

bool AppointmentManager::setAppointmentWaiting(int appointmentID)
{
	Appointment* appointment = appointmentTree.search(appointmentID);

	if (appointment)
	{
		appointment->status = "Waiting";
		return true;
	}
	else
	{
		cout << RED << "Error: Appointment with ID " << appointmentID << " not found." << RESET << endl;
		return false;
	}
}

bool AppointmentManager::cancelAppointment(int appointmentID)
{
	Appointment* appointment = appointmentTree.search(appointmentID);

	if (appointment)
	{
		appointment->status = "Canceled";
		return true;
	}
	else
	{
		cout << RED << "Error: Appointment with ID " << appointmentID << " not found." << RESET << endl;
		return false;
	}
}

bool AppointmentManager::completeAppointment(int appointmentID)
{
	Appointment* appointment = appointmentTree.search(appointmentID);

	if (appointment)
	{
		appointment->status = "Completed";
		return true;
	}
	else
	{
		cout << RED << "Error: Appointment with ID " << appointmentID << " not found." << RESET << endl;
		return false;
	}
}

void AppointmentManager::displayAppointments()
{ appointmentTree.display(); }