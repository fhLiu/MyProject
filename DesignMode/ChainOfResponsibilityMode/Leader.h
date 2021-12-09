#pragma once
#include <memory>

struct Leader
{
    Leader();
    void SetNext(Leader* next);
    std::shared_ptr<Leader> GetNext();
    virtual bool HandleRequset(int time_len, int& nums) = 0;
private:
    std::shared_ptr<Leader> next;
protected:
    int transfer_number;
};
