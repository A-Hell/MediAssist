#pragma once
#include "Common.h"


class BST
{
	struct Node
	{
		int appointmentID;
		string date,time;
		Node* left;
		Node* right;
		Node() : appointmentID(0), date(""), time(""), left(nullptr), right(nullptr) {}
	};
	Node* root;

	// Private Methods
	Node* insert(Node* node, int appointmentID, const string& date, const string& time);
	Node* remove(Node* node, int appointmentID, const string& date, const string& time);
	Node* search(Node* node, int appointmentID, const string& date, const string& time);
	void inorderTraversal(Node* node);

public:
	// Public Interfaces
	BST() : root(nullptr) {}
	void insert(int appointmentID, const string& date, const string& time); // insertion based on date and time
	void remove(int appointmentID, const string& date, const string& time); // removal based on appointmentID
	int search(int appointmentID, const string& date, const string& time); // search based on date and time, returns appointmentID if found, else returns -1
	void display();
	void displayInorder();
};