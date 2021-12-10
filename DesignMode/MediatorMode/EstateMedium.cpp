#include "EstateMedium.h"

void EstateMedium::Register(std::shared_ptr<Customer> member)
{
    members.push_back(member);
}

void EstateMedium::Relay(std::string from, std::string to)
{

}