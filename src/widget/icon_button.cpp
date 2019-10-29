#include "widget/icon_button.hpp"

namespace Widget {

IconButton::IconButton(Visual& parent) : Widget(parent) {}

void IconButton::setSize(std::uint16_t x, std::uint16_t y) {
    Widget::setSize(x, y);
    m_button.setSize(sf::Vector2f(x, y));
}

void IconButton::setColor(const sf::Color& color) {
    m_button.setFillColor(color);
}

void IconButton::draw(sf::RenderWindow& window) {
    window.draw(m_button);
}
bool IconButton::handleEvent(const sf::Event& event) {
    return true;
}

} // namespace Widget
