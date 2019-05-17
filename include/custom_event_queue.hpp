#pragma once

#include <queue>
#include "utils/singleton.hpp"

class CustomEvent {
public:

    enum Type {
        None,
        ButtonClicked,
        SetFocus,
        ReleaseFocus,

        Count
    };

    CustomEvent(const void* = nullptr, Type = None);

    const void* source() const {
        return m_eventSource;
    }

    Type type() const {
        return m_type;
    }

private:
    const void* m_eventSource;
    Type m_type;

};

class CustomEventQueue : public Singleton<CustomEventQueue> {
public:
    CustomEventQueue();
    void pollEvent(CustomEvent&);
    void pushEvent(const CustomEvent&);

private:
    std::queue<CustomEvent> m_eventsQueue;
};
