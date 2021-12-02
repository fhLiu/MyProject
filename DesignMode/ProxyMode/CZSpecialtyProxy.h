#pragma once
#include <memory>
#include "ARSpecialty.h"

struct CZSpecialtyProxy:Specialty
{
    CZSpecialtyProxy(Specialty* sp):sp(sp){}

    void Show() override;

private:
    void PreShow();
    void PostShow();

private:
    std::shared_ptr<Specialty> sp;
};
