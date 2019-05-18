#include <iostream>
#include "widget/textbox.hpp"

namespace Widget {

Textbox::Textbox(std::shared_ptr<Widget> parent)
    : Widget(parent), m_isHovered(false), m_isFocused(false)
{

}

void Textbox::paint(sf::RenderWindow& renderWindow) {
    renderWindow.draw(m_shape);
    const sf::Vector2f& shapePos(m_shape.getPosition());
    m_text.setPosition(shapePos.x + 5, shapePos.y + 5);
    renderWindow.draw(m_text);
}

bool Textbox::_onMouseMoved(const sf::Event& event) {
    bool forwardEvent = true;
    const sf::Vector2f& origin(m_shape.getPosition());
    const sf::FloatRect& bounds(m_shape.getLocalBounds());

    if (event.mouseMove.x >= origin.x &&
        event.mouseMove.y >= origin.y &&
        event.mouseMove.x <= (origin.x + bounds.width) &&
        event.mouseMove.y <= (origin.y + bounds.height))
    {
        std::cerr << "Is hovered." << std::endl;
        m_isHovered = true;
    }
    else
    {
        m_isHovered = false;
    }
    return forwardEvent;
}

bool Textbox::_onMouseButtonPressed(const sf::Event& event) {
    bool forwardEvent = true;

    // Do not handle the event if the textbox is not hovered but focused,
    // release the handle.
    if(!m_isHovered and m_isFocused) {
        pushEvent(
            ::CustomEvent(
                reinterpret_cast<void*>(shared_from_this().get()),
                CustomEvent::ReleaseFocus
            )
        );
        return forwardEvent;
    }

    if (event.mouseButton.button == sf::Mouse::Left) {
        // Send a focus message.
        pushEvent(
            ::CustomEvent(
                reinterpret_cast<void*>(shared_from_this().get()),
                CustomEvent::SetFocus
            )
        );
    }
    return forwardEvent;
}

void Textbox::handleCustomEvent(const ::CustomEvent& event) {
    if (event.type() == CustomEvent::Type::SetFocus) {
        m_isFocused = true;
    }
}

bool Textbox::handleEvent(const sf::Event& event) {
    bool forwardEvent = true;
    switch(event.type) {
    case sf::Event::MouseMoved:
        forwardEvent = _onMouseMoved(event);
        break;
    case sf::Event::MouseButtonPressed:
        forwardEvent = _onMouseButtonPressed(event);
        break;
    default:
        break;
    }
    return forwardEvent;
}

Textbox& Textbox::setRect(int x, int y, int width, int height) {
    m_shape.setPosition(x, y);
    m_shape.setSize(sf::Vector2f(width, height));
    return *this;
}

Textbox& Textbox::setFontSize(int fontSize) {
    m_text.setCharacterSize(fontSize);
    return *this;
}

Textbox& Textbox::setFont(const std::string& fontName) {
    m_text.setFont(font(fontName));
    return *this;
}

Textbox& Textbox::setColor(const sf::Color& color) {
    m_text.setColor(color);
    return *this;
}

Textbox& Textbox::setBackgroundColor(const sf::Color& color) {
    m_shape.setFillColor(color);
    return *this;
}

Textbox& Textbox::setBorderColor(const sf::Color& color) {
    m_shape.setOutlineThickness(5);
    m_shape.setOutlineColor(color);
    return *this;
}

Textbox& Textbox::setContent(const std::string& str)
{
    m_content.flush();
    m_content << str;
    m_text.setString(m_content.str());
    return *this;
}

} // namespace Widget
