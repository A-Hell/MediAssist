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
	Node* insert(Node* node, int appointmentID, const string& date, const string& time)
	{
		if(!node)
		{
			Node* newNode = new Node();
			newNode->appointmentID = appointmentID;
			newNode->date = date;
			newNode->time = time;
			return newNode;
		}

		// Compare date and time to decide where to insert
		if (date < node->date || (date == node->date && time < node->time))
			node->left = insert(node->left, appointmentID, date, time);
		else
			node->right = insert(node->right, appointmentID, date, time); // store duplicate date|time values on right

		return node;
	}


	Node* remove(Node* node, int appointmentID, const string& date, const string& time)
	{
		if (!node)
			return nullptr;

		// Compare date and time to decide where to insert
		if (node->appointmentID == appointmentID && node->date == date && node->time == time)
		{
			// Node to be deleted found
			Node* q;
			// Deletion case
			if (node->left == nullptr)
			{
				q = node->right;
				delete node;
				node = q;
			}
			else if (node->right == nullptr)
			{
				q = node->left;
				delete node;
				node = q;
			}
			// Case: 2 Children
			else
			{
				// replace with inorder successor
				q = node->right;
				while (q->left)
					q = q->left;

				node->appointmentID = q->appointmentID;
				node->date = q->date;
				node->time = q->time;

				node->right = remove(node->right, q->appointmentID, q->date, q->time);
			}
		}
		else if (date < node->date || (date == node->date && time < node->time))
			node->left = remove(node->left, appointmentID, date, time);
		else
			node->right = remove(node->right, appointmentID, date, time);

		return node;
	}


	Node* search(Node* node, int appointmentID, const string& date, const string& time)
	{
		if (!node)
			return nullptr;

		if (node->appointmentID == appointmentID && node->date == date && node->time == time)
			return node;
		else if (date < node->date || (date == node->date && time < node->time))
			return search(node->left, appointmentID, date, time);
		else
			return search(node->right, appointmentID, date, time);
	}


	void inorderTraversal(Node* node)
	{
		if (!node)
			return;
		inorderTraversal(node->left);
		cout << "Appointment ID: " << node->appointmentID << ", Date: " << node->date << ", Time: " << node->time << endl;
		inorderTraversal(node->right);
	}

	// Post-order memory cleanup for BST
	Node* postOrderDelete(Node* node)
	{
		if (!node)
			return nullptr;
		node->left = postOrderDelete(node->left);
		node->right = postOrderDelete(node->right);
		delete node;
		return nullptr;
	}

public:
	// Public Interfaces
	BST() : root(nullptr) {}

	// Insert an appointment based on appointmentID, date, and time
	void insert(int appointmentID, const string& date, const string& time)
	{
		if (appointmentID <= 0 || date.empty() || time.empty())
			throw invalid_argument("Invalid appointment data");
		root = insert(root, appointmentID, date, time);
	}

	// Remove an appointment based on appointmentID, date, and time
	void remove(int appointmentID, const string& date, const string& time)
	{ root = remove(root, appointmentID, date, time); }

	// Search for an appointment based on appointmentID, date and time, returns appointmentID if found, else returns -1
	int search(int appointmentID, const string& date, const string& time)
	{
		Node* res = search(root, appointmentID, date, time);
		if(res)
			return res->appointmentID;
		return -1;
	}

	// Display all appointments in order
	void display()
	{
		cout << "Appointments in order:" << endl;
		if (!root)
			cout << "No appointments found." << endl;
		else 
			inorderTraversal(root);
	}

	// Public method to delete the entire tree
	void deleteTree()
	{
		root = postOrderDelete(root);
		cout << "All appointments have been deleted." << endl;
	}

	// Free memory allocated for the BST
	~BST(){ root = postOrderDelete(root);}
};