#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "LazySingleton.h"
#include "SimpleFactory.h"
#include "Direction.h"
#include "AbFactoryOne.h"
#include "AbFactoryTwo.h"
#include "CZSpecialtyProxy.h"
#include "OpticalAdapter.h"
#include "ElectricAdapter.h"
#include "Wallet.h"
#include "HandBag.h"
#include "Yellow.h"
#include "Red.h"
#include "Succubus.h"
#include "Girl.h"
#include "OriginalMorrigan.h"
#include "BlackPieces.h"
#include "WhitePieces.h"
#include "WeiqiFactory.h"

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

TEST_F(DesignModeTest, PROXY_MODE_CZSPECIALTY)
{
    Specialty *specialty = new ARSpecialty();
    std::shared_ptr<Specialty> proxy(new CZSpecialtyProxy(specialty));
    proxy->Show();
}

TEST_F(DesignModeTest, ADAPTER_MODE_DRIVE_SELECTION)
{
    ElectricMotor *emm = new ElectricMotor();
    OpticalMotor *omm = new OpticalMotor();
    std::shared_ptr<Motor> sp(new ElectricAdapter(emm));
    sp->Drive();
    sp.reset(new OpticalAdapter(omm));
    sp->Drive();
}

TEST_F(DesignModeTest, BRIDGE_MODE_BAG_AND_COLOR)
{
    Color *color = new Yellow();
    std::shared_ptr<Bag>  wallet(new Wallet());
    wallet->SetColor(color);
    wallet->GetName();

    color = new Red();
    wallet->SetColor(color);
    wallet->GetName();

}

TEST_F(DesignModeTest, DECORATOR_MODE_MORRIGAN)
{
    std::shared_ptr<Morrigan> mp(new OriginalMorrigan());
    mp->Display();
    
    mp.reset(new Succubus(new OriginalMorrigan()));
    mp->Display();

    mp.reset(new Girl(new OriginalMorrigan()));
    mp->Display();
}

TEST_F(DesignModeTest, FLYWEIGHT_MODE_WEIQI)
{
    WeiqiFactory *wf = new WeiqiFactory();
    Point pt;
    pt.x = 3;
    pt.y = 4;

    auto wc = wf->GetChessPieces("w");
    wc->DownPieces(pt);

    pt.x = 3;
    pt.y = 5;
    wc = wf->GetChessPieces("b");
    wc->DownPieces(pt);
    
    delete wf;
    wf = nullptr;
}

int main(int argc, char *argv[])
{
    cout<<"Welcome DisignMode World..."<<endl;

    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}