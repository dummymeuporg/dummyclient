#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "custom_event_queue.hpp"
#include "resource_provider.hpp"
#include "visual.hpp"

namespace Widget {

namespace Abstract {

class Widget : public ::Visual
{
public:
    Widget(Visual&);
    void draw(sf::RenderWindow&) override;
    virtual void setPos(std::uint16_t, std::uint16_t);

    std::uint16_t x() const {
        return m_x;
    }

    std::uint16_t y() const {
        return m_y;
    }

    bool isEnabled() const {
        return m_isEnabled;
    }

protected:
    Visual& m_parent;

};

} // namespace Abstract

} // namespace Widget
