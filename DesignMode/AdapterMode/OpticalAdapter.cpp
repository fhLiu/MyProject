#include "OpticalAdapter.h"

OpticalAdapter::OpticalAdapter(OpticalMotor *om):p_om(om)
{

}

void OpticalAdapter::Drive()
{
    p_om->OpticalDrive();
}