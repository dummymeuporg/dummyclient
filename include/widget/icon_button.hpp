#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class IconButton : public Abstract::Widget {
public:
    IconButton(Visual&);
    void draw(sf::RenderWindow&) override;
    //bool handleCustomEvent(const ::CustomEvent&) override;
    sf::IntRect boundingRect() const override;

    void setSize(std::uint16_t, std::uint16_t);

    // XXX: temporary
    void setColor(const sf::Color& color);

    // XXX: temporary
    sf::RectangleShape m_button;

};

}
