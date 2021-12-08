#include "SafeGoods.h"
#include <iostream>

TransGoods::TransGoods(std::string name, int quantity, float unit_price):name(name),
                        quantity(quantity), unit_price(unit_price)
{

}

float TransGoods::Caculation()
{
    return quantity * unit_price;
}

void TransGoods::Show()
{
    std::cout<<name<<" 数量："<<quantity<<", 单价："<<unit_price<<" 元"<<std::endl;
}

std::string& TransGoods::GetName()
{
    return name;
}