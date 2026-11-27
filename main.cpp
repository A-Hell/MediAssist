#include "Common.h"
#include "Managers/HospitalSystem.h"
#include "Interface/CLI.h"

int main()
{
    HospitalSystem hospital;
	// Hard coded departments for testing 
	int dep1 = hospital.createDepartment("Cardiology", "Heart-related treatments and procedures.", "Building A, Floor 2");
	int dep2 = hospital.createDepartment("Respiratory", "Treatment of lung and breathing disorders.", "Building B, Floor 1");
	int dep3 = hospital.createDepartment("Gastroenterology", "Treatment of digestive system disorders.", "Building C, Floor 3");
	int dep4 = hospital.createDepartment("Orthopedics", "Treatment of bones, joints, and muscles.", "Building D, Floor 4");

	// Hard coded doctors for testing
	hospital.registerDoctor(dep1, "Dr. Alice Smith", "555-1234", "Cardiologist");
	hospital.registerDoctor(dep2, "Dr. Bob Johnson", "555-5678", "Pulmonologist");
	hospital.registerDoctor(dep3, "Dr. Carol Williams", "555-8765", "Gastroenterologist");
	hospital.registerDoctor(dep4, "Dr. David Brown", "555-4321", "Orthopedic Surgeon");

    CLI cli(hospital);

    cli.run();

    return 0;
}
