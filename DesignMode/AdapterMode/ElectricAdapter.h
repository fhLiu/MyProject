#pragma once

#include <memory>
#include "Motor.h"
#include "ElectricMotor.h"

struct ElectricAdapter : Motor
{
    ElectricAdapter(ElectricMotor * em);
    void Drive() override;

private:
    std::shared_ptr<ElectricMotor> p_em;
};
