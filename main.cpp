#include "Common.h"
#include "Managers/HospitalSystem.h"
#include "Interface/CLI.h"

int main()
{
    HospitalSystem hospital;
    
	hospital.loadHospitalData(); // Load data from files if available

    CLI cli(hospital);

    cli.run();

	hospital.saveHospitalData(); // Save data to files before exiting

    return 0;
}
