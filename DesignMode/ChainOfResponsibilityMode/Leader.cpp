#include "Leader.h"

Leader::Leader():next(nullptr)
{}

void Leader::SetNext(Leader* next)
{
    this->next.reset(next);
}

std::shared_ptr<Leader> Leader::GetNext()
{
    return next;
}