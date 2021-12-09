#include "HunDun.h"

HunDun::HunDun():sp(new HunDunChef())
{

}

void HunDun::Cooking()
{
    sp->action();
}