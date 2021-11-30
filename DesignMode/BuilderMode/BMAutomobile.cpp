#include "BMAutomobile.h"


void BMAutomobile::BuildBody()
{
    body.assign("宝马车身");
}

void BMAutomobile::BuildTire()
{
    tire.assign("米其林A级轮胎");
}

void BMAutomobile::BuildEngine()
{
    engine.assign("宝马发动机");
}

void BMAutomobile::BuildControlSystem()
{
    cs.assign("宝马控制系统");
}

void BMAutomobile::BuildDisplaySystem()
{
    ds.assign("宝马显示系统");
}

void BMAutomobile::ToString()
{
    std::cout<<"车身："<<body<<", 轮胎："<<tire<<", 发动机："<<engine<<
        ", 控制系统："<<cs<<", 显示系统："<<ds<<std::endl;
}