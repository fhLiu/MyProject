#pragma once

#include <iostream>

/**
 * @brief 
 *  Automobile 建造过程
 */
struct Builder
{
    virtual void BuildBody() = 0;
    virtual void BuildTire() = 0;
    virtual void BuildEngine() = 0;
    virtual void BuildControlSystem() = 0;
    virtual void BuildDisplaySystem() = 0;
    virtual void ToString() = 0;

    Builder(){
        std::cout<<"Builder...."<<std::endl;
    }
    virtual ~Builder()
    {
        std::cout<<"~Builder..."<<std::endl;
    }

protected:
    std::string body;
    std::string tire;
    std::string engine;
    std::string cs;
    std::string ds;
};
