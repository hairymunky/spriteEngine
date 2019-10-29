#ifndef EVENT_CONTROLLER_H
#define EVENT_CONTROLLER_H

#include "event_handler.h"
#include <vector>
#include <queue>

//////////////////////////////////////////////////
// EventController
// Responsible for sending events to subscribers
// This should be done every frame (ideally).
//////////////////////////////////////////////////
class EventController {
    std::vector<Subscriber*> mSubscribers;
    std::queue<Event*> mEvents;

    EventController();

    static EventController *spInstance;

    public:

    static EventController* getInstance();
    static void destroy();
    
    ~EventController();

#ifdef DEBUG
    void showSubscribers();
    void showEvents();
#endif 

    void requestEvent(Event::EventType type, Handler* who);
    void unrequestEvent(Event::EventType type, Handler* who);
    void unrequestAllEvents(Handler* who);

    bool sendEvents();

    void addEventToQueue(Event* ev);
};

#endif //!EVENT_CONTROLLER_H