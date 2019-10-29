#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class IconButton : public Abstract::Widget {
public:
    IconButton(Visual&);
    void draw(sf::RenderWindow&) override;
    bool handleEvent(const sf::Event& event) override;

    void setSize(std::uint16_t, std::uint16_t);

    // XXX: temporary
    void setColor(const sf::Color& color);

protected:
    // XXX: temporary
    sf::RectangleShape m_button;
};

}
