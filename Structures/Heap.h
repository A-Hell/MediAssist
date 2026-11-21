#pragma once
#include "Common.h"

/*
	Array based implementation of max heap
	Sorts appointemnts based on Triage Score
*/
class MaxHeap
{
	struct Node
	{
		int appointmentID, triageScore;
		Node() : appointmentID(0), triageScore(0){}
	};

	Node* heap;
	const int capacity;
	int size;

	// Private Methods
	void heapifyUp(int index);
	void heapifyDown(int index);

public:
	// Public Interfaces
	MaxHeap(int capacity): capacity(capacity), size(0) { heap = new Node[capacity];}
	bool insert(int appointmentID, int triageScore); 
	bool remove(int appointmentID);
	int extractMax(); // returns appointment with highest triage score, -1 if empty
	void display();
	~MaxHeap() { delete[] heap; }
};