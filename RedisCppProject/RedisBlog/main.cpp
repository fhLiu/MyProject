#include <iostream>
#include <string>
#include "gtest/gtest.h"

using namespace std;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::UnitTest;

int main(int argc, char **argv)
{
    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}