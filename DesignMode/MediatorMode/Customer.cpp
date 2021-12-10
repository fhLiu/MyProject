#include "Customer.h"

void Customer::SetMedium(Medium* medium)
{
    this->medium.reset(medium);
}

std::string& Customer::GetName()
{
    return name;
}