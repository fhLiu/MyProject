#pragma once
#include "ChessPieces.h"

struct BlackPieces : ChessPieces
{
    void DownPieces(Point& pt) override;
};
