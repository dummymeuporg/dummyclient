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
    virtual bool handleEvent(const sf::Event&) = 0;

    virtual void setPos(std::uint16_t, std::uint16_t);
    virtual void setSize(std::uint16_t, std::uint16_t);

    std::uint16_t x() const {
        return m_x;
    }

    std::uint16_t y() const {
        return m_y;
    }

    void addChild(std::shared_ptr<Visual>);
    void removeChild(std::shared_ptr<Visual>);
protected:
    ::ResourceProvider& m_resourceProvider;
    ::CustomEventQueue& m_eventQueue;
    std::uint16_t m_x, m_y;
    std::uint16_t m_width, m_height;
    std::set<std::shared_ptr<Visual>> m_children;
};
