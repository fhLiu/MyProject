#include "Direction.h"

Direction::Direction(Builder *ptr):m_ptr(ptr)
{}

void Direction::CreateAutomobile()
{
    m_ptr->BuildBody();
    m_ptr->BuildTire();
    m_ptr->BuildEngine();
    m_ptr->BuildControlSystem();
    m_ptr->BuildDisplaySystem();
    m_ptr->ToString();
}

void Direction::Reset(Builder* ptr)
{
    m_ptr.reset(ptr);
}