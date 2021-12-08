#include "SafeBags.h"

TransBags::TransBags(std::string name):name(name)
{

}

float TransBags::Caculation()
{
    float sum = 0;
    for (auto elem: bags)
    {
        sum += elem->Caculation();
    }

    return sum;
}

void TransBags::Show()
{
    for (auto elem : bags)
    {
        std::cout<<name<<"::";
        elem->Show();
    }
}

std::string& TransBags::GetName()
{
    return name;
}

void TransBags::Add(TransArticles* elem)
{
    bags.push_back(elem);
}

void TransBags::Remove(TransArticles* elem)
{
    for(auto it = bags.begin(); it != bags.end();)
    {
        if ((*it)->GetName()  == elem->GetName())
        {
            it = bags.erase((it));
        }
        else{
            (it)++;
        }
        
    }
    
}