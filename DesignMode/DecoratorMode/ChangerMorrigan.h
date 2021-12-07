#pragma once
#include "Morrigan.h"
#include <memory>

struct ChangerMorrigan : Morrigan
{
    ChangerMorrigan(Morrigan* mg):m_ptr(mg){}
    void Display() override;

private:
    std::shared_ptr<Morrigan> m_ptr;
};
