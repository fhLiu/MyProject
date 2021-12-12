#include <iostream>
#include <memory>
#include "FourQueue.h"
#include "gtest/gtest.h"



using namespace std;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::UnitTest;

struct NormalAlgorithmTest : testing::Test
{
    void SetUp()override
    {
    }
    void TearDown()override
    {
    }
};

TEST_F(NormalAlgorithmTest, FOUR_QUEUE_POSITION_ISSUE)
{
    NQueue<4> que;
    que.Running();

    NQueue<8> que1;
    que1.Running();
}


int main(int argc, char *argv[])
{
    cout<<"Welcome Algorithm World..."<<endl;

    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}