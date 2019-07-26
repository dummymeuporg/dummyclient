#pragma once

#include <queue>
#include <dummy/utils/singleton.hpp>

class CustomEvent {
public:

    enum Type {
        None,
        ButtonClicked,
        SetFocus,
        ReleaseFocus,
        LeftArrowPressed,
        RightArrowPressed,

        // XXX: For now there is no reason
        // to put these elsewhere:
        LoadMapFromFile,
        MapFileLoaded,
        CharacterCreated,
        CharacterSelected,
        MapViewLoaded,
        MovementActive,
        MovementInactive,

        Count
    };

    CustomEvent(void* = nullptr, Type = None, void* = nullptr);

    void* source() const {
        return m_eventSource;
    }

    void* target() const {
        return m_eventTarget;
    }

    Type type() const {
        return m_type;
    }

private:
    void* m_eventSource;
    Type m_type;
    void* m_eventTarget;

};

class CustomEventQueue : public Singleton<CustomEventQueue> {
public:
    CustomEventQueue();
    void pollEvent(CustomEvent&);
    void pushEvent(const CustomEvent&);

private:
    std::queue<CustomEvent> m_eventsQueue;
};
