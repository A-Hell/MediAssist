#include "PatientManager.h"

// Creates the PatientManager with an empty Hash Table.
PatientManager::PatientManager(int capacity) : patientTable(capacity) {}

int PatientManager::registerPatient(string name, int age, string gender, string phone, string address, double height, double weight)
{
    Patient patient(name, age, gender, phone, address, height, weight);

    // Save the automatically generated ID.
    int patientID = patient.getPatientID();

    // Store the patient in the Hash Table.
    if (patientTable.insert(patient))
    {
        return patientID;
    }

    return -1;
}

// Finds a patient using their ID.
Patient* PatientManager::searchPatient(int patientID)
{
    return patientTable.search(patientID);
}

// Updates the patient's name.
bool PatientManager::updateName(int patientID, string name)
{
    Patient* patient = patientTable.search(patientID);

    if (patient == NULL)
    {
        return false;
    }

    Patient updatedPatient = *patient;
    updatedPatient.name = name;

    return patientTable.update(patientID, updatedPatient);
}

// Updates the patient's age.
bool PatientManager::updateAge(int patientID, int age)
{
    Patient* patient = patientTable.search(patientID);

    if (patient == NULL || age <= 0)
    {
        return false;
    }

    Patient updatedPatient = *patient;
    updatedPatient.age = age;

    return patientTable.update(patientID, updatedPatient);
}

// Updates the patient's gender.
bool PatientManager::updateGender(int patientID, string gender)
{
    Patient* patient = patientTable.search(patientID);

    if (patient == NULL)
    {
        return false;
    }

    Patient updatedPatient = *patient;
    updatedPatient.gender = gender;

    return patientTable.update(patientID, updatedPatient);
}

// Updates the patient's phone number.
bool PatientManager::updatePhone(int patientID, string phone)
{
    Patient* patient = patientTable.search(patientID);

    if (patient == NULL)
    {
        return false;
    }

    Patient updatedPatient = *patient;
    updatedPatient.phone = phone;

    return patientTable.update(patientID, updatedPatient);
}

// Updates the patient's address.
bool PatientManager::updateAddress(int patientID, string address)
{
    Patient* patient = patientTable.search(patientID);

    if (patient == NULL)
    {
        return false;
    }

    Patient updatedPatient = *patient;
    updatedPatient.address = address;

    return patientTable.update(patientID, updatedPatient);
}

// Updates the patient's height.
bool PatientManager::updateHeight(int patientID, double height)
{
    Patient* patient = patientTable.search(patientID);

    if (patient == NULL || height <= 0)
    {
        return false;
    }

    Patient updatedPatient = *patient;
    updatedPatient.height = height;

    return patientTable.update(patientID, updatedPatient);
}

// Updates the patient's weight.
bool PatientManager::updateWeight(int patientID, double weight)
{
    Patient* patient = patientTable.search(patientID);

    if (patient == NULL || weight <= 0)
    {
        return false;
    }

    Patient updatedPatient = *patient;
    updatedPatient.weight = weight;

    return patientTable.update(patientID, updatedPatient);
}

// Removes a patient using their ID.
bool PatientManager::removePatient(int patientID)
{
    return patientTable.remove(patientID);
}

// Displays all registered patients.
void PatientManager::displayPatients()
{
    patientTable.display();
}