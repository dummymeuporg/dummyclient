#include <iostream>
#include "widget/textbox.hpp"

namespace Widget {

Textbox::Textbox(std::shared_ptr<Widget> parent)
    : Widget(parent), m_isHovered(false), m_isFocused(false),
      m_isCarretDrawn(false), m_carretIndex(0)
{

}

void Textbox::paint(sf::RenderWindow& renderWindow) {
    int delta = 30;
    sf::Color backgroundColor(m_shape.getFillColor());
    if (m_isFocused) {
        backgroundColor.r = m_backgroundColor.r + delta;
        backgroundColor.g = m_backgroundColor.g + delta;
        backgroundColor.b = m_backgroundColor.b + delta;
        
        if (m_carretClock.getElapsedTime().asMilliseconds() >= 500) {
            m_isCarretDrawn = !m_isCarretDrawn;
            m_carretClock.restart();
        }

    } else {
        backgroundColor.r = m_backgroundColor.r - delta;
        backgroundColor.g = m_backgroundColor.g - delta;
        backgroundColor.b = m_backgroundColor.b - delta;
    }

    m_shape.setFillColor(backgroundColor);

    renderWindow.draw(m_shape);
    const sf::Vector2f& shapePos(m_shape.getPosition());
    m_text.setPosition(shapePos.x + 5, shapePos.y + 5);
    renderWindow.draw(m_text);

    if (m_isCarretDrawn) {
        const sf::Vector2f& textPosition(
            m_text.findCharacterPos(m_carretIndex));
        sf::RectangleShape carret;
        carret.setPosition(textPosition.x, textPosition.y);
        carret.setSize(sf::Vector2f(2, 24));
        carret.setFillColor(sf::Color(0, 0, 0));
        renderWindow.draw(carret);
    }
}

bool Textbox::_onTextEntered(const sf::Event& event) {
    return true;
}

bool Textbox::_onKeyReleased(const sf::Event& event) {
    bool forwardEvent = true;
    std::cerr << "Key released. " << event.key.code << std::endl;
    switch(m_lastKeyInput) {
    case sf::Keyboard::Left:
        if (m_carretIndex > 0) {
            --m_carretIndex;
        }
        forwardEvent = false;
        m_lastKeyInput = sf::Keyboard::Unknown;
        m_carretClock.restart();
        m_isCarretDrawn = true;
        break;
    case sf::Keyboard::Right:
        if (m_carretIndex < m_content.str().size()) {
            ++m_carretIndex;
        }
        forwardEvent = false;
        m_lastKeyInput = sf::Keyboard::Unknown;
        m_carretClock.restart();
        m_isCarretDrawn = true;
        break;
    default:
        break;
    }
    return forwardEvent;
}

bool Textbox::_onKeyPressed(const sf::Event& event) {
    bool forwardEvent = true;
    std::cerr << "Key pressed. " << event.key.code << std::endl;
    m_lastKeyInput = event.key.code;
    return forwardEvent;
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
        std::cerr << "Release for focus." << std::endl;
        pushEvent(
            ::CustomEvent(
                reinterpret_cast<void*>(shared_from_this().get()),
                CustomEvent::ReleaseFocus,
                reinterpret_cast<void*>(shared_from_this().get())
            )
        );
        return forwardEvent;
    } else if (event.mouseButton.button == sf::Mouse::Left && m_isHovered) {
        // Send a focus message.
        pushEvent(
            ::CustomEvent(
                reinterpret_cast<void*>(shared_from_this().get()),
                CustomEvent::SetFocus,
                reinterpret_cast<void*>(shared_from_this().get())
            )
        );
        forwardEvent = false;
    }
    return forwardEvent;
}

void Textbox::handleCustomEvent(const ::CustomEvent& event) {
    if (event.type() == CustomEvent::Type::SetFocus) {
        m_isFocused = true;
        std::cerr << "Got focused." << std::endl;
        m_carretClock.restart();
        m_isCarretDrawn = true;
    } else if(event.type() == CustomEvent::Type::ReleaseFocus) {
        m_isFocused = false;
        std::cerr << "Lost focus." << std::endl;
        m_isCarretDrawn = false;
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
    case sf::Event::KeyPressed:
        forwardEvent = _onKeyPressed(event);
        break;
    case sf::Event::TextEntered:
        forwardEvent = _onTextEntered(event);
        break;
    case sf::Event::KeyReleased:
        forwardEvent = _onKeyReleased(event);
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
    m_backgroundColor = color;
    m_shape.setFillColor(m_backgroundColor);
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
