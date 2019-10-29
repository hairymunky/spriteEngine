#include "event_controller.h"

EventController* EventController::spInstance = nullptr;

EventController* EventController::getInstance() {
    if (!spInstance)
        spInstance = new EventController();

    return spInstance;
}

void EventController::destroy() {
    
    delete spInstance;
}


EventController::EventController() {}

EventController::~EventController() {
    // delete all pointers!
    for (auto s : mSubscribers) {
        delete s->handler;
        s->handler == nullptr;
    }

    mSubscribers.clear();

    while (!mEvents.empty()) {

        mEvents.pop();
    }
}



#ifdef DEBUG
void EventController::showSubscribers() {
    for (auto sub : mSubscribers) {
        printf("Subscriber: %s\n", sub->handler->name().c_str());
    }
}

void EventController::showEvents() {
    printf("*** WARNING THIS DELETES EVENTS IN THE QUEUE ***\n");
    while (!mEvents.empty()) {
        printf("Event: %s\n", mEvents.front()->name().c_str());
        mEvents.pop();
    }
}
#endif // DEBUG

void EventController::requestEvent(Event::EventType type, Handler* who) {

    Subscriber* sub = new Subscriber(type, who);
    mSubscribers.push_back(sub);
}

void EventController::unrequestEvent(Event::EventType type, Handler* who) {
    
    for (auto sub : mSubscribers) {
        if (sub->handler == who && sub->eventType == type) {
            sub->eventType = Event::EventType::DEACTIVATED;
        }
    }
}


void EventController::unrequestAllEvents(Handler* who) {
    
    for (auto sub : mSubscribers) {
        if (sub->handler == who) {
            sub->eventType = Event::EventType::DEACTIVATED;
            delete sub->handler;
        }
    }
}


void EventController::addEventToQueue(Event* ev) {

    mEvents.push(ev);
}


bool EventController::sendEvents() {
    
    if (mEvents.empty())
        return false; // no events to process

    while (!mEvents.empty()) {

        Event* ev = mEvents.front();

        for (auto sub : mSubscribers) {
            if (sub->eventType == ev->type()) {
                sub->handler->receiveEvent(ev);
            }
        }

        // Delete the event
        mEvents.pop();
    }
    return true;
}