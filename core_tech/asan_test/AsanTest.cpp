#include "AsanTest.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

void asan_example_memory_overflow()
{
    UInt8 ip[10];
    memcpy(ip, "12345678901232154", 15);
}

void asan_example_memory_leak()
{
    UInt16 *pss = new UInt16(65);
    std::cout<<"p is : "<<*pss<<std::endl;
    return;
}

void asan_example_memory_invalid()
{
    SInt8 *p = nullptr;
    strcpy(p, "a");

    return;
}



void handle_asan_examples()
{
    // asan_example_memory_overflow();
    asan_example_memory_leak();
    asan_example_memory_invalid();
    return;
}