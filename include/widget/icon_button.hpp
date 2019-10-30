#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class IconButton : public Abstract::Widget {
public:
    IconButton(Visual&);
    void draw(sf::RenderWindow&) override;
    bool handleEvent(const sf::Event& event) override;
    sf::IntRect boundingRect() const override;

    void setSize(std::uint16_t, std::uint16_t);

    // XXX: temporary
    void setColor(const sf::Color& color);

protected:
    bool _onMouseMoved(const sf::Event&);
    bool _onMouseButtonPressed(const sf::Event&);
    bool _onMouseButtonReleased(const sf::Event&);
    bool m_isHovered;
    bool m_isClicked;
    bool m_isPushed;

    // XXX: temporary
    sf::RectangleShape m_button;

};

}
