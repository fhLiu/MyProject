#pragma once
#include "ChessPieces.h"
#include <vector>
#include <iostream>
#include <memory>

struct WeiqiFactory
{
    WeiqiFactory();
    ChessPieces* GetChessPieces(std::string type);

private:
    std::vector<std::shared_ptr<ChessPieces>> vcp;
};
