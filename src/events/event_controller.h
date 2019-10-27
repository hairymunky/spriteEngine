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
    std::vector<std::shared_ptr<Subscriber>> mSubscribers;
    std::queue<std::shared_ptr<Event>> mEvents;

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

    void requestEvent(Event::EventType type, std::shared_ptr<Handler> who);
    void unrequestEvent(Event::EventType type, std::shared_ptr<Handler> who);
    void unrequestAllEvents(std::shared_ptr<Handler> who);

    bool sendEvents();

    void addEventToQueue(std::shared_ptr<Event> ev);
};

#endif //!EVENT_CONTROLLER_H