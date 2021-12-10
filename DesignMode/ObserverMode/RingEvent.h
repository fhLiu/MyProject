#pragma once
#include <iostream>

enum struct SOUND_TYPE{SHANGKE, XIAKE};

struct RingEvent
{
    RingEvent():sound_type(SOUND_TYPE::XIAKE){}

    SOUND_TYPE GetRing()
    {
        return sound_type;
    }
    
    void ChangeSoundType(SOUND_TYPE type)
    {
        sound_type = type;
    }

    bool IsShangke()
    {
        return sound_type == SOUND_TYPE::SHANGKE;
    }
private:
    SOUND_TYPE sound_type;
};
