#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

#include "../models/Patient.h"
#include "../structures/HashTable.h"

class PatientManager
{
private:
    // Stores all registered patients using our Hash Table.
    HashTable patientTable;
    friend class FileManager;

public:
    // Creates the PatientManager with an empty Hash Table.
    PatientManager(int capacity = 10);

    int registerPatient(string name, int age, string gender, string phone, string address, double height, double weight);

    // Finds a patient using their ID.
    Patient* searchPatient(int patientID);

    // Updates individual patient details.
    bool updateName(int patientID, string name);
    bool updateAge(int patientID, int age);
    bool updateGender(int patientID, string gender);
    bool updatePhone(int patientID, string phone);
    bool updateAddress(int patientID, string address);
    bool updateHeight(int patientID, double height);
    bool updateWeight(int patientID, double weight);

    bool removePatient(int patientID);
    void displayPatients();
};

#endif
