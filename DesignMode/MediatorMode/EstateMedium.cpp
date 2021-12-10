#include "EstateMedium.h"
#include <algorithm>

void EstateMedium::Register(std::shared_ptr<Customer> member)
{
    auto res = std::find_if(members.begin(), members.end(),[member](std::shared_ptr<Customer> it){
        return it->GetName() == member->GetName();
    });

    if (res != members.end())
    {
        members.push_back(member);    
    }
}

void EstateMedium::Relay(std::string from, std::string to)
{
    for (auto elem : members)
    {
        if(from != elem->GetName())
        {
            elem->Receive(from, to);
        }
    }
    
}