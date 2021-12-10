#pragma once
#include <vector>
#include <memory>
#include "Medium.h"
#include "Customer.h"

struct EstateMedium : Medium
{
    void Register(std::shared_ptr<Customer> member) override;
    void Relay(std::string, std::string) override;
private:
    std::vector<std::shared_ptr<Customer>> members;
};
