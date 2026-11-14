#ifndef PATIENT_H
#define PATIENT_H
#include "Common.h"

class PatientManager;

class Patient
{
    int patientID;
    string name;
    int age;
    string gender;
    string phone;
    string address;
    double height;
    double weight;
    inline static int counter = 0;

    friend class PatientManager;

    int generatePatientID() 
    { 
        return ++counter; 
    }

public:
    Patient() : patientID(0), name("N/A"), age(0), gender("N/A"), phone("N/A"), address("N/A"), height(0.0), weight(0.0)
    {
        patientID = generatePatientID();
    }

    Patient(string name, int age, string gender, string phone, string address, double height, double weight) : patientID(0), name(name), age(age), gender(gender), phone(phone), address(address), height(height), weight(weight)
    {
        patientID = generatePatientID();
    }

    int getPatientID()
    { 
        return patientID; 
    }
    string getName() 
    { 
        return name; 
    }
    int getAge()
    { 
        return age; 
    }
    string getGender() 
    { 
        return gender; 
    }
    string getPhone() 
    {
        return phone; 
    }
    string getAddress() 
    {
        return address; 
    }
    double getHeight()
    { 
        return height; 
    }
    double getWeight() 
    { 
        return weight; 
    }

    friend ostream& operator<<(ostream& out, const Patient& patient)
    {
        out << BOLD + "Patient ID: " + RESET << patient.patientID << endl;
        out << BOLD + "Patient Name: " + RESET << patient.name << endl;
        out << BOLD + "Age: " + RESET << patient.age << endl;
        out << BOLD + "Gender: " + RESET << patient.gender << endl;
        out << BOLD + "Phone Number: " + RESET << patient.phone << endl;
        out << BOLD + "Address: " + RESET << patient.address << endl;
        out << BOLD + "Height: " + RESET << patient.height << " cm" << endl;
        out << BOLD + "Weight: " + RESET << patient.weight << " kg" << endl;

        return out;
    }
};

#endif