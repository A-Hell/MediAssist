
#include "CLI.h"

// Constructor that takes a reference to an existing HospitalSystem instance
CLI::CLI(HospitalSystem& hospital) : hospital(hospital), running(false) {}

// Starts the CLI 
void CLI::run() 
{
	running = true;
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
		case 3:
			handleDoctorMenu();
			break;
		case 4:
			handleDepartmentMenu();
			break;
		case 0:
			Exit();
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 0 && running);
}

void CLI::showMainMenu()
{
	clearScreen();
	cout << BOLD + UNDERLINE + "Main Menu:" + RESET << endl;
	cout << "1: Patient Menu" << endl;
	cout << "2: Appointment Menu" << endl;
	cout << "3: Doctor Menu" << endl;
	cout << "4: Department Menu" << endl;
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
			break;
		case 4:
			removePatient();
			break;
		case 99:
			return;
		case 0:
			Exit();
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 0 && choice != 99 && running);
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
				Exit();
				break;
			default:
				cout << "Invalid choice. Please try again." << endl;
			}
		} while (choice != 0 && choice != 99 && running);
	}
	else
		cout << RED + BOLD + "Patient with ID " << patientID << " not found." << RESET << endl;

	createPause("\nPress Enter to return to the Patient Menu...");
}


// ---------- Appointment Menu Functions ----------

void CLI::handleAppointmentMenu()
{
	handleMainMenu(); // Placeholder code
}


// ---------- Doctor Menu Functions ----------
void CLI::handleDoctorMenu()
{
	int choice;
	do {
		showDoctorMenu();

		cout << BOLD + GREEN + "Enter your choice: " + RESET + GRAY + ITALIC;
		cin >> choice;
		cout << RESET;

		switch (choice) {
		case 1:
			registerDoctor();
			break;
		case 2:
			displayDoctorDetails();
			break;
		case 3:
			handleDoctorUpdation();
			break;
		case 4:
			removeDoctor();
			break;
		case 5:
			clearScreen();
			cout <<BOLD + UNDERLINE + "All Doctors:" + RESET << endl;
			hospital.displayAllDoctors();
			createPause("\nPress Enter to return to the Doctor Menu...");
			break;
		case 6:
			clearScreen();
			cout <<BOLD + UNDERLINE + "Available Doctors:" + RESET << endl;
			hospital.displayAvailableDoctors();
			createPause("\nPress Enter to return to the Doctor Menu...");
			break;
		case 7:
			int departmentID;
			cout << BOLD + GREEN + "Enter Department ID to display doctors: " + RESET + GRAY + ITALIC;
			cin >> departmentID;
			cout << RESET << endl;

			hospital.displayDoctorsByDepartment(departmentID);
			createPause("\nPress Enter to return to the Doctor Menu...");
			break;
		case 99:
			return;
		case 0:
			Exit();
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 0 && choice != 99 && running);
}

void CLI::showDoctorMenu()
{
	clearScreen();
	cout << BOLD + UNDERLINE + "Doctor Menu:" + RESET << endl;
	cout << "1: Register Doctor" << endl;
	cout << "2: Display Doctor Details" << endl;
	cout << "3: Update Doctor Details" << endl;
	cout << "4: Remove Doctor" << endl;
	cout << "5: Display All Doctors" << endl;
	cout << "6: Display Available Doctors" << endl;
	cout << "7: Display Doctors by Department" << endl;
	cout << "99: Go back" << endl;
	cout << "0: Exit" << endl;
}

void CLI::registerDoctor()
{
	clearScreen();
	string name, phone, specialization;
	int departmentID;

	cout << BOLD + UNDERLINE + "Register New Doctor:" + RESET << endl;
	cout << BOLD + GREEN + "Enter Doctor's name: " + RESET + GRAY + ITALIC;
	clearInputBuffer();
	getline(cin, name);

	cout << RESET << BOLD + GREEN + "Enter Doctor's department ID: " + RESET + GRAY + ITALIC;
	cin >> departmentID;

	cout << RESET << BOLD + GREEN + "Enter Doctor's phone number: " + RESET + GRAY + ITALIC;
	clearInputBuffer();
	getline(cin, phone);

	cout << RESET << BOLD + GREEN + "Enter Doctor's specialization: " + RESET + GRAY + ITALIC;
	clearInputBuffer();
	getline(cin, specialization);
	cout << RESET;

	int ID = hospital.registerDoctor(departmentID, name, phone, specialization);

	if (ID != -1) {
		cout << DYELLOW + BOLD + "Doctor registered successfully with ID: " << ID << RESET << endl;
	}
	else {
		cout << RED + BOLD + "Failed to register doctor." << RESET << endl;
	}

	createPause("\nPress Enter to return to the Patient Menu...");
}

void CLI::displayDoctorDetails()
{
	clearScreen();

	int doctorID;
	cout << BOLD + GREEN + "Enter Doctor ID to display details: " + RESET + GRAY + ITALIC;
	cin >> doctorID;
	cout << RESET;

	Doctor* doctor = hospital.findDoctor(doctorID);
	if (doctor) {
		cout << *doctor;
	}
	else {
		cout << RED + BOLD + "Doctor with ID " << doctorID << " not found." << RESET << endl;
	}

	createPause("\nPress Enter to return to the Doctor Menu...");
}

void CLI::removeDoctor()
{
	clearScreen();

	int doctorID;
	cout << BOLD + GREEN + "Enter ID of Doctor to remove: " + RESET + GRAY + ITALIC;
	cin >> doctorID;
	cout << RESET;

	if (hospital.removeDoctor(doctorID)) {
		cout << DYELLOW + BOLD + "Doctor removed successfully!" << RESET << endl;
	}
	else {
		cout << RED + BOLD + "Failed to remove Doctor with ID " << doctorID << RESET << endl;
	}

	createPause("\nPress Enter to return to the Doctor Menu...");
}

void CLI::handleDoctorUpdation()
{
	int choice, doctorID;
	int temp1;
	bool temp2;
	string temp3;

	cout << BOLD + GREEN + "Enter Doctor ID to update details: " + RESET + GRAY + ITALIC;
	cin >> doctorID;
	cout << RESET;

	const Doctor* doctor = hospital.findDoctor(doctorID);
	if (doctor)
	{
		do {
			clearScreen();
			cout << BOLD + UNDERLINE + "Update Doctor Details:" + RESET << endl;
			cout << "1: Update Name " << "( Current: " << doctor->getName() << " )" << endl;
			cout << "2: Update Department " << "( Current: " << doctor->getDepartmentId() << " )" << endl;
			cout << "3: Update Phone number" << "( Current: " << doctor->getPhone() << " )" << endl;
			cout << "4: Update Specialization " << "( Current: " << doctor->getSpecialization() << " )" << endl;
			cout << "5: Update Availability " << "( Current: " << (doctor->isAvailable() ? "Available" : "Not Available") << " )" << endl;
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
				if (hospital.updateDoctorName(doctorID, temp3)) {
					cout << DYELLOW + BOLD + "Doctor name updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update doctor name." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 2:
				cout << BOLD + GREEN + "\nEnter new department ID: " + RESET + GRAY + ITALIC;
				cin >> temp1;
				cout << RESET;
				if (hospital.updateDoctorDepartment(doctorID, temp1)) {
					cout << DYELLOW + BOLD + "Doctor department updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update doctor department." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 3:
				cout << BOLD + GREEN + "\nEnter new phone number: " + RESET + GRAY + ITALIC;
				clearInputBuffer();
				getline(cin, temp3);
				cout << RESET;
				if (hospital.updateDoctorPhone(doctorID, temp3)) {
					cout << DYELLOW + BOLD + "Doctor phone number updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update doctor phone number." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 4:
				cout << BOLD + GREEN + "\nEnter new specialization: " + RESET + GRAY + ITALIC;
				clearInputBuffer();
				getline(cin, temp3);
				cout << RESET;
				if (hospital.updateDoctorSpecialization(doctorID, temp3)) {
					cout << DYELLOW + BOLD + "Doctor specialization updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update Doctor specialization." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 5:
				cout << BOLD + GREEN + "\nEnter new availability (1 for Available, 0 for Not Available): " + RESET + GRAY + ITALIC;
				cin >> temp2;
				cout << RESET;
				if (hospital.updateDoctorAvailability(doctorID, temp2)) {
					cout << DYELLOW + BOLD + "Doctor availability updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update Doctor's availability." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 99:
				return;
				break;
			case 0:
				Exit();
				break;
			default:
				cout << "Invalid choice. Please try again." << endl;
			}
		} while (choice != 0 && choice != 99 && running);
	}
	else
		cout << RED + BOLD + "Doctor with ID " << doctorID << " not found." << RESET << endl;

	createPause("\nPress Enter to return to the Doctor Menu...");
	handleDoctorMenu();
}

// ---------- Department Menu Functions ----------
void CLI::handleDepartmentMenu()
{
	int choice;
	do {
		showDepartmentMenu();

		cout << BOLD + GREEN + "Enter your choice: " + RESET + GRAY + ITALIC;
		cin >> choice;
		cout << RESET;

		switch (choice) {
		case 1:
			registerDepartment();
			break;
		case 2:
			displayDepartmentDetails();
			break;
		case 3:
			handleDepartmentUpdation();
			break;
		case 4:
			removeDepartment();
			break;
		case 5:
			addDoctorToDepartment();
			break;
		case 6:
			removeDoctorFromDepartment();
			break;
		case 7:
			clearScreen();

			int departmentID;
			cout << BOLD + GREEN + "Enter Department ID to display doctors: " + RESET + GRAY + ITALIC;
			cin >> departmentID;
			cout << RESET << endl;

			hospital.displayDepartmentDoctors(departmentID);
			createPause("\nPress Enter to return to the Department Menu...");
			break;

		case 8:
			clearScreen();

			cout << BOLD + UNDERLINE + "All Departments:" + RESET << endl;
			hospital.displayAllDepartments();
			createPause("\nPress Enter to return to the Department Menu...");
			break;

		case 99:
			return;
			break;
		case 0:
			Exit();
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 0 && choice != 99 && running);
}

void CLI::showDepartmentMenu()
{
	clearScreen();
	cout << BOLD + UNDERLINE + "Department Menu:" + RESET << endl;
	cout << "1: Register Department" << endl;
	cout << "2: Display Department Details" << endl;
	cout << "3: Update Department Details" << endl;
	cout << "4: Remove Department" << endl;
	cout << "5: Add Doctor to Department" << endl;
	cout << "6: Remove Doctor from Department" << endl;
	cout << "7: Display Doctors in Department" << endl;
	cout << "8: Display All Departments" << endl;
	cout << "99: Go back" << endl;
	cout << "0: Exit" << endl;
}

void CLI::registerDepartment()
{
	string name, description, location;

	cout << BOLD + UNDERLINE + "Register New Patient:" + RESET << endl;

	cout << BOLD + GREEN + "Enter department name: " + RESET + GRAY + ITALIC;
	clearInputBuffer();
	getline(cin, name);

	cout << BOLD + GREEN + "Enter department description: " + RESET + GRAY + ITALIC;
	clearInputBuffer();
	getline(cin, description);

	cout << BOLD + GREEN + "Enter department location	: " + RESET + GRAY + ITALIC;
	clearInputBuffer();
	getline(cin, location);

	int departmentID = hospital.createDepartment(name, description, location);

	if (departmentID != -1) {
		cout << DYELLOW + BOLD + "Department registered successfully with ID: " << departmentID << RESET << endl;
	}
	else {
		cout << RED + BOLD + "Failed to register department." << RESET << endl;
	}
}

void CLI::displayDepartmentDetails()
{
	clearScreen();

	int departmentID;
	cout << BOLD + GREEN + "Enter Department ID to display details: " + RESET + GRAY + ITALIC;
	cin >> departmentID;
	cout << RESET;

	Department* department = hospital.findDepartment(departmentID);
	if (department) {
		cout << *department;
	}
	else {
		cout << RED + BOLD + "Department with ID " << departmentID << " not found." << RESET << endl;
	}

	createPause("\nPress Enter to return to the Department Menu...");
}

void CLI::handleDepartmentUpdation()
{
	int choice, departmentID;
	string temp3;

	cout << BOLD + GREEN + "Enter Department ID to update details: " + RESET + GRAY + ITALIC;
	cin >> departmentID;
	cout << RESET;

	const Department* department = hospital.findDepartment(departmentID);
	if (department)
	{
		do {
			clearScreen();
			cout << BOLD + UNDERLINE + "Update Department Details:" + RESET << endl;
			cout << "1: Update Name " << "( Current: " << department->getName() << " )" << endl;
			cout << "2: Update Description " << "( Current: " << department->getDescription() << " )" << endl;
			cout << "3: Update Location" << "( Current: " << department->getLocation() << " )" << endl;
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
				if (hospital.updateDepartmentName(departmentID, temp3)) {
					cout << DYELLOW + BOLD + "Department name updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update department name." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 2:
				cout << BOLD + GREEN + "\nEnter new name: " + RESET + GRAY + ITALIC;
				clearInputBuffer();
				getline(cin, temp3);
				cout << RESET;
				if (hospital.updateDepartmentDescription(departmentID, temp3)) {
					cout << DYELLOW + BOLD + "Department description updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update department description." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 3:
				cout << BOLD + GREEN + "\nEnter new Location: " + RESET + GRAY + ITALIC;
				clearInputBuffer();
				getline(cin, temp3);
				cout << RESET;
				if (hospital.updateDepartmentLocation(departmentID, temp3)) {
					cout << DYELLOW + BOLD + "Department location updated successfully." << RESET << endl;
				}
				else {
					cout << RED + BOLD + "Failed to update department location." << RESET << endl;
				}
				createPause("\nPress Enter to return to continue...");
				break;

			case 99:
				return;
			case 0:
				Exit();
				break;
			default:
				cout << "Invalid choice. Please try again." << endl;
			}
		} while (choice != 0 && choice != 99 && running);
	}
	else
		cout << RED + BOLD + "Department with ID " << departmentID << " not found." << RESET << endl;

	createPause("\nPress Enter to return to the Department Menu...");
}

void CLI::removeDepartment() {
	clearScreen();
	int departmentID;
	cout << BOLD + GREEN + "Enter ID of Department to remove: " + RESET + GRAY + ITALIC;
	cin >> departmentID;
	cout << RESET;
	if (hospital.removeDepartment(departmentID)) {
		cout << DYELLOW + BOLD + "Department removed successfully!" << RESET << endl;
	}
	else {
		cout << RED + BOLD + "Failed to remove Department with ID " << departmentID << RESET << endl;
	}
	createPause("\nPress Enter to return to the Department Menu...");
}

void CLI::addDoctorToDepartment() {
	clearScreen();
	int departmentID, doctorID;
	cout << BOLD + GREEN + "Enter ID of Department to add to: " + RESET + GRAY + ITALIC;
	cin >> departmentID;
	cout << RESET;

	cout << BOLD + GREEN + "Enter ID of Doctor to add: " + RESET + GRAY + ITALIC;
	cin >> doctorID;
	cout << RESET;

	if (hospital.doctorExists(doctorID) && hospital.departmentExists(departmentID)) {
		if (hospital.addDoctorToDepartment(departmentID, doctorID)) {
			cout << DYELLOW + BOLD + "Doctor added to Department successfully!" << RESET << endl;
		}
		else {
			cout << RED + BOLD + "Failed to add Doctor to Department." << RESET << endl;
		}
	}
	else {
		cout << RED + BOLD + "Invalid Doctor ID or Department ID." << RESET << endl;
	}

	createPause("\nPress Enter to return to the Department Menu...");
}

void CLI::removeDoctorFromDepartment() {
	clearScreen();
	int departmentID, doctorID;
	cout << BOLD + GREEN + "Enter ID of Department to remove from: " + RESET + GRAY + ITALIC;
	cin >> departmentID;
	cout << RESET;
	cout << BOLD + GREEN + "Enter ID of Doctor to remove: " + RESET + GRAY + ITALIC;
	cin >> doctorID;
	cout << RESET;
	if (hospital.doctorExists(doctorID) && hospital.departmentExists(departmentID)) {
		if (hospital.removeDoctorFromDepartment(departmentID, doctorID)) {
			cout << DYELLOW + BOLD + "Doctor removed from Department successfully!" << RESET << endl;
		}
		else {
			cout << RED + BOLD + "Failed to remove Doctor from Department." << RESET << endl;
		}
	}
	else {
		cout << RED + BOLD + "Invalid Doctor ID or Department ID." << RESET << endl;
	}

	createPause("\nPress Enter to return to the Department Menu...");
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

void CLI::Exit() {
	running = false;
	createPause("Exiting the system.Goodbye!");
}