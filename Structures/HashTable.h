#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Common.h"
#include "../models/Patient.h"

class HashTable
{
private:
    struct Node
    {
        Patient patient;
        Node* next;

        Node(const Patient& p)
        {
            patient = p;
            next = NULL;
        }
    };

    Node** table;
    int capacity;
    int size;

    int hashFunction(int patientID);

public:
    HashTable(int capacity = 10);
    ~HashTable();

    bool insert(Patient& patient);
    Patient* search(int patientID);
    bool update(int patientID, Patient& updatedPatient);
    bool remove(int patientID);
    bool contains(int patientID);
    void display();
};

#endif