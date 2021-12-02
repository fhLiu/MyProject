#include "CZSpecialtyProxy.h"
#include <iostream>

void CZSpecialtyProxy::Show()
{
    PreShow();
    sp->Show();
    PostShow();
}

void CZSpecialtyProxy::PreShow()
{
    std::cout<<"我是湖南CZ代理，买3件98折，买5件9折，10件以上85折。。。"<<std::endl;
}

void CZSpecialtyProxy::PostShow()
{
    std::cout<<"门面地址：湖南CZ XXX区XXX路XXX号，淘宝店铺搜索CZ AR总代理..."<<std::endl;
}