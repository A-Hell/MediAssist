#include "Common.h"
#include "Managers/HospitalSystem.h"
#include "Interface/CLI.h"

int main()
{
    HospitalSystem hospital;

    CLI cli(hospital);

    cli.run();

    return 0;
}
