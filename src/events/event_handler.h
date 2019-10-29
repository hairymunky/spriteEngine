#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "event.h"
#include <memory>

//////////////////////////////////////////////////
// Event Handler
// Classes derived from this class are able to
// receive and process events. They should not
// create events incase of cyclic recursion.
//////////////////////////////////////////////////
class Handler
{
public:
    virtual ~Handler() {}

    virtual void receiveEvent(Event* ev) = 0;
    virtual std::string name() = 0;
};

//////////////////////////////////////////////////
// Subscriber
// Holds the details of Handlers and the events
// they are subscribed to. Allows the publisher
// and listener not to know each other.
//////////////////////////////////////////////////
class Subscriber
{
public:
    ~Subscriber() {}
    Event::EventType eventType;
    Handler* handler;

    Subscriber(Event::EventType et, Handler* who)
        : eventType(et), handler(who) {}
};

//////////////////////////////////////////////////
// Publisher
// Classes derived from `publisher` can generate
// events and pass them to the broker for broadcast
// to subscribers. Doesn't care who subscribes!
//////////////////////////////////////////////////
class Publisher
{
public:
    virtual ~Publisher() {}
    virtual void sendEvent(Event* ev) = 0;
    virtual std::string name() = 0;
};

#endif //!EVENT_HANDLER_H