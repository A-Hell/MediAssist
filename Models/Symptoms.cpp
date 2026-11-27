#include "../Models/Symptoms.h"

// Returns the points assigned to the selected symptom.
int getSymptomPoints(Symptom symptom)
{
    switch (symptom)
    {
        // General symptoms
    case Symptom::Fever:
        return 2;

    case Symptom::Fatigue:
        return 1;

    case Symptom::Headache:
        return 1;

    case Symptom::Dizziness:
        return 2;

    case Symptom::GeneralWeakness:
        return 2;


        // Cardiology
    case Symptom::ChestDiscomfort:
        return 5;

    case Symptom::Palpitations:
        return 3;

    case Symptom::Fainting:
        return 5;

    case Symptom::LegSwelling:
        return 2;


        // Respiratory
    case Symptom::Cough:
        return 1;

    case Symptom::SoreThroat:
        return 1;

    case Symptom::Wheezing:
        return 3;

    case Symptom::BreathingDifficulty:
        return 5;

    case Symptom::ChestTightness:
        return 4;


        // Gastroenterology
    case Symptom::AbdominalPain:
        return 3;

    case Symptom::Nausea:
        return 1;

    case Symptom::Vomiting:
        return 2;

    case Symptom::Diarrhea:
        return 2;

    case Symptom::BloodInStool:
        return 5;


        // Orthopedics
    case Symptom::JointPain:
        return 2;

    case Symptom::BackPain:
        return 2;

    case Symptom::JointSwelling:
        return 2;

    case Symptom::LimitedMovement:
        return 3;

    case Symptom::LimbInjury:
        return 4;

    case Symptom::SuspectedFracture:
        return 5;

    default:
        return 0;
    }
}


// Goes through the selected symptoms and adds their points together.
int calculateTriageScore(const vector<Symptom>& symptoms)
{
    int totalScore = 0;

    for (Symptom symptom : symptoms)
    {
        totalScore = totalScore + getSymptomPoints(symptom);
    }

    return totalScore;
}


// Checks the total score and decides the appointment's priority.
Priority determinePriority(int triageScore)
{
    if (triageScore >= 5)
    {
        return Priority::Urgent;
    }
    else
    {
        return Priority::Routine;
    }
}


// Returns the general symptoms and the symptoms of the selected department.
vector<Symptom> getAvailableSymptoms(const string& departmentName)
{
    vector<Symptom> symptoms;

    // Make sure the department is one of the departments we support.
    if (departmentName != "Cardiology" &&
        departmentName != "Respiratory" &&
        departmentName != "Gastroenterology" &&
        departmentName != "Orthopedics")
    {
        return symptoms;
    }

    // Add general symptoms because every department can use them.
    symptoms.push_back(Symptom::Fever);
    symptoms.push_back(Symptom::Fatigue);
    symptoms.push_back(Symptom::Headache);
    symptoms.push_back(Symptom::Dizziness);
    symptoms.push_back(Symptom::GeneralWeakness);


    // Add only the symptoms related to Cardiology.
    if (departmentName == "Cardiology")
    {
        symptoms.push_back(Symptom::ChestDiscomfort);
        symptoms.push_back(Symptom::Palpitations);
        symptoms.push_back(Symptom::Fainting);
        symptoms.push_back(Symptom::LegSwelling);
    }

    // Add only the symptoms related to Respiratory.
    else if (departmentName == "Respiratory")
    {
        symptoms.push_back(Symptom::Cough);
        symptoms.push_back(Symptom::SoreThroat);
        symptoms.push_back(Symptom::Wheezing);
        symptoms.push_back(Symptom::BreathingDifficulty);
        symptoms.push_back(Symptom::ChestTightness);
    }

    // Add only the symptoms related to Gastroenterology.
    else if (departmentName == "Gastroenterology")
    {
        symptoms.push_back(Symptom::AbdominalPain);
        symptoms.push_back(Symptom::Nausea);
        symptoms.push_back(Symptom::Vomiting);
        symptoms.push_back(Symptom::Diarrhea);
        symptoms.push_back(Symptom::BloodInStool);
    }

    // Add only the symptoms related to Orthopedics.
    else if (departmentName == "Orthopedics")
    {
        symptoms.push_back(Symptom::JointPain);
        symptoms.push_back(Symptom::BackPain);
        symptoms.push_back(Symptom::JointSwelling);
        symptoms.push_back(Symptom::LimitedMovement);
        symptoms.push_back(Symptom::LimbInjury);
        symptoms.push_back(Symptom::SuspectedFracture);
    }

    return symptoms;
}

// Checks whether the patient selected valid symptoms for their department.
bool areSymptomsValid(const string& departmentName, const vector<Symptom>& selectedSymptoms)
{
    // Get the symptoms available for this department.
    vector<Symptom> availableSymptoms = getAvailableSymptoms(departmentName);

    // A department must exist and the patient must select at least one symptom.
    if (availableSymptoms.empty() || selectedSymptoms.empty())
    {
        return false;
    }

    // Check each selected symptom.
    for (int i = 0; i < selectedSymptoms.size(); i++)
    {
        bool found = false;

        // Check whether the selected symptom is allowed in this department.
        for (int j = 0; j < availableSymptoms.size(); j++)
        {
            if (selectedSymptoms[i] == availableSymptoms[j])
            {
                found = true;
                break;
            }
        }

        // Reject the selection if the symptom is not allowed.
        if (found == false)
        {
            return false;
        }

        // Make sure the patient has not selected the same symptom twice.
        for (int j = 0; j < i; j++)
        {
            if (selectedSymptoms[i] == selectedSymptoms[j])
            {
                return false;
            }
        }
    }

    return true;
}