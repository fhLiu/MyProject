#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "LazySingleton.h"

using namespace std;

using namespace std;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::UnitTest;

struct DesignModeTest : testing::Test
{
    void SetUp()override
    {
    }
    void TearDown()override
    {
    }
};

TEST_F(DesignModeTest, SINGLETON_LAZY_MODE_NORMAL)
{
    auto instance = LazySingleton::GetInstance();
    EXPECT_EQ(instance->GetCounter, 1);
}




int main(int argc, char *argv[])
{
    cout<<"Welcome DisignMode World..."<<endl;

    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}