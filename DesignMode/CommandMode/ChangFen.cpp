#include "ChangFen.h"

ChangFen::ChangFen():sp(new ChangFenChef())
{

}

void ChangFen::Cooking()
{
    sp->action();
}