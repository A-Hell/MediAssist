#ifndef QUEUE_H
#define QUEUE_H

#include "Common.h"

class Queue
{
private:
    // Each Node stores an Appointment ID and points to the next Node.
    struct Node
    {
        int appointmentID;
        Node* next;

        Node(int id)
        {
            appointmentID = id;
            next = NULL;
        }
    };

    Node* frontNode;
    Node* rearNode;

    // Keeps track of the number of waiting appointments.
    int size;

public:
    Queue()
    {
        frontNode = NULL;
        rearNode = NULL;
        size = 0;
    }

    void enqueue(int appointmentID)
    {
        // Appointment IDs must be positive.
        if (appointmentID <= 0)
        {
            return;
        }

        Node* newNode = new Node(appointmentID);

        if (frontNode == NULL)
        {
            frontNode = newNode;
            rearNode = newNode;
        }
        else
        {
            // Connect the current rear Node to the new Node.
            rearNode->next = newNode;
            // The new Node is now the last Node.
            rearNode = newNode;
        }
        // One more appointment has entered the Queue.
        size++;
    }

    int dequeue()
    {
        if (frontNode == NULL)
        {
            return -1;
        }

        // Save the first Node so we can delete it.
        Node* temp = frontNode;

        // Store its Appointment ID before deleting the Node.
        int appointmentID = temp->appointmentID;

        // Move the front pointer to the next Node.
        frontNode = frontNode->next;

        if (frontNode == NULL)
        {
            rearNode = NULL;
        }

        // Free the memory occupied by the removed Node.
        delete temp;
        // One appointment has left the Queue.
        size--;

        return appointmentID;
    }

    // Returns the Appointment ID at the front without removing it.
    int front() const
    {
        if (frontNode == NULL)
        {
            return -1;
        }

        return frontNode->appointmentID;
    }

    bool isEmpty() const
    {
        return frontNode == NULL;
    }

    int getSize() const
    {
        return size;
    }

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
                cout << current->appointmentID;
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