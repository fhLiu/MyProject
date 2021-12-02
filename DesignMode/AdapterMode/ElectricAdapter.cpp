#include "ElectricAdapter.h"

ElectricAdapter::ElectricAdapter(ElectricMotor * em):p_em(em)
{

}

void ElectricAdapter::Drive()
{
    p_em->ElecticDrive();
}