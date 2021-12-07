#pragma once
#include "ChessPieces.h"

struct WhitePieces : ChessPieces
{
    void DownPieces(Point& pt) override;
};
