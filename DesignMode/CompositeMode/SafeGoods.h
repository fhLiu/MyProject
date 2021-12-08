#pragma once
#include "SafeArticles.h"
#include <iostream>

//叶子节点： 具体商品
struct TransGoods : TransArticles
{
    TransGoods(std::string name, int quantity, float unit_price);
    float Caculation() override;
    void Show() override;
    std::string& GetName() override;

private:
    std::string name;
    int quantity;
    float unit_price;
};
