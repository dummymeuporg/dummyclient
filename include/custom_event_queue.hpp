#pragma once

#include <queue>
#include <dummy/utils/singleton.hpp>

class Visual;

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
        EnterKeyPressed,
        EscapeKeyPressed,
        QuitButtonClicked,
        ChangeCharacterButtonClicked,
        CancelButtonClicked,

        MouseEntered,
        MouseLeft,
        LeftClick,

        Count
    };

    CustomEvent(Visual* = nullptr, Type = None, Visual* = nullptr);

    Visual* source() const {
        return m_eventSource;
    }

    Visual* target() const {
        return m_eventTarget;
    }

    Type type() const {
        return m_type;
    }

private:
    Visual* m_eventSource;
    Type m_type;
    Visual* m_eventTarget;

};

class CustomEventQueue : public Singleton<CustomEventQueue> {
public:
    CustomEventQueue();
    void pollEvent(CustomEvent&);
    void pushEvent(const CustomEvent&);
    void pushEvent(CustomEvent&&);

private:
    std::queue<CustomEvent> m_eventsQueue;
};
