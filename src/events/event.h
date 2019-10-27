#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event
{
public:
    enum class EventType
    {
        WINDOW_CLOSE = 1,
        MOUSE_MOVE,
        DEACTIVATED = 999 // for unsubbed
    };

    Event(EventType type) : mType(type) {}

    virtual std::string name() = 0;
    EventType type() { return mType; }

    virtual ~Event() {}

protected:
    EventType mType;
};

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() : Event(Event::EventType::WINDOW_CLOSE) {}
    ~WindowCloseEvent() {}
    std::string name() override { return "WINDOW_CLOSE"; }
};

class MouseMoveEvent : public Event
{
public:
    MouseMoveEvent(int x, int y) : Event(Event::EventType::MOUSE_MOVE), mX(x), mY(y) {}
    ~MouseMoveEvent() {}
    std::string name() override { return "MOUSE_MOVE"; }
    void getMouse(int &x, int &y)
    {
        x = mX;
        y = mY;
    }

protected:
    int mX{0}, mY{0};
};

#endif //!EVENT_H