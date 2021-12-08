#pragma once
#include <iostream>

//抽象构建： 物品
struct TransArticles
{
    virtual float Caculation() = 0;
    virtual void Show() = 0;
    virtual std::string& GetName() = 0;

    virtual ~TransArticles(){}
};
