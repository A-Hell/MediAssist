
#ifndef TRIAGEMANAGER_H
#define TRIAGEMANAGER_H

#include "../Structures/Queue.h"
#include "../Structures/Heap.h"
#include "Symptoms.h"

class TriageManager
{
private:
    // Each node stores the waiting lists for one department.
    struct Node
    {
        int departmentID;
        Queue routineQueue;
        MaxHeap urgentHeap;
        Node* next;

        Node(int id, int capacity)
            : departmentID(id), urgentHeap(capacity)
        {
            next = NULL;
        }
    };

    Node* head;
    int heapCapacity;


    // Finds the waiting lists belonging to a department.
    Node* findDepartment(int departmentID) const;

    // Checks whether an appointment is already in any waiting list.
    bool appointmentExists(int appointmentID) const;

    // Checks whether the selected symptoms belong to the chosen department.
    bool areSymptomsAllowed(const string& departmentName,
        const vector<Symptom>& symptoms) const;


public:

    // Creates an empty TriageManager.
    TriageManager(int heapCapacity = 100);

    // Prevents copying because this class owns dynamically allocated nodes.
    TriageManager(const TriageManager&) = delete;
    TriageManager& operator=(const TriageManager&) = delete;

    // Adds a department and creates its waiting lists.
    bool addDepartment(int departmentID);

    // Adds an appointment using an already calculated triage score.
    bool insertAppointment(int departmentID, int appointmentID, int triageScore);

    // Calculates the score from selected symptoms and adds the appointment.
    bool insertAppointment(int departmentID, int appointmentID,
        const string& departmentName, const vector<Symptom>& symptoms,
        int& triageScore);

    // Removes an appointment from the department's waiting lists.
    bool removeAppointment(int departmentID, int appointmentID);

    // Updates an appointment's score and moves it if its priority changes.
    bool updateTriageScore(int departmentID, int appointmentID, int newScore);

    // Removes and returns the next routine appointment.
    int getNextRoutineAppointment(int departmentID);

    // Removes and returns the most urgent appointment.
    int getNextUrgentAppointment(int departmentID);

    // Displays both waiting lists belonging to a department.
    bool displayWaitingLists(int departmentID) const;

    // Displays the waiting lists of all registered departments.
    void displayAllWaitingLists() const;

    // Deletes all department nodes when the TriageManager is destroyed.
    ~TriageManager();
};

#endif