#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "LazySingleton.h"
#include "SimpleFactory.h"
#include "Direction.h"
#include "AbFactoryOne.h"
#include "AbFactoryTwo.h"

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
    EXPECT_EQ(instance->GetCounter(), 1);
}

TEST_F(DesignModeTest, SIMPLE_FACTORY_PRODUCE_PRODUCT)
{
    SimpleFactory sf;
    std::shared_ptr<SimpleProducer> sp(sf.CreateProduct(PRODUCT_TYPE::TYPE_A));
    sp->ProduceProduct();
    sp.reset(sf.CreateProduct(PRODUCT_TYPE::TYPE_B));
    sp->ProduceProduct();
}

TEST_F(DesignModeTest, FACTORY_METHOD_PRODUCE_PRODUCT)
{
   std::shared_ptr<AbFactory> factory(new AbFactoryOne());
   factory->CreateProduct()->Show();
   factory.reset(new AbFactoryTwo());
   factory->CreateProduct()->Show();
}

TEST_F(DesignModeTest, BUILD_MODE_AUTOMOBILE)
{
    Direction direc(new BJAutomobile());
    direc.CreateAutomobile();

    direc.Reset(new BMAutomobile());
    direc.CreateAutomobile();
}



int main(int argc, char *argv[])
{
    cout<<"Welcome DisignMode World..."<<endl;

    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}