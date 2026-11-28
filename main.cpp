//#include "Common.h"
//#include "Managers/HospitalSystem.h"
//#include "Interface/CLI.h"
//
//int main()
//{
//    HospitalSystem hospital;
//    
//	hospital.loadHospitalData(); // Load data from files if available
//
//    CLI cli(hospital);
//
//    cli.run();
//
//	hospital.saveHospitalData(); // Save data to files before exiting
//
//    return 0;
//}



#include "Common.h"
#include "Managers/HospitalSystem.h"
#include "Interface/CLI.h"

int main()
{
    HospitalSystem hospital;

    if (!hospital.loadHospitalData())
    {
        cout << RED << "Error loading hospital data!" << RESET << endl;
        return 1;
    }

    cout << GREEN << "Hospital data loaded successfully!" << RESET << endl;

    CLI cli(hospital);

    cli.run();

    if (!hospital.saveHospitalData())
    {
        cout << RED << "Error saving hospital data!" << RESET << endl;
        return 1;
    }

    cout << GREEN << "Hospital data saved successfully!" << RESET << endl;

    return 0;
}
