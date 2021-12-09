#include "Leader.h"

Leader::Leader():next(nullptr),transfer_number(0)
{}

void Leader::SetNext(Leader* next)
{
    this->next.reset(next);
}

std::shared_ptr<Leader> Leader::GetNext()
{
    return next;
}