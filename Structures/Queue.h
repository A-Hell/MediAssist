#ifndef QUEUE_H
#define QUEUE_H

#include "Common.h"

class Queue
{
private:
    // Each node represents one appointment in the waiting queue.
    struct Node
    {
        int appointmentID;
        int triageScore;
        Node* next;

        Node(int id, int score)
        {
            appointmentID = id;
            triageScore = score;
            next = NULL;
        }
    };

    Node* frontNode;
    Node* rearNode;

    // Keeps count of how many appointments are currently waiting.
    int size;

public:
    Queue()
    {
        frontNode = NULL;
        rearNode = NULL;
        size = 0;
    }

    // Adds a new appointment at the end of the queue.
    void enqueue(int appointmentID, int triageScore)
    {
        if (appointmentID <= 0 || triageScore < 0)
        {
            return;
        }

        Node* newNode = new Node(appointmentID, triageScore);

        // If the queue is empty, the new node becomes both front and rear.
        if (frontNode == NULL)
        {
            frontNode = newNode;
            rearNode = newNode;
        }
        else
        {
            // Otherwise, connect it after the current last node.
            rearNode->next = newNode;
            rearNode = newNode;
        }

        size++;
    }

    // Removes and returns the appointment at the front of the queue.
    int dequeue()
    {
        if (frontNode == NULL)
        {
            return -1;
        }

        Node* temp = frontNode;
        int appointmentID = temp->appointmentID;

        frontNode = frontNode->next;

        // If that was the only appointment, the queue is now empty.
        if (frontNode == NULL)
        {
            rearNode = NULL;
        }

        delete temp;
        size--;

        return appointmentID;
    }

    // Returns the first appointment without removing it.
    int front() const
    {
        if (frontNode == NULL)
        {
            return -1;
        }

        return frontNode->appointmentID;
    }

    // Checks whether there are any appointments waiting.
    bool isEmpty() const
    {
        return frontNode == NULL;
    }

    // Checks whether an appointment is already in the queue.
    bool contains(int appointmentID) const
    {
        Node* current = frontNode;

        while (current != NULL)
        {
            if (current->appointmentID == appointmentID)
            {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    // Returns the current number of waiting appointments.
    int getSize() const
    {
        return size;
    }

    // Displays all appointments currently stored in the queue.
    void display() const
    {
        cout << BOLD << "\n WAITING QUEUE " << RESET << endl;

        Node* current = frontNode;

        if (current == NULL)
        {
            cout << "Queue is empty." << endl;
        }
        else
        {
            cout << "Front -> ";

            while (current != NULL)
            {
                cout << "(" << current->appointmentID << ", " << current->triageScore << ")";

                current = current->next;

                if (current != NULL)
                {
                    cout << " -> ";
                }
            }

            cout << " -> NULL" << endl;
        }

        cout << "Total Waiting Appointments: " << size << endl;
    }

    // Updates the triage score of an appointment already in the queue.
    bool updateTriageScore(int appointmentID, int newScore)
    {
        if (newScore < 0)
        {
            return false;
        }

        Node* current = frontNode;

        while (current != NULL)
        {
            if (current->appointmentID == appointmentID)
            {
                current->triageScore = newScore;
                return true;
            }

            current = current->next;
        }

        return false;
    }

    // Removes a specific appointment from the queue.
    bool remove(int appointmentID, int& triageScore)
    {
        Node* current = frontNode;
        Node* previous = NULL;

        while (current != NULL)
        {
            if (current->appointmentID == appointmentID)
            {
                triageScore = current->triageScore;

                if (previous == NULL)
                {
                    frontNode = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                if (current == rearNode)
                {
                    rearNode = previous;
                }

                delete current;
                size--;

                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    // Deletes all remaining nodes when the queue object is destroyed.
    ~Queue()
    {
        while (frontNode != NULL)
        {
            Node* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }

        rearNode = NULL;
        size = 0;
    }
};

#endif