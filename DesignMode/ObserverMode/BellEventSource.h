#pragma once
#include <vector>
#include <memory>
#include "EventListener.h"
#include "RingEvent.h"

struct BellEventSource
{
    BellEventSource();
    void AddListener(std::shared_ptr<EventListener> listen);
    void Ring(RingEvent& ring);

private:
    void Notify(RingEvent& ring);
private:
    std::vector<std::shared_ptr<EventListener>> listeners;
};
