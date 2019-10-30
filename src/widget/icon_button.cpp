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
    bool forwardEvent = true;
    switch(event.type) {
    case sf::Event::MouseMoved:
        forwardEvent = _onMouseMoved(event);
        break;
    case sf::Event::MouseButtonPressed:
        forwardEvent = _onMouseButtonPressed(event);
        break;
    case sf::Event::MouseButtonReleased:
        forwardEvent = _onMouseButtonReleased(event);
        break;
    default:
        break;
    }

    return forwardEvent;
}

bool IconButton::_onMouseMoved(const sf::Event& event) {
    bool forwardEvent(true);
    const auto& origin(m_button.getOrigin());
    sf::Vector2f buttonPos(m_x - origin.x, m_y - origin.y);
    if ((event.mouseMove.x >= (buttonPos.x)) &&
            (event.mouseMove.x <= (buttonPos.x + m_button.getSize().x)) &&
            (event.mouseMove.y >= (buttonPos.y)) &&
            (event.mouseMove.y <= (buttonPos.y + m_button.getSize().y)))
    {
        forwardEvent = false;
        if (!m_isHovered)
        {
            m_isHovered = true;
        }
    } else {
        m_isHovered = false;
    }
    return forwardEvent;
}

bool IconButton::_onMouseButtonPressed(const sf::Event& event) {
    bool forwardEvent(true);
    if (m_isHovered && !m_isPushed &&
            event.mouseButton.button == sf::Mouse::Left) {
        // Consider the button being clicked.
        m_isPushed = true;
        forwardEvent = false;
    }
    return true;
}

bool IconButton::_onMouseButtonReleased(const sf::Event& event) {
    bool forwardEvent = true;
    if (m_isHovered && m_isPushed)
    {
        if (event.mouseButton.button == sf::Mouse::Left) {
            m_isPushed = false;
            pushEvent(
                CustomEvent(this, CustomEvent::ButtonClicked, nullptr)
            );
            forwardEvent = false;
        }
    }
    return forwardEvent;
}


} // namespace Widget
