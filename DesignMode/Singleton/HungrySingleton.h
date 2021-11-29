#pragma once

struct HungrySingleton
{
    static HungrySingleton* GetInstance()
    {
        return instance;
    }

private:
    HungrySingleton(){};
    HungrySingleton& operator=(const HungrySingleton&){}

private:
    static HungrySingleton* instance;
};
