#pragma once
#include "Point.h"

struct ChessPieces
{
    virtual void DownPieces(Point& point) = 0;
    virtual ~ChessPieces(){}
};
