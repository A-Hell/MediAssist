#include "TriageManager.h"

// Finds the waiting lists belonging to a department.
TriageManager::Node* TriageManager::findDepartment(int departmentID) const
{
    Node* current = head;

    while (current != NULL)
    {
        if (current->departmentID == departmentID)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}


// Checks whether an appointment is already in any waiting list.
bool TriageManager::appointmentExists(int appointmentID) const
{
    Node* current = head;

    while (current != NULL)
    {
        if (current->routineQueue.contains(appointmentID) ||
            current->urgentHeap.search(appointmentID))
        {
            return true;
        }

        current = current->next;
    }

    return false;
}


// Checks whether the selected symptoms belong to the chosen department.
bool TriageManager::areSymptomsAllowed(const string& departmentName,
    const vector<Symptom>& symptoms) const
{
    // The department and symptom selection must both be valid.
    if (symptoms.empty())
    {
        return false;
    }

    // Get the symptoms available for this department.
    vector<Symptom> availableSymptoms = getAvailableSymptoms(departmentName);

    if (availableSymptoms.empty())
    {
        return false;
    }

    // Check every selected symptom.
    for (int i = 0; i < symptoms.size(); i++)
    {
        bool found = false;

        // Check whether the symptom is available in this department.
        for (int j = 0; j < availableSymptoms.size(); j++)
        {
            if (symptoms[i] == availableSymptoms[j])
            {
                found = true;
                break;
            }
        }

        if (found == false)
        {
            return false;
        }

        // Make sure the same symptom has not been selected twice.
        for (int j = 0; j < i; j++)
        {
            if (symptoms[i] == symptoms[j])
            {
                return false;
            }
        }
    }

    return true;
}


// Creates an empty TriageManager.
TriageManager::TriageManager(int heapCapacity)
{
    head = NULL;

    if (heapCapacity <= 0)
    {
        heapCapacity = 100;
    }

    this->heapCapacity = heapCapacity;
}


// Adds a department and creates its waiting lists.
bool TriageManager::addDepartment(int departmentID)
{
    if (departmentID <= 0 || findDepartment(departmentID) != NULL)
    {
        return false;
    }

    Node* newNode = new Node(departmentID, heapCapacity);

    // Add the new department at the beginning of the linked list.
    newNode->next = head;
    head = newNode;

    return true;
}


// Places an appointment in the correct waiting list based on its score.
bool TriageManager::insertAppointment(int departmentID, int appointmentID, int triageScore)
{
    // Check that the appointment information is valid.
    if (departmentID <= 0 || appointmentID <= 0 || triageScore <= 0)
    {
        return false;
    }

    // Find the department where the appointment belongs.
    Node* department = findDepartment(departmentID);

    if (department == NULL || appointmentExists(appointmentID))
    {
        return false;
    }

    // Decide whether the appointment is routine or urgent.
    Priority priority = determinePriority(triageScore);

    // Routine appointments are added to the Queue.
    if (priority == Priority::Routine)
    {
        department->routineQueue.enqueue(appointmentID, triageScore);
        return true;
    }

    // Urgent appointments are added to the MaxHeap.
    return department->urgentHeap.insert(appointmentID, triageScore);
}


// Calculates the score from selected symptoms and adds the appointment.
bool TriageManager::insertAppointment(int departmentID, int appointmentID,
    const string& departmentName, const vector<Symptom>& symptoms,
    int& triageScore)
{
    // Make sure the patient selected valid symptoms for this department.
    if (!areSymptomsAllowed(departmentName, symptoms))
    {
        return false;
    }

    // Calculate the points of all selected symptoms.
    int score = calculateTriageScore(symptoms);

    if (score <= 0)
    {
        return false;
    }

    // Add the appointment using its calculated score.
    if (!insertAppointment(departmentID, appointmentID, score))
    {
        return false;
    }

    triageScore = score;

    return true;
}


// Removes an appointment from the department's waiting lists.
bool TriageManager::removeAppointment(int departmentID, int appointmentID)
{
    // Check whether the given IDs are valid.
    if (departmentID <= 0 || appointmentID <= 0)
    {
        return false;
    }

    // Find the department where the appointment is stored.
    Node* department = findDepartment(departmentID);

    if (department == NULL)
    {
        return false;
    }

    int triageScore = 0;

    // First check the routine Queue.
    if (department->routineQueue.remove(appointmentID, triageScore))
    {
        return true;
    }

    // If it wasn't in the Queue, check the urgent MaxHeap.
    if (department->urgentHeap.remove(appointmentID))
    {
        return true;
    }

    return false;
}


// Updates an appointment's score and moves it if its priority changes.
bool TriageManager::updateTriageScore(int departmentID, int appointmentID, int newScore)
{
    // Check whether the given information is valid.
    if (departmentID <= 0 || appointmentID <= 0 || newScore <= 0)
    {
        return false;
    }

    // Find the department where the appointment is stored.
    Node* department = findDepartment(departmentID);

    if (department == NULL)
    {
        return false;
    }

    Priority newPriority = determinePriority(newScore);

    // Check whether the appointment is currently in the routine Queue.
    if (department->routineQueue.contains(appointmentID))
    {
        // If it is still routine, only update its score.
        if (newPriority == Priority::Routine)
        {
            return department->routineQueue.updateTriageScore(appointmentID, newScore);
        }

        // If it has become urgent, first try adding it to the MaxHeap.
        if (!department->urgentHeap.insert(appointmentID, newScore))
        {
            return false;
        }

        int oldScore = 0;

        // Remove it from the Queue after it has been added to the Heap.
        if (department->routineQueue.remove(appointmentID, oldScore))
        {
            return true;
        }

        // Undo the insertion if it could not be removed from the Queue.
        department->urgentHeap.remove(appointmentID);

        return false;
    }


    // Check whether the appointment is currently in the urgent MaxHeap.
    if (department->urgentHeap.search(appointmentID))
    {
        // If it has become routine, add it to the end of the Queue.
        if (newPriority == Priority::Routine)
        {
            department->routineQueue.enqueue(appointmentID, newScore);

            // Remove it from the Heap after adding it to the Queue.
            if (department->urgentHeap.remove(appointmentID))
            {
                return true;
            }

            // Undo the Queue insertion if removal from the Heap fails.
            int removedScore = 0;
            department->routineQueue.remove(appointmentID, removedScore);

            return false;
        }

        // If it is still urgent, remove it and insert it with the new score.
        // The existing Heap interface does not provide an update operation.
        if (department->urgentHeap.remove(appointmentID))
        {
            return department->urgentHeap.insert(appointmentID, newScore);
        }
    }

    return false;
}


// Removes and returns the next routine appointment.
int TriageManager::getNextRoutineAppointment(int departmentID)
{
    Node* department = findDepartment(departmentID);

    if (department == NULL)
    {
        return -1;
    }

    return department->routineQueue.dequeue();
}


// Removes and returns the most urgent appointment.
int TriageManager::getNextUrgentAppointment(int departmentID)
{
    Node* department = findDepartment(departmentID);

    if (department == NULL)
    {
        return -1;
    }

    return department->urgentHeap.extractMax();
}


// Displays both waiting lists belonging to a department.
bool TriageManager::displayWaitingLists(int departmentID) const
{
    Node* department = findDepartment(departmentID);

    if (department == NULL)
    {
        return false;
    }

    cout << BOLD << "\nDEPARTMENT ID: "
        << departmentID << RESET << endl;

    department->routineQueue.display();
    department->urgentHeap.display();

    return true;
}


// Displays the waiting lists of all registered departments.
void TriageManager::displayAllWaitingLists() const
{
    if (head == NULL)
    {
        cout << "No departments have waiting lists." << endl;
        return;
    }

    Node* current = head;

    while (current != NULL)
    {
        displayWaitingLists(current->departmentID);
        current = current->next;
    }
}


// Deletes all department nodes when the TriageManager is destroyed.
TriageManager::~TriageManager()
{
    while (head != NULL)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}