#pragma once
#include <iostream>
#include <vector>
#include "SafeArticles.h"

//树枝节点，相比于叶子节点，有自己的额外方法,添加和移除叶子节点，所以这是安全组合模式

struct TransBags : TransArticles
{
    TransBags(std::string name);
    float Caculation() override;
    void Show() override;
    std::string& GetName() override;

    void Add(TransArticles* );
    void Remove(TransArticles*);
    TransArticles* GetChild(int index);

private:
    std::string name;
    std::vector<TransArticles*> bags;
};
