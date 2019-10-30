#pragma once

#include <memory>
#include <set>

#include "game_element.hpp"

class Game;

class Visual : public std::enable_shared_from_this<Visual>,
               public ::GameElement
{
public:
    Visual();
    virtual void draw(sf::RenderWindow&) = 0;
    virtual bool handleEvent(const sf::Event&);
    void handleCustomEvent(const ::CustomEvent&);

    virtual void setPos(std::uint16_t, std::uint16_t);
    virtual void setSize(std::uint16_t, std::uint16_t);

    std::uint16_t x() const {
        return m_x;
    }

    std::uint16_t y() const {
        return m_y;
    }

    std::uint16_t width() const {
        return m_width;
    }

    std::uint16_t height() const {
        return m_height;
    }

    bool isEnabled() const {
        return m_isEnabled;
    }

    void addChild(std::shared_ptr<Visual>);
    void removeChild(std::shared_ptr<Visual>);
    void setEnabled(bool);
protected:
    ::ResourceProvider& m_resourceProvider;
    ::CustomEventQueue& m_eventQueue;
    std::uint16_t m_x, m_y;
    std::uint16_t m_width, m_height;
    std::set<std::shared_ptr<Visual>> m_children;
    Visual* m_focusedChild;
    bool m_isEnabled;
};
