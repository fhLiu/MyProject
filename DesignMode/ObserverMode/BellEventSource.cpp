#include "BellEventSource.h"
#include <map>

namespace {
    std::map<SOUND_TYPE, std::string>  dump_assosi = {{SOUND_TYPE::SHANGKE, "叮叮叮，上课铃声响了。。。。。。"},
                                                    {SOUND_TYPE::XIAKE, "叮叮叮，下课铃声响了。。。。。。"}};  
}

BellEventSource::BellEventSource(){}

void BellEventSource::AddListener(std::shared_ptr<EventListener> listen)
{
    listeners.push_back(listen);
}

void BellEventSource::Ring(RingEvent& ring)
{
    std::cout<<dump_assosi[ring.GetRing()]<<std::endl;
    Notify(ring);
}

void BellEventSource::Notify(RingEvent& ring)
{

    for (auto& elem : listeners)
    {
        if (ring.IsShangke())
        {
            elem->Shangke();
        }else
        {
            elem->Xiake();
        }   
    }
}