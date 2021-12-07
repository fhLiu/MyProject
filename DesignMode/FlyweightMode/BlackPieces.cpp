#include "BlackPieces.h"
#include <iostream>

void BlackPieces::DownPieces(Point& pt)
{
    std::cout<<"黑子落棋, 落棋位置为： "<<pt.x<<", "<<pt.y<<std::endl;
}