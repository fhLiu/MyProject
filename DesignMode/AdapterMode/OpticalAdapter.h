#pragma once
#include <memory>
#include "Motor.h"
#include "OpticalMotor.h"

struct OpticalAdapter : Motor
{
    OpticalAdapter(OpticalMotor *om);
    void Drive() override;

private:
    std::shared_ptr<OpticalMotor> p_om;
};
