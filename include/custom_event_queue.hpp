#pragma once

#include <queue>

class CustomEvent {
public:

    enum Type {
        None,
        ButtonClicked,

        Count
    };

    CustomEvent(const void*, Type);

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

class CustomEventQueue {
public:
    CustomEventQueue();
    void pollEvent(CustomEvent&);
    void pushEvent(const CustomEvent&);

private:
    std::queue<CustomEvent> m_eventsQueue;
};
