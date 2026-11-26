
#ifndef SYMPTOMS_H
#define SYMPTOMS_H

#include "common.h"
#include <vector>
#include <string>

// All the symptoms that patients can select in MediAssist.
enum class Symptom
{
    // General symptoms available in every department
    Fever,
    Fatigue,
    Headache,
    Dizziness,
    GeneralWeakness,

    // Cardiology symptoms
    ChestDiscomfort,
    Palpitations,
    Fainting,
    LegSwelling,

    // Respiratory symptoms
    Cough,
    SoreThroat,
    Wheezing,
    BreathingDifficulty,
    ChestTightness,

    // Gastroenterology symptoms
    AbdominalPain,
    Nausea,
    Vomiting,
    Diarrhea,
    BloodInStool,

    // Orthopedics symptoms
    JointPain,
    BackPain,
    JointSwelling,
    LimitedMovement,
    LimbInjury,
    SuspectedFracture
};


// These are the two possible priorities for an appointment.
enum class Priority
{
    Routine,
    Urgent
};


// Returns the points assigned to a selected symptom.
int getSymptomPoints(Symptom symptom);

// Adds the points of all selected symptoms.
int calculateTriageScore(const vector<Symptom>& symptoms);

// Checks the score and decides the appointment's priority.
Priority determinePriority(int triageScore);

// Returns general symptoms and symptoms of the selected department.
vector<Symptom> getAvailableSymptoms(const string& departmentName);

#endif
