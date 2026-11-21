#pragma once
#include "Common.h"

/*
	Array based implementation of max heap
	Sorts appointments based on Triage Score
	Uses arrival number to break ties in triage score
*/
class MaxHeap
{
	struct Node
	{
		int appointmentID, triageScore, arrivalNumber;
		Node() : appointmentID(0), triageScore(0), arrivalNumber(0) {}
	};

	inline static int arrivalCounter = 0;

	Node* heap;
	const int capacity;
	int size;

	// Private Methods
	void heapifyUp(int index)
	{
		while (index > 0)
		{
			int parentIndex = (index - 1) / 2;

			if (hasHigherPriority(heap[index], heap[parentIndex]))
			{
				swap(heap[index], heap[parentIndex]);
				index = parentIndex;
			}
			else
				break;
		}
	}

	void heapifyDown(int index)
	{
		int leftChild = index * 2 + 1;
		int rightChild = index * 2 + 2;
		int largest = index;

		// Compare with left child
		if (leftChild < size && hasHigherPriority(heap[leftChild], heap[largest]))
			largest = leftChild;

		// Compare with right child
		if (rightChild < size && hasHigherPriority(heap[rightChild], heap[largest]))
			largest = rightChild;

		if (largest != index)
		{
			swap(heap[index], heap[largest]);
			heapifyDown(largest);
		}
	}

	// Helper function to compare two nodes, to avoid duplicate logic
	bool hasHigherPriority(const Node& a, const Node& b)
	{
		if (a.triageScore != b.triageScore)
			return a.triageScore > b.triageScore;

		return a.arrivalNumber < b.arrivalNumber;
	}

public:
	// Public Interfaces
	MaxHeap(int capacity): capacity(capacity), size(0) 
	{
		if (capacity <= 0)
			throw invalid_argument("Capacity must be greater than 0");

		heap = new Node[capacity];
	}

	// Insertion of appointment based on triage score, arrival number breaks ties
	bool insert(int appointmentID, int triageScore)
	{
		if (size >= capacity)
			return false;
		if (appointmentID <= 0 || triageScore < 0)
			return false;

		heap[size].appointmentID = appointmentID;
		heap[size].triageScore = triageScore;
		heap[size].arrivalNumber = arrivalCounter++;
		heapifyUp(size);
		size++;
		return true;
	}

	// searches for appointment based on appointmentID, returns true if found, false if not found
	bool search(int appointmentID)
	{
		for (int i = 0; i < size; ++i)
			if (heap[i].appointmentID == appointmentID)
				return true;
		return false;
	}

	// removes appointment based on appointmentID, returns true if removed, false if not found
	bool remove(int appointmentID) 
	{
		for (int i = 0; i < size; ++i)
		{
			if (heap[i].appointmentID == appointmentID)
			{
				heap[i] = heap[size - 1];
				size--;
				if (i < size)
				{	
					if (i > 0 && hasHigherPriority(heap[i], heap[(i - 1) / 2]))
						heapifyUp(i);
					else
						heapifyDown(i);
				}
				return true;
			}
		}
		return false;
	}


	// returns appointment with highest triage score, -1 if empty
	int extractMax() 
	{
		if (size == 0)
			return -1;
		int maxAppointmentID = heap[0].appointmentID;
		heap[0] = heap[size - 1];
		size--;
		if (size > 0)
			heapifyDown(0);
		return maxAppointmentID;
	}

	// peeks at the appointment with the highest triage score, returns -1 if empty
	int peek()
	{
		if(size == 0)
			return -1;
		return heap[0].appointmentID;
	}

	void display() const
	{
		cout << "Max Heap (AppointmentID, TriageScore, ArrivalNumber): " << endl;
		if (size == 0)
		{
			cout << "Heap is empty." << endl;
			return;
		}

		for (int i = 0; i < size; ++i)
			cout << "(" << heap[i].appointmentID << ", " << heap[i].triageScore << ", " << heap[i].arrivalNumber << ") ";
		cout << endl;
	}

	~MaxHeap() { delete[] heap; }
};