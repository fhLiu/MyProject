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
#include "SafeBags.h"
#include "SafeGoods.h"
#include "AmericanStudyBorad.h"
#include "JapanStudyBorad.h"
#include "WyTour.h"
#include "ChangFen.h"
#include "HeFen.h"
#include "HunDun.h"
#include "ChainClient.h"
#include "ThreadContext.h"
#include "BellEventSource.h"
#include "StuEventListener.h"
#include "TeachEventListener.h"
#include "Originator.h"


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

TEST_F(DesignModeTest, SAFE_COMPOSITE_MODE_BAG_GOODS)
{
    TransBags bigBag("大袋子"), mediumBag("中袋子"), smallRedBag("红色小袋子"), smallWhiteBag("白色小袋子");
    TransGoods wytc("婺源特产", 2, 15),wydt("婺源地图", 4, 6.5),sgxg("韶关香菇", 2, 15.8),czlwy("郴州临武鸭", 1, 68),
    czdjy("郴州东江鱼", 3, 36),jdzcq("景德镇瓷器", 1, 198),lining("李宁运动鞋",1, 389);

    smallRedBag.Add(&wytc);
    smallRedBag.Add(&sgxg);

    smallWhiteBag.Add(&wydt);
    smallWhiteBag.Add(&czdjy);

    mediumBag.Add(&lining);
    mediumBag.Add(&smallWhiteBag);

    bigBag.Add(&jdzcq);
    bigBag.Add(&czlwy);
    bigBag.Add(&mediumBag);
    bigBag.Add(&smallRedBag);

    std::cout<<"当前选购的商品有："<<std::endl;
    bigBag.Show();
    std::cout<<"==================================================="<<std::endl;
    std::cout<<"需要支付的价格是：￥"<<bigBag.Caculation()<<"。"<<std::endl;
}

TEST_F(DesignModeTest, TEMPLATE_MODE_ABOUT_STUDY_ABROAD)
{
    std::shared_ptr<StudyAbroad> sp(new AmericanStudyBroad());
    sp->TemplateMethod();
    std::cout<<"==================================================="<<std::endl;
    sp.reset(new JapanStudyAbroad());
    sp->TemplateMethod();
}

TEST_F(DesignModeTest, STRATEGY_MODE_SG_WY_TRAFFIC_TOOLS)
{
    TripMode* car = new ByCar();
    WyTour wyt;
    wyt.SetTripMode(car);
    wyt.GoOut();

    TripMode* train = new ByTrain();
    wyt.SetTripMode(train);
    wyt.GoOut();

    TripMode* self_drive = new BySelfDrive();
    wyt.SetTripMode(self_drive);
    wyt.GoOut();
}

TEST_F(DesignModeTest, COMMAND_MODE_BREAKFAST)
{
    std::shared_ptr<BreakFast> sp(new HunDun());
    sp->Cooking();

    sp.reset(new HeFen());
    sp->Cooking();

    sp.reset(new ChangFen());
    sp->Cooking();
}

TEST_F(DesignModeTest, CHAINOFRESPONSBILITY_MODE_ABOUT_VACATION)
{
    int time_len = 5, nums = 0;
    EXPECT_EQ(LeaveApprovalProcess(time_len, nums), true);
    EXPECT_EQ(nums, 2);

    time_len = 10;
    nums = 0;
    EXPECT_EQ(LeaveApprovalProcess(time_len, nums), true);
    EXPECT_EQ(nums, 4);

    time_len = 15;
    nums = 0;
    EXPECT_EQ(LeaveApprovalProcess(time_len, nums), false);
    EXPECT_EQ(nums, 4);
}

TEST_F(DesignModeTest, STATE_MODE_THREAD_STATE_THRANSFER)
{
    std::vector<string> state_name{"新建状态","就绪状态","运行状态","阻塞状态","死亡状态"};
    ThreadContext ctxt;
    EXPECT_EQ(ctxt.GetState()->GetName(), state_name[0]);
    ctxt.Start();
    EXPECT_EQ(ctxt.GetState()->GetName(), state_name[1]);
    ctxt.GetCPU();
    ctxt.Resume();
    ctxt.Suspend();
    EXPECT_EQ(ctxt.GetState()->GetName(), state_name[3]);
    ctxt.Resume();
    EXPECT_EQ(ctxt.GetState()->GetName(), state_name[1]);
}

TEST_F(DesignModeTest, OBSERVER_MODE_RING_AND_SCHOOL)
{
    BellEventSource  obj;
    RingEvent        ring;
    
    std::shared_ptr<EventListener> stu(new StuEventListener());
    std::shared_ptr<EventListener> tech(new TeachEventListener());
    ring.ChangeSoundType(SOUND_TYPE::SHANGKE);
    obj.AddListener(tech);
    obj.AddListener(stu);
    obj.Ring(ring);
    ring.ChangeSoundType(SOUND_TYPE::XIAKE);
    obj.Ring(ring);
}

TEST_F(DesignModeTest, MEMENTOR_MODE_CLASSICAL_GIRL)
{
    std::vector<std::string> four_girl{"西施", "貂蝉", "昭君", "杨贵妃"};
    Originator initial(four_girl[0]);
    MemGirlStack mementor;
    mementor.Push(initial.CreateMementor());
    initial.SetAdmire(four_girl[2]);
    mementor.Push(initial.CreateMementor());

    initial.SetAdmire(four_girl[1]);
    mementor.Push(initial.CreateMementor());

    auto res = mementor.Pop();
    EXPECT_NE(res, nullptr);
    initial.RestoreMementor(*res);
    std::cout<<"回退到当前美女是："<<res->GetName()<<"  "<<initial.GetAdmire()<<std::endl;
}

int main(int argc, char *argv[])
{
    cout<<"Welcome DisignMode World..."<<endl;

    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}