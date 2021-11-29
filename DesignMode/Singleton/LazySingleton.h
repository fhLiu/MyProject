#pragma once

struct LazySingleton
{
    static LazySingleton* GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new LazySingleton();
            return instance;
        }
        
    }

    static void DestoryInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    static int GetCounter()
    {
        count++;
        if(count == 50000000)
            count = 0;
        return count;
    }

private:
    LazySingleton(){}
    LazySingleton(const LazySingleton&){}
    LazySingleton& operator=(const LazySingleton&){}

private:
    static LazySingleton *instance;

private:
    static int count;
};
