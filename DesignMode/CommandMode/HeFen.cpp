#include "HeFen.h"

HeFen::HeFen():sp(new HeFenChef())
{

}

void HeFen::Cooking()
{
    sp->action();
}