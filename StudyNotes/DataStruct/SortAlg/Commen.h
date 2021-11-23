#pragma once

constexpr int MAXSIZE = 10;

struct SqList
{
    SqList():length(0){}
    int arr[MAXSIZE+1];
    int length;
};

template<typename T>
void ElemSwap(T& lh, T& rh)
{
    T tmp;
    tmp = lh;
    lh = rh;
    rh = tmp;
    return;
}

