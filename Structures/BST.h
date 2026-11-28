#pragma once
#pragma once
#include "Common.h"
#include "../Models/Appointment.h"
#include <queue>

/*
	Binary Search Tree for storing and managing appointments
	Sorted by appointment date and time
	Stores complete Appointment objects
*/
class BST
{
	struct Node
	{
		Appointment appointment;
		Node* left;
		Node* right;
		Node(const Appointment& app) : appointment(app), left(nullptr), right(nullptr) {}
	};
	Node* root;

	// Private Methods
	Node* insert(Node* node, const Appointment& appointment)
	{
		if (!node)
		{
			return new Node(appointment);
		}

		// Compare date and time to decide where to insert
		if (appointment.getAppointmentDate() < node->appointment.getAppointmentDate() || 
			(appointment.getAppointmentDate() == node->appointment.getAppointmentDate() && 
			 appointment.getAppointmentTime() < node->appointment.getAppointmentTime()))
			node->left = insert(node->left, appointment);
		else
			node->right = insert(node->right, appointment); // store duplicate date|time values on right

		return node;
	}

	Node* remove(Node* node, int appointmentID, const string& date, const string& time)
	{
		if (!node)
			return nullptr;

		// Compare date and time to find the node
		if (node->appointment.getAppointmentID() == appointmentID && 
			node->appointment.getAppointmentDate() == date && 
			node->appointment.getAppointmentTime() == time)
		{
			// Node to be deleted found
			if (node->left == nullptr)
			{
				Node* temp = node->right;
				delete node;
				return temp;
			}
			else if (node->right == nullptr)
			{
				Node* temp = node->left;
				delete node;
				return temp;
			}
			// Case: 2 Children - replace with inorder successor
			else
			{
				Node* minNode = node->right;
				while (minNode->left)
					minNode = minNode->left;

				node->appointment = minNode->appointment;
				node->right = remove(node->right, minNode->appointment.getAppointmentID(), 
					minNode->appointment.getAppointmentDate(), minNode->appointment.getAppointmentTime());
			}
		}
		else if (date < node->appointment.getAppointmentDate() || 
				(date == node->appointment.getAppointmentDate() && time < node->appointment.getAppointmentTime()))
			node->left = remove(node->left, appointmentID, date, time);
		else
			node->right = remove(node->right, appointmentID, date, time);

		return node;
	}

	Node* search(Node* node, int appointmentID, const string& date, const string& time) const
	{
		if (!node)
			return nullptr;

		if (node->appointment.getAppointmentID() == appointmentID && 
			node->appointment.getAppointmentDate() == date && 
			node->appointment.getAppointmentTime() == time)
			return node;
		else if (date < node->appointment.getAppointmentDate() || 
				(date == node->appointment.getAppointmentDate() && time < node->appointment.getAppointmentTime()))
			return search(node->left, appointmentID, date, time);
		else
			return search(node->right, appointmentID, date, time);
	}

	void inorderTraversal(Node* node) const
	{
		if (!node)
			return;
		inorderTraversal(node->left);
		cout << node->appointment << endl;
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

	friend class FileManager;

public:
	// Public Interfaces
	BST() : root(nullptr) {}

	// Insert an appointment into the BST
	void insert(const Appointment& appointment)
	{
		if (appointment.getAppointmentID() <= 0 || appointment.getAppointmentDate().empty() || appointment.getAppointmentTime().empty())
			throw invalid_argument("Invalid appointment data");
		root = insert(root, appointment);
	}

	// Remove an appointment based on appointmentID, date, and time
	void remove(int appointmentID, const string& date, const string& time)
	{ 
		root = remove(root, appointmentID, date, time); 
	}

	// Search for an appointment, returns pointer to Appointment object if found, nullptr otherwise
	Appointment* search(int appointmentID, const string& date, const string& time)
	{
		Node* res = search(root, appointmentID, date, time);
		if (res)
			return &(res->appointment);
		return nullptr;
	}

	// BFS Search for appointment by ID only
	Appointment* search(int appointmentID)
	{
		if (!root)
			return nullptr;

		queue<Node*> q;
		q.push(root);

		while (!q.empty())
		{
			Node* cur = q.front();
			q.pop();

			if (cur->appointment.getAppointmentID() == appointmentID)
				return &(cur->appointment);

			if (cur->left)
				q.push(cur->left);

			if (cur->right)
				q.push(cur->right);
		}

		return nullptr;
	}

	// Display all appointments in chronological order
	void display() const
	{
		cout << "Appointments in chronological order:" << endl << endl;
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
	~BST() 
	{ 
		root = postOrderDelete(root);
	}
};