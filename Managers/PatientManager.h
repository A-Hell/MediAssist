#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

#include "../models/Patient.h"
#include "../structures/HashTable.h"

class PatientManager
{
private:
    // Stores all registered patients using our Hash Table.
    HashTable patientTable;

public:
    // Creates the PatientManager with an empty Hash Table.
    PatientManager(int capacity = 10) : patientTable(capacity) {}

    int registerPatient(string name, int age, string gender, string phone, string address, double height, double weight)
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
    Patient* searchPatient(int patientID)
    {
        return patientTable.search(patientID);
    }

    // Updates the information of an existing patient.
    bool updatePatient(int patientID, string name, int age, string gender, string phone, string address, double height, double weight)
    {
        // Find the existing patient first.
        Patient* patient = patientTable.search(patientID);

        // We cannot update a patient who doesn't exist.
        if (patient == NULL)
        {
            return false;
        }

        // Make a copy so we can update the information without generating a new Patient ID.
        Patient updatedPatient = *patient;

        // PatientManager is a friend of Patient so it can access these private attributes directly.
        updatedPatient.name = name;
        updatedPatient.age = age;
        updatedPatient.gender = gender;
        updatedPatient.phone = phone;
        updatedPatient.address = address;
        updatedPatient.height = height;
        updatedPatient.weight = weight;

        return patientTable.update(patientID, updatedPatient);
    }

    // Removes a patient using their ID.
    bool removePatient(int patientID)
    {
        return patientTable.remove(patientID);
    }

    // Displays all registered patients.
    void displayPatients()
    {
        patientTable.display();
    }
};

#endif