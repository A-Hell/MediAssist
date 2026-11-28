
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Common.h"
#include "../models/Patient.h"

class HashTable
{
private:

    // Each Node stores one complete Patient record and We use linked lists so multiple patients can share the same bucket.
    struct Node
    {
        Patient patient;
        Node* next;

        Node(const Patient& p) : patient(p), next(NULL) {}
    };

    // This is an array of buckets where each bucket points to the first Node of its linked list.
    Node** table;

    // Capacity is the total number of buckets and size is the total number of patients currently stored.
    int capacity;
    int size;

    // This calculates which bucket a patient should go into using their ID and modulus keeps the index within capacity range.
    int hashFunction(int patientID)
    {
        return patientID % capacity;
    }

    friend class FileManager;

public:

    // Creates the Hash Table with the given capacity. If none is provided 10 buckets are used by default.
    HashTable(int capacity = 10)
    {
        // Make sure we don't create a Hash Table with an invalid capacity.
        if (capacity <= 0)
        {
            capacity = 10;
        }

        this->capacity = capacity;
        size = 0;

        // Creates an array where each position will store a Node pointer.
        table = new Node * [capacity];

        // Sets every pointer to null as initially buckets are empty.
        for (int i = 0; i < capacity; i++)
        {
            table[i] = NULL;
        }
    }

    // Adds a new patient to the Hash Table.
    bool insert(Patient& patient)
    {
        int patientID = patient.getPatientID();

        // Patient IDs must be positive.
        if (patientID <= 0)
        {
            return false;
        }
        // Find the bucket where this patient should be stored.
        int index = hashFunction(patientID);

        // Start from the first Node in that bucket.
        Node* current = table[index];

        // Check the entire linked list to make sure this ID isn't already stored (To avoid duplicates)
        while (current != NULL)
        {
            if (current->patient.getPatientID() == patientID)
            {
                return false;
            }
            current = current->next;
        }

        Node* newNode = new Node(patient);

        //Connect the new node to the current (first node in the bucket). This handles collisions using Separate Chaining.
        newNode->next = table[index];
        table[index] = newNode;

        // One more patient added.
        size++;
        return true;
    }

    // Finds a patient using their ID and returns a pointer to their record.
    Patient* search(int patientID)
    {
        // Invalid ID can't be searched.
        if (patientID <= 0)
        {
            return NULL;
        }

        // Calculate the bucket where this patient should be.
        int index = hashFunction(patientID);

        // Start searching from the first Node in that bucket.
        Node* current = table[index];

        // Traverse the linked list until we find the patient or reach its end.
        while (current != NULL)
        {
            // Check whether the current Node contains the ID we're looking for.
            if (current->patient.getPatientID() == patientID)
            {
                return &current->patient;
            }
            current = current->next;
        }

        //If no patient was found with that ID, Null is returned.
        return NULL;
    }

    // Updates the information of a patient who already exists in the Hash Table.
    bool update(int patientID, Patient& updatedPatient)
    {
        // Make sure the ID is valid and the updated record belongs to the same patient. 
        // Patient ID must never change.
        if (patientID <= 0 || updatedPatient.getPatientID() != patientID)
        {
            return false;
        }

        // Find the patient whose information needs to be updated.
        Patient* patient = search(patientID);

        // If no patient then no update.
        if (patient == NULL)
        {
            return false;
        }

        // Replace the existing patient's information with the updated record. The ID remains the same.
        *patient = updatedPatient;

        return true;
    }

    // Removes a patient from the Hash Table using their ID.
    bool remove(int patientID)
    {
        // Check that the given ID is valid.
        if (patientID <= 0)
        {
            return false;
        }
        // Find the bucket that contains this patient.
        int index = hashFunction(patientID);

        // Current helps us locate the Node we want to delete.
        // Previous keeps track of the Node immediately before it.
        Node* current = table[index];
        Node* previous = NULL;

        // Search through the linked list in this bucket.
        while (current != NULL)
        {
            // Check whether we have found the patient we want to remove.
            if (current->patient.getPatientID() == patientID)
            {
                // If previous is NULL, the Node we're deleting is the first Node in the linked list.
                if (previous == NULL)
                {
                    // Move the bucket's starting pointer to the next Node.
                    table[index] = current->next;
                }
                else
                {
                    // Otherwise, connect the previous Node directly to the Node after the one we're deleting.
                    previous->next = current->next;
                }

                // The Node is no longer needed, so free its memory.
                delete current;

                // One less patient in the hash table.
                size--;
                return true;
            }
            previous = current;
            current = current->next;
        }

        // If no patient found.
        return false;
    }

    // Checks whether a particular patient ID exists in the Hash Table.
    bool contains(int patientID)
    {
        if (patientID <= 0)
        {
            return false;
        }

        // Calculate the bucket where the patient should be stored.
        int index = hashFunction(patientID);

        // Start from the first Node in that bucket.
        Node* current = table[index];

        // Search through the linked list for the given ID.
        while (current != NULL)
        {
            if (current->patient.getPatientID() == patientID)
            {
                //Patient Found, return true.
                return true;
            }

            // Move to the next Node and continue searching.
            current = current->next;
        }

        // No patient found.
        return false;
    }

    // Displays all the buckets and the patients stored inside them.
    void display()
    {
        cout << BOLD << "\nHASH TABLE" << RESET << endl;

        // Visit every bucket in the array.
        for (int i = 0; i < capacity; i++)
        {
            cout << "Bucket " << i << ": ";
            Node* current = table[i];
            while (current != NULL)
            {
                cout << "[ID: " << current->patient.getPatientID() << ", Name: " << current->patient.getName() << "]";
                current = current->next;

                // Print an arrow only when another Node exists.
                if (current != NULL)
                {
                    cout << " -> ";
                }
            }

            // NULL marks the end of this bucket's linked list.
            cout << " -> NULL" << endl;
        }

        // Display how many patients are stored and how many buckets exist.
        cout << "\nTotal Patients: " << size << endl;
        cout << "Capacity: " << capacity << endl;
    }

    // Frees all the Nodes we created dynamically.
    ~HashTable()
    {
        // Go through every bucket in the array.
        for (int i = 0; i < capacity; i++)
        {
            Node* current = table[i];

            // Delete every Node in this bucket's linked list.
            while (current != NULL)
            {
                // Save the current Node so we can delete it.
                Node* temp = current;

                // Move current forward before deleting the Node.
                current = current->next;
                // Free the memory occupied by the saved Node.
                delete temp;
            }
        }
        // All Nodes have been deleted, so we can now delete the bucket array.
        delete[] table;
    }
};

#endif