#include "BJAutomobile.h"

void BJAutomobile::BuildBody()
{
    body.assign("宝骏车身");
}

void BJAutomobile::BuildTire()
{
    tire.assign("米其林C级轮胎");
}

void BJAutomobile::BuildEngine()
{
    engine.assign("宝骏发动机");
}

void BJAutomobile::BuildControlSystem()
{
    cs.assign("宝骏控制系统");
}

void BJAutomobile::BuildDisplaySystem()
{
    ds.assign("宝骏显示系统");
}

void BJAutomobile::ToString()
{
    std::cout<<"车身："<<body<<", 轮胎："<<tire<<", 发动机："<<engine<<
        ", 控制系统："<<cs<<", 显示系统："<<ds<<std::endl;
}