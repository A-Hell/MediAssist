#ifndef QUEUE_H
#define QUEUE_H
#include "Common.h"

class Queue
{
private:
    struct Node
    {
        int patientID;
        Node* next;
    };

    Node* frontPtr;
    Node* rearPtr;
    int size;

public:
    Queue();
    ~Queue();

    void enqueue(int patientID);
    int dequeue();
    int front() const;
    bool isEmpty() const;
    int getSize() const;
    void display() const;
};

#endif