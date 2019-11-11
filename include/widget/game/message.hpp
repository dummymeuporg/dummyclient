#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

namespace Game {

class Message : public Abstract::Widget {
public:
    Message(Visual&);
    void draw(sf::RenderWindow&) override;
    bool handleCustomEvent(const ::CustomEvent&) override;
    sf::IntRect boundingRect() const override;
    void setSize(std::uint16_t, std::uint16_t);
    void setContent(const std::string&);
private:
    sf::String m_message;
    sf::RectangleShape m_rectangle;
};

} // namespace Game

} // namespace Widget
