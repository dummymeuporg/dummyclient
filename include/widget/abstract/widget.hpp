#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "custom_event_queue.hpp"
#include "game_element.hpp"
#include "resource_provider.hpp"

namespace Widget {

namespace Abstract {

class Widget : public std::enable_shared_from_this<Widget>,
               public ::GameElement
{
public:
    Widget(std::shared_ptr<Widget> = nullptr);
    virtual void paint(sf::RenderWindow&) = 0;
    virtual bool handleEvent(const sf::Event& event);
    Widget& setPos(std::uint16_t, std::uint16_t);

    std::uint16_t x() const {
        return m_x;
    }

    std::uint16_t y() const {
        return m_y;
    }

    std::shared_ptr<Widget> parent() const {
        return m_parent;
    }
protected:
    std::shared_ptr<Widget> m_parent;
    ::ResourceProvider& m_resourceProvider;
    ::CustomEventQueue& m_eventQueue;
    std::uint16_t m_x, m_y;

};

} // namespace Abstract

} // namespace Widget
