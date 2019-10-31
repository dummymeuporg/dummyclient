#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class FloatWindow : public Abstract::Widget {
public:
    FloatWindow(Visual&);
    void draw(sf::RenderWindow&) override;
    bool handleEvent(const sf::Event& event) override;
    sf::IntRect boundingRect() const override;
private:
    sf::RectangleShape m_window;
    sf::RectangleShape m_statusBar;
    sf::RectangleShape m_closeButton;
};

} // namespace Widget
