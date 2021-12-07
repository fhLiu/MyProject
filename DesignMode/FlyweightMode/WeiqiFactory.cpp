#include "WeiqiFactory.h"
#include "WhitePieces.h"
#include "BlackPieces.h"


WeiqiFactory::WeiqiFactory()
{
    std::shared_ptr<ChessPieces> sp(new WhitePieces());
    vcp.push_back(sp);
    sp.reset(new BlackPieces());
    vcp.push_back(sp);
}

ChessPieces* WeiqiFactory::GetChessPieces(std::string type)
{
    if(vcp.size() != 2)
    {
        std::cout<<"vector not more elements..."<<std::endl;
        return nullptr;
    }
    if (type == "w")
    {
        return vcp[0].get();
    }
    else if(type == "b")
    {
        return vcp[1].get();
    }
    return nullptr;
}