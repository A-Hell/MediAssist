
#include "CLI.h"

// Constructor that takes a reference to an existing HospitalSystem instance
CLI::CLI(HospitalSystem& hospital) : hospital(hospital) {}

// Starts the CLI 
void CLI::run() 
{
	handleMainMenu();
}

// ---------- Menu Functions ----------

void CLI::handleMainMenu()
{
	int choice;
	do {
		showMainMenu();

		cout << BOLD + GREEN + "Enter your choice: " + RESET + GRAY + ITALIC;
		cin >> choice;
		cout << RESET;

		switch (choice) {
		case 1:
			handlePatientMenu();
			break;
		case 2:
			handleAppointmentMenu();
			break;
		case 0:
			createPause("Exiting the system.Goodbye!");
			Exit();
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 0);
}

void CLI::showMainMenu()
{
	clearScreen();
	cout << BOLD + UNDERLINE + "Main Menu:" + RESET << endl;
	cout << "1: Patient Menu" << endl;
	cout << "2: Appointment Menu" << endl;
	cout << "0: Exit" << endl;
}

// ---------- Patient Menu Functions ----------
void CLI::handlePatientMenu()
{
	int choice;
	do {
		showPatientMenu();

		cout << BOLD + GREEN + "Enter your choice: " + RESET + GRAY + ITALIC;
		cin >> choice;
		cout << RESET;

		switch (choice) {
		case 1:
			registerPatient();
			break;
		case 2:
			displayPatientDetails();
			break;
		case 3:
			handlePatientUpdation();
		case 4:
			removePatient();
		case 99:
			handleMainMenu();
			break;
		case 0:
			createPause("Exiting the system.Goodbye!");
			Exit();
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 0 && choice != 99);
}

void CLI::showPatientMenu()
{
	clearScreen();
	cout << BOLD + UNDERLINE + "Patient Menu:" + RESET << endl;
	cout << "1: Register Patient" << endl;
	cout << "2: Display Patient Details" << endl;
	cout << "3: Update Patient Details" << endl;
	cout << "4: Remove Patient" << endl;
	cout << "99: Go back" << endl;
	cout << "0: Exit" << endl;
}

void CLI::registerPatient()
{
	clearScreen();
	string name, gender, phone, address;
	int age;
	double height, weight;

	cout << BOLD + UNDERLINE + "Register New Patient:" + RESET << endl;

	cout << BOLD + GREEN + "Enter patient name: " + RESET + GRAY + ITALIC;
	clearInputBuffer();
	getline(cin, name);

	cout << RESET << BOLD + GREEN + "Enter patient age: " + RESET + GRAY + ITALIC;
	cin >> age;

	cout << RESET << BOLD + GREEN + "Enter patient gender: " + RESET + GRAY + ITALIC;
	clearInputBuffer();
	getline(cin, gender);

	cout << RESET << BOLD + GREEN + "Enter patient height (in cm): " + RESET + GRAY + ITALIC;
	cin >> height;

	cout << RESET << BOLD + GREEN + "Enter patient weight (in kg): " + RESET + GRAY + ITALIC;
	cin >> weight;

	cout << RESET << BOLD + GREEN + "Enter patient phone number: " + RESET + GRAY + ITALIC;
	clearInputBuffer();
	getline(cin, phone);

	cout << RESET << BOLD + GREEN + "Enter patient address: " + RESET + GRAY + ITALIC;
	clearInputBuffer();
	getline(cin, address);
	cout << RESET;

	int ID = hospital.registerPatient(name, age, gender, phone, address, height, weight);
	
	if (ID != -1) {
		cout << DYELLOW + BOLD + "Patient registered successfully with ID: " << ID << RESET << endl;
	} else {
		cout << "Failed to register patient." << endl;
	}

	createPause("\nPress Enter to return to the Patient Menu...");
	handlePatientMenu();
}

void CLI::displayPatientDetails()
{
	clearScreen();

	int patientID;
	cout << BOLD + GREEN + "Enter Patient ID to display details: " + RESET + GRAY + ITALIC;
	cin >> patientID;
	cout << RESET;

	const Patient* patient = hospital.findPatient(patientID);
	if (patient) {
		cout << *patient;
	} else {
		cout << RED + BOLD + "Patient with ID " << patientID << " not found." << RESET << endl;
	}

	createPause("\nPress Enter to return to the Patient Menu...");
	handlePatientMenu();
}

void CLI::removePatient()
{
	clearScreen();

	int patientID;
	cout << BOLD + GREEN + "Enter ID of Patient to remove: " + RESET + GRAY + ITALIC;
	cin >> patientID;
	cout << RESET;

	if (hospital.removePatient(patientID)) {
		cout << DYELLOW + BOLD + "Patient removed successfully!" << endl;
	}
	else {
		cout << RED + BOLD + "Failed to remove Patient with ID " << patientID << RESET << endl;
	}

	createPause("\nPress Enter to return to the Patient Menu...");
	handlePatientMenu();
}

void CLI::handlePatientUpdation()
{
	int choice, patientID;
	int temp1;
	double temp2;
	string temp3;

	cout << BOLD + GREEN + "Enter Patient ID to update details: " + RESET + GRAY + ITALIC;
	cin >> patientID;
	cout << RESET;

	const Patient* patient = hospital.findPatient(patientID);

	if (patient)
	{
		do {
			clearScreen();
			cout << BOLD + UNDERLINE + "Update Patient Details:" + RESET << endl;
			cout << "1: Update Name "<< "( Current: " << patient->getName() << " )" << endl;
			cout << "2: Update Age " << "( Current: " << patient->getAge() << " )" << endl;
			cout << "3: Update Gender " << "( Current: " << patient->getGender() << " )" << endl;
			cout << "4: Update Height " << "( Current: " << patient->getHeight() << " )" << endl;
			cout << "5: Update Weight " << "( Current: " << patient->getWeight() << " )" << endl;
			cout << "6: Update Phone number " << "( Current: " << patient->getPhone() << " )" << endl;
			cout << "7: Update Address " << "( Current: " << patient->getAddress() << " )" << endl;
			cout << "99: Go Back" << endl;
			cout << "0: Exit" << endl;

			cout << BOLD + GREEN + "Enter your choice: " + RESET + GRAY + ITALIC;
			cin >> choice;
			cout << RESET;

			switch (choice) 
			{
			case 1:
				cout << BOLD + GREEN + "\nEnter new name: " + RESET + GRAY + ITALIC;
				clearInputBuffer();
				getline(cin, temp3);
				cout << RESET;
				if (hospital.updatePatientName(patientID, temp3)){
					cout << DYELLOW + BOLD + "Patient name updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update patient name." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 2:
				cout << BOLD + GREEN + "\nEnter new age: " + RESET + GRAY + ITALIC;
				cin >> temp1;
				cout << RESET;
				if (hospital.updatePatientAge(patientID, temp1)){
					cout << DYELLOW + BOLD + "Patient age updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update patient age." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 3:
				cout << BOLD + GREEN + "\nEnter new gender: " + RESET + GRAY + ITALIC;
				clearInputBuffer();
				getline(cin, temp3);
				cout << RESET;
				if (hospital.updatePatientGender(patientID, temp3)){
					cout << DYELLOW + BOLD + "Patient Gender updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update patient Gender." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 4:
				cout << BOLD + GREEN + "\nEnter new height: " + RESET + GRAY + ITALIC;
				cin >> temp2;
				cout << RESET;
				if (hospital.updatePatientHeight(patientID, temp2)){
					cout << DYELLOW + BOLD + "Patient height updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update patient height." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 5:
				cout << BOLD + GREEN + "\nEnter new weight: " + RESET + GRAY + ITALIC;
				cin >> temp2;
				cout << RESET;
				if (hospital.updatePatientWeight(patientID, temp2)) {
					cout << DYELLOW + BOLD + "Patient weight updated successfully." << RESET << endl;
				} else {
					cout << RED + BOLD + "Failed to update patient weight." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 6:
				cout << BOLD + GREEN + "\nEnter new phone number: " + RESET + GRAY + ITALIC;
				clearInputBuffer();
				getline(cin, temp3);
				cout << RESET;
				if (hospital.updatePatientPhone(patientID, temp3)) {
					cout << DYELLOW + BOLD + "Patient phone number updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update patient phone number." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 7:
				cout << BOLD + GREEN + "\nEnter new address: " + RESET + GRAY + ITALIC;
				clearInputBuffer();
				getline(cin, temp3);
				cout << RESET;
				if( hospital.updatePatientAddress(patientID, temp3) ) {
					cout << DYELLOW + BOLD + "Patient address updated successfully." << RESET << endl;
				} else {
					cout << RED + BOLD + "Failed to update patient address." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 99:
				handlePatientMenu();
				break;
			case 0:
				createPause("Exiting the system.Goodbye!");
				Exit();
				break;
			default:
				cout << "Invalid choice. Please try again." << endl;
			}
		} while (choice != 0 && choice != 99);
	}
	else
		cout << RED + BOLD + "Patient with ID " << patientID << " not found." << RESET << endl;

	createPause("\nPress Enter to return to the Patient Menu...");
	handlePatientMenu();
}


// ---------- Appointment Menu Functions ----------

void CLI::handleAppointmentMenu()
{
	handleMainMenu(); // Placeholder code
}

// ---------- Utility Functions ----------

void CLI::clearInputBuffer() { if (cin.peek() == '\n') cin.ignore(); }

void CLI::createPause(const string& message)
{
	cout << message;
	cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void CLI::clearScreen() { cout << RESET; system("cls"); }

void CLI::Exit() { exit(0); }