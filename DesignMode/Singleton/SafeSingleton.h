#pragma once

template<typename T>
struct BaseSingleton
{
    static T& GetInstance()
    {
        static T instance;
        return instance;
    }

protected:
    BaseSingleton(){};
    BaseSingleton& operator=(const BaseSingleton&){}
};

#define SINGLETON(name) struct name : public BaseSingleton<name>


SINGLETON(SafeSingleton)
{
    
    friend BaseSingleton<SafeSingleton>;

private:
    SafeSingleton(){}
    SafeSingleton& operator=(const SafeSingleton&){}
};
