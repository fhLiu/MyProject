#include "Girl.h"
#include <iostream>

Girl::Girl(Morrigan* cm):ChangerMorrigan(cm)
{}

void Girl::SetChange()
{
    std::cout<<"变身超级美少女！"<<std::endl;
}

void Girl::Display()
{
    SetChange();
    ChangerMorrigan::Display();
}