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

EventController::~EventController() {}



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

void EventController::requestEvent(Event::EventType type, std::shared_ptr<Handler> who) {

    std::shared_ptr<Subscriber> sub = std::make_shared<Subscriber>(type, who);
    mSubscribers.push_back(sub);
}

void EventController::unrequestEvent(Event::EventType type, std::shared_ptr<Handler> who) {
    
    for (auto sub : mSubscribers) {
        if (sub->handler == who && sub->eventType == type) {
            sub->eventType = Event::EventType::DEACTIVATED;
        }
    }
}


void EventController::unrequestAllEvents(std::shared_ptr<Handler> who) {
    
    for (auto sub : mSubscribers) {
        if (sub->handler == who) {
            sub->eventType = Event::EventType::DEACTIVATED;
        }
    }
}


void EventController::addEventToQueue(std::shared_ptr<Event> ev) {

    mEvents.push(ev);
}


bool EventController::sendEvents() {
    
    if (mEvents.empty())
        return false; // no events to process

    while (!mEvents.empty()) {

        std::shared_ptr<Event> ev = mEvents.front();

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