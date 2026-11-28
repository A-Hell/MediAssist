#include "FileManager.h"
#include <fstream>
#include <iomanip>
#include <utility>


// ---------------- DEPARTMENT FILE OPERATIONS ----------------

// Save all department details in the file
bool FileManager::saveDepartments(const DepartmentManager& departmentManager, const string& filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    file << "MEDIASSIST_DEPARTMENTS_V1" << endl;
    file << "DepartmentCount " << departmentManager.departments.size() << endl;

    for (size_t i = 0; i < departmentManager.departments.size(); i++)
    {
        const Department& department = departmentManager.departments[i];

        file << endl;
        file << "DepartmentID " << department.departmentId << endl;
        file << "Name " << quoted(department.name) << endl;
        file << "Description " << quoted(department.description) << endl;
        file << "Location " << quoted(department.location) << endl;
        file << "DoctorCount " << department.doctorIds.size() << endl;

        for (size_t j = 0; j < department.doctorIds.size(); j++)
        {
            file << "DoctorID " << department.doctorIds[j] << endl;
        }
    }

    file.close();
    return !file.fail();
}


// Load all department details from the file
bool FileManager::loadDepartments(DepartmentManager& departmentManager, const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    string header, label;
    int count;

    if (!(file >> header))
    {
        if (file.eof() && !file.bad())
        {
            vector<Department> emptyDepartments;
            departmentManager.departments.swap(emptyDepartments);
            return true;
        }

        return false;
    }

    if (header != "MEDIASSIST_DEPARTMENTS_V1")
    {
        return false;
    }

    if (!(file >> label >> count) || label != "DepartmentCount" || count < 0)
    {
        return false;
    }

    struct DepartmentData
    {
        int id;
        string name;
        string description;
        string location;
        vector<int> doctorIds;
    };

    vector<DepartmentData> loadedData;
    int highestID = 0;

    for (int i = 0; i < count; i++)
    {
        DepartmentData data;
        int doctorCount;

        if (!(file >> label >> data.id) || label != "DepartmentID" || data.id <= 0)
        {
            return false;
        }

        if (!(file >> label >> quoted(data.name)) || label != "Name")
        {
            return false;
        }

        if (!(file >> label >> quoted(data.description)) || label != "Description")
        {
            return false;
        }

        if (!(file >> label >> quoted(data.location)) || label != "Location")
        {
            return false;
        }

        if (!(file >> label >> doctorCount) || label != "DoctorCount" || doctorCount < 0)
        {
            return false;
        }

        for (int j = 0; j < doctorCount; j++)
        {
            int doctorID;

            if (!(file >> label >> doctorID) || label != "DoctorID" || doctorID <= 0)
            {
                return false;
            }

            // Check for duplicate doctor IDs in the department
            for (size_t k = 0; k < data.doctorIds.size(); k++)
            {
                if (data.doctorIds[k] == doctorID)
                {
                    return false;
                }
            }

            data.doctorIds.push_back(doctorID);
        }

        // Check for duplicate department IDs
        for (size_t j = 0; j < loadedData.size(); j++)
        {
            if (loadedData[j].id == data.id)
            {
                return false;
            }
        }

        if (data.id > highestID)
        {
            highestID = data.id;
        }

        loadedData.push_back(data);
    }

    vector<Department> loadedDepartments;
    int oldCounter = Department::counter;

    for (size_t i = 0; i < loadedData.size(); i++)
    {
        Department department(loadedData[i].name, loadedData[i].description, loadedData[i].location);

        department.departmentId = loadedData[i].id;
        department.doctorIds = loadedData[i].doctorIds;

        loadedDepartments.push_back(department);
    }

    departmentManager.departments.swap(loadedDepartments);

    Department::counter = oldCounter;

    if (highestID > Department::counter)
    {
        Department::counter = highestID;
    }

    return true;
}


// ---------------- DOCTOR FILE OPERATIONS ----------------

// Save all doctor details in the file
bool FileManager::saveDoctors(const DoctorManager& doctorManager, const string& filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    file << "MEDIASSIST_DOCTORS_V1" << endl;
    file << "DoctorCount " << doctorManager.doctors.size() << endl;

    for (size_t i = 0; i < doctorManager.doctors.size(); i++)
    {
        const Doctor& doctor = doctorManager.doctors[i];

        file << endl;
        file << "DoctorID " << doctor.doctorId << endl;
        file << "DepartmentID " << doctor.departmentId << endl;
        file << "Name " << quoted(doctor.name) << endl;
        file << "Phone " << quoted(doctor.phone) << endl;
        file << "Specialization " << quoted(doctor.specialization) << endl;
        file << "Availability " << doctor.availability << endl;
    }

    file.close();
    return !file.fail();
}


// Load all doctor details from the file
bool FileManager::loadDoctors(DoctorManager& doctorManager, const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    string header, label;
    int count;

    if (!(file >> header))
    {
        if (file.eof() && !file.bad())
        {
            vector<Doctor> emptyDoctors;
            doctorManager.doctors.swap(emptyDoctors);
            return true;
        }

        return false;
    }

    if (header != "MEDIASSIST_DOCTORS_V1")
    {
        return false;
    }

    if (!(file >> label >> count) || label != "DoctorCount" || count < 0)
    {
        return false;
    }

    struct DoctorData
    {
        int id;
        int departmentID;
        string name;
        string phone;
        string specialization;
        bool availability;
    };

    vector<DoctorData> loadedData;
    vector<Doctor> loadedDoctors;
    int highestID = 0;

    for (int i = 0; i < count; i++)
    {
        DoctorData data;
        int availability;

        if (!(file >> label >> data.id) || label != "DoctorID" || data.id <= 0)
        {
            return false;
        }

        if (!(file >> label >> data.departmentID) || label != "DepartmentID" || data.departmentID <= 0)
        {
            return false;
        }

        if (!(file >> label >> quoted(data.name)) || label != "Name")
        {
            return false;
        }

        if (!(file >> label >> quoted(data.phone)) || label != "Phone")
        {
            return false;
        }

        if (!(file >> label >> quoted(data.specialization)) || label != "Specialization")
        {
            return false;
        }

        if (!(file >> label >> availability) || label != "Availability" || (availability != 0 && availability != 1))
        {
            return false;
        }

        data.availability = (availability == 1);

        // Check for duplicate doctor IDs
        for (size_t j = 0; j < loadedData.size(); j++)
        {
            if (loadedData[j].id == data.id)
            {
                return false;
            }
        }

        if (data.id > highestID)
        {
            highestID = data.id;
        }

        loadedData.push_back(data);
    }

    int oldCounter = Doctor::counter;

    for (size_t i = 0; i < loadedData.size(); i++)
    {
        Doctor doctor(loadedData[i].departmentID, loadedData[i].name,
            loadedData[i].phone, loadedData[i].specialization, loadedData[i].availability);

        doctor.doctorId = loadedData[i].id;

        loadedDoctors.push_back(doctor);
    }

    doctorManager.doctors.swap(loadedDoctors);

    Doctor::counter = oldCounter;

    if (highestID > Doctor::counter)
    {
        Doctor::counter = highestID;
    }

    return true;
}


// ---------------- PATIENT FILE OPERATIONS ----------------

// Save all patient details in the file
bool FileManager::savePatients(const PatientManager& patientManager, const string& filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    const HashTable& table = patientManager.patientTable;

    file << "MEDIASSIST_PATIENTS_V1" << endl;
    file << "PatientCount " << table.size << endl;

    // Visit every bucket in the Hash Table
    for (int i = 0; i < table.capacity; i++)
    {
        HashTable::Node* current = table.table[i];

        // Visit every patient in this bucket
        while (current != NULL)
        {
            const Patient& patient = current->patient;

            file << endl;
            file << "PatientID " << patient.patientID << endl;
            file << "Name " << quoted(patient.name) << endl;
            file << "Age " << patient.age << endl;
            file << "Gender " << quoted(patient.gender) << endl;
            file << "Phone " << quoted(patient.phone) << endl;
            file << "Address " << quoted(patient.address) << endl;
            file << "Height " << setprecision(17) << patient.height << endl;
            file << "Weight " << setprecision(17) << patient.weight << endl;

            current = current->next;
        }
    }

    file.close();
    return !file.fail();
}


// Load all patient details from the file
bool FileManager::loadPatients(PatientManager& patientManager, const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    string header, label;
    int count;

    if (!(file >> header))
    {
        if (file.eof() && !file.bad())
        {
            HashTable emptyTable(patientManager.patientTable.capacity);

            swap(patientManager.patientTable.table, emptyTable.table);
            swap(patientManager.patientTable.size, emptyTable.size);

            return true;
        }

        return false;
    }

    if (header != "MEDIASSIST_PATIENTS_V1")
    {
        return false;
    }

    if (!(file >> label >> count) || label != "PatientCount" || count < 0)
    {
        return false;
    }

    struct PatientData
    {
        int id;
        string name;
        int age;
        string gender;
        string phone;
        string address;
        double height;
        double weight;
    };

    vector<PatientData> loadedData;
    int highestID = 0;

    for (int i = 0; i < count; i++)
    {
        PatientData data;

        if (!(file >> label >> data.id) || label != "PatientID" || data.id <= 0)
        {
            return false;
        }

        if (!(file >> label >> quoted(data.name)) || label != "Name")
        {
            return false;
        }

        if (!(file >> label >> data.age) || label != "Age")
        {
            return false;
        }

        if (!(file >> label >> quoted(data.gender)) || label != "Gender")
        {
            return false;
        }

        if (!(file >> label >> quoted(data.phone)) || label != "Phone")
        {
            return false;
        }

        if (!(file >> label >> quoted(data.address)) || label != "Address")
        {
            return false;
        }

        if (!(file >> label >> data.height) || label != "Height")
        {
            return false;
        }

        if (!(file >> label >> data.weight) || label != "Weight")
        {
            return false;
        }

        // Check for duplicate patient IDs
        for (size_t j = 0; j < loadedData.size(); j++)
        {
            if (loadedData[j].id == data.id)
            {
                return false;
            }
        }

        if (data.id > highestID)
        {
            highestID = data.id;
        }

        loadedData.push_back(data);
    }

    HashTable loadedTable(patientManager.patientTable.capacity);
    int oldCounter = Patient::counter;

    for (size_t i = 0; i < loadedData.size(); i++)
    {
        Patient patient(loadedData[i].name, loadedData[i].age, loadedData[i].gender,
            loadedData[i].phone, loadedData[i].address, loadedData[i].height, loadedData[i].weight);

        patient.patientID = loadedData[i].id;

        if (!loadedTable.insert(patient))
        {
            Patient::counter = oldCounter;
            return false;
        }
    }

    swap(patientManager.patientTable.table, loadedTable.table);
    swap(patientManager.patientTable.size, loadedTable.size);

    Patient::counter = oldCounter;

    if (highestID >= Patient::counter)
    {
        Patient::counter = highestID + 1;
    }

    return true;
}


// ---------------- APPOINTMENT FILE OPERATIONS ----------------

// Save all appointment details in the file
bool FileManager::saveAppointments(const AppointmentManager& appointmentManager, const string& filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    vector<BST::Node*> appointments;
    vector<BST::Node*> stack;

    BST::Node* current = appointmentManager.appointmentTree.root;

    // Traverse the BST in chronological order
    while (current != NULL || !stack.empty())
    {
        while (current != NULL)
        {
            stack.push_back(current);
            current = current->left;
        }

        current = stack.back();
        stack.pop_back();

        appointments.push_back(current);
        current = current->right;
    }

    file << "MEDIASSIST_APPOINTMENTS_V1" << endl;
    file << "AppointmentCount " << appointments.size() << endl;

    for (size_t i = 0; i < appointments.size(); i++)
    {
        const Appointment& appointment = appointments[i]->appointment;

        file << endl;
        file << "AppointmentID " << appointment.appointmentID << endl;
        file << "PatientID " << appointment.patientID << endl;
        file << "DepartmentID " << appointment.departmentID << endl;
        file << "Date " << quoted(appointment.appointmentDate) << endl;
        file << "Time " << quoted(appointment.appointmentTime) << endl;
        file << "Status " << quoted(appointment.status) << endl;
        file << "SymptomCount " << appointment.symptoms.size() << endl;

        for (size_t j = 0; j < appointment.symptoms.size(); j++)
        {
            file << "Symptom " << static_cast<int>(appointment.symptoms[j]) << endl;
        }
    }

    file.close();
    return !file.fail();
}


// Load all appointment details from the file
bool FileManager::loadAppointments(AppointmentManager& appointmentManager, const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    string header, label;
    int count;

    if (!(file >> header))
    {
        if (file.eof() && !file.bad())
        {
            BST emptyTree;
            swap(appointmentManager.appointmentTree.root, emptyTree.root);

            return true;
        }

        return false;
    }

    if (header != "MEDIASSIST_APPOINTMENTS_V1")
    {
        return false;
    }

    if (!(file >> label >> count) || label != "AppointmentCount" || count < 0)
    {
        return false;
    }

    struct AppointmentData
    {
        int id;
        int patientID;
        int departmentID;
        string date;
        string time;
        string status;
        vector<Symptom> symptoms;
    };

    vector<AppointmentData> loadedData;
    int highestID = 0;

    for (int i = 0; i < count; i++)
    {
        AppointmentData data;
        int symptomCount;

        if (!(file >> label >> data.id) || label != "AppointmentID" || data.id <= 0)
        {
            return false;
        }

        if (!(file >> label >> data.patientID) || label != "PatientID" || data.patientID <= 0)
        {
            return false;
        }

        if (!(file >> label >> data.departmentID) || label != "DepartmentID" || data.departmentID <= 0)
        {
            return false;
        }

        if (!(file >> label >> quoted(data.date)) || label != "Date" || !isValidDate(data.date))
        {
            return false;
        }

        if (!(file >> label >> quoted(data.time)) || label != "Time" || !isValidTime(data.time))
        {
            return false;
        }

        if (!(file >> label >> quoted(data.status)) || label != "Status")
        {
            return false;
        }

        if (data.status != "Scheduled" && data.status != "Waiting" &&
            data.status != "Completed" && data.status != "Cancelled")
        {
            return false;
        }

        if (!(file >> label >> symptomCount) || label != "SymptomCount" || symptomCount < 0)
        {
            return false;
        }

        for (int j = 0; j < symptomCount; j++)
        {
            int symptomValue;

            if (!(file >> label >> symptomValue) || label != "Symptom" ||
                symptomValue < 0 || symptomValue > static_cast<int>(Symptom::SuspectedFracture))
            {
                return false;
            }

            Symptom symptom = static_cast<Symptom>(symptomValue);

            // Check for duplicate symptoms
            for (size_t k = 0; k < data.symptoms.size(); k++)
            {
                if (data.symptoms[k] == symptom)
                {
                    return false;
                }
            }

            data.symptoms.push_back(symptom);
        }

        // Check for duplicate appointment IDs
        for (size_t j = 0; j < loadedData.size(); j++)
        {
            if (loadedData[j].id == data.id)
            {
                return false;
            }
        }

        if (data.id > highestID)
        {
            highestID = data.id;
        }

        loadedData.push_back(data);
    }

    BST loadedTree;
    int oldCounter = Appointment::counter;

    for (size_t i = 0; i < loadedData.size(); i++)
    {
        Appointment appointment(loadedData[i].patientID, loadedData[i].departmentID,
            loadedData[i].symptoms, loadedData[i].date, loadedData[i].time, loadedData[i].status);

        appointment.appointmentID = loadedData[i].id;

        loadedTree.insert(appointment);
    }

    swap(appointmentManager.appointmentTree.root, loadedTree.root);

    Appointment::counter = oldCounter;

    if (highestID >= Appointment::counter)
    {
        Appointment::counter = highestID + 1;
    }

    return true;
}


// ---------------- SAVE AND LOAD ALL HOSPITAL DATA ----------------

// Save all patients, departments, doctors and appointments
bool FileManager::saveAll(const PatientManager& patientManager, const DepartmentManager& departmentManager, const DoctorManager& doctorManager, const AppointmentManager& appointmentManager)
{
    if (!savePatients(patientManager))
    {
        return false;
    }

    if (!saveDepartments(departmentManager))
    {
        return false;
    }

    if (!saveDoctors(doctorManager))
    {
        return false;
    }

    if (!saveAppointments(appointmentManager))
    {
        return false;
    }

    return true;
}


// Load all hospital data

bool FileManager::loadAll(PatientManager& patientManager, DepartmentManager& departmentManager, DoctorManager& doctorManager, AppointmentManager& appointmentManager)
{
    PatientManager tempPatients(patientManager.patientTable.capacity);
    DepartmentManager tempDepartments;
    DoctorManager tempDoctors;
    AppointmentManager tempAppointments;

    cout << "Loading patients..." << endl;
    if (!loadPatients(tempPatients))
    {
        cout << "FAILED: patients.txt" << endl;
        return false;
    }
    cout << "Patients loaded." << endl;

    cout << "Loading departments..." << endl;
    if (!loadDepartments(tempDepartments))
    {
        cout << "FAILED: departments.txt" << endl;
        return false;
    }
    cout << "Departments loaded." << endl;

    cout << "Loading doctors..." << endl;
    if (!loadDoctors(tempDoctors))
    {
        cout << "FAILED: doctors.txt" << endl;
        return false;
    }
    cout << "Doctors loaded." << endl;

    cout << "Loading appointments..." << endl;
    if (!loadAppointments(tempAppointments))
    {
        cout << "FAILED: appointments.txt" << endl;
        return false;
    }
    cout << "Appointments loaded." << endl;

    cout << "Checking doctor-department relationships..." << endl;

    for (size_t i = 0; i < tempDoctors.doctors.size(); i++)
    {
        const Doctor& doctor = tempDoctors.doctors[i];
        bool departmentFound = false;
        bool doctorListed = false;

        for (size_t j = 0; j < tempDepartments.departments.size(); j++)
        {
            const Department& department = tempDepartments.departments[j];

            if (department.departmentId == doctor.departmentId)
            {
                departmentFound = true;

                for (size_t k = 0; k < department.doctorIds.size(); k++)
                {
                    if (department.doctorIds[k] == doctor.doctorId)
                    {
                        doctorListed = true;
                        break;
                    }
                }
                break;
            }
        }

        if (!departmentFound || !doctorListed)
        {
            cout << "FAILED: Doctor ID " << doctor.doctorId
                << " has an invalid department relationship." << endl;
            return false;
        }
    }

    for (size_t i = 0; i < tempDepartments.departments.size(); i++)
    {
        const Department& department = tempDepartments.departments[i];

        for (size_t j = 0; j < department.doctorIds.size(); j++)
        {
            bool doctorFound = false;

            for (size_t k = 0; k < tempDoctors.doctors.size(); k++)
            {
                if (tempDoctors.doctors[k].doctorId == department.doctorIds[j] &&
                    tempDoctors.doctors[k].departmentId == department.departmentId)
                {
                    doctorFound = true;
                    break;
                }
            }

            if (!doctorFound)
            {
                cout << "FAILED: Department ID " << department.departmentId
                    << " contains an invalid Doctor ID " << department.doctorIds[j] << endl;
                return false;
            }
        }
    }

    cout << "Checking appointment relationships..." << endl;

    vector<BST::Node*> stack;
    BST::Node* current = tempAppointments.appointmentTree.root;

    while (current != NULL || !stack.empty())
    {
        while (current != NULL)
        {
            stack.push_back(current);
            current = current->left;
        }

        current = stack.back();
        stack.pop_back();

        const Appointment& appointment = current->appointment;

        if (tempPatients.patientTable.search(appointment.patientID) == NULL)
        {
            cout << "FAILED: Appointment ID " << appointment.appointmentID
                << " refers to missing Patient ID " << appointment.patientID << endl;
            return false;
        }

        bool departmentFound = false;

        for (size_t i = 0; i < tempDepartments.departments.size(); i++)
        {
            if (tempDepartments.departments[i].departmentId == appointment.departmentID)
            {
                departmentFound = true;
                break;
            }
        }

        if (!departmentFound)
        {
            cout << "FAILED: Appointment ID " << appointment.appointmentID
                << " refers to missing Department ID " << appointment.departmentID << endl;
            return false;
        }

        current = current->right;
    }

    swap(patientManager.patientTable.table, tempPatients.patientTable.table);
    swap(patientManager.patientTable.size, tempPatients.patientTable.size);

    departmentManager.departments.swap(tempDepartments.departments);
    doctorManager.doctors.swap(tempDoctors.doctors);

    swap(appointmentManager.appointmentTree.root, tempAppointments.appointmentTree.root);

    return true;
}

