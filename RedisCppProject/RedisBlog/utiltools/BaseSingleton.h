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
    BaseSingleton(){}
private:
    BaseSingleton(const BaseSingleton& rh){}
    BaseSingleton& operator=(const BaseSingleton& rh){}
};

#define RedisSingleton(name) struct name: public BaseSingleton<name>