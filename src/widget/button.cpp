#include <iostream>
#include "widget/button.hpp"

namespace Widget {

Button::Button(std::shared_ptr<Widget> parent,
               ::ResourceProvider& resourceProvider,
               ::CustomEventQueue& eventQueue)
    : Label(parent, resourceProvider, eventQueue),
      m_isHovered(false), m_isPushed(false)
{    
}

void Button::paint(sf::RenderWindow& window) {
    // First paint the background, then the label
    window.draw(m_buttonBackground);
    Label::paint(window);
}

bool Button::_onMouseMoved(const sf::Event& event)
{
    bool forwardEvent = true;
    sf::Vector2f labelPos = m_caption.getPosition();
    sf::FloatRect textRect = m_caption.getLocalBounds();
    sf::Color bgColor = m_buttonBackground.getFillColor();
    int deltaR = 10, deltaG = 10, deltaB = 10;
    if ((event.mouseMove.x >= (labelPos.x - 10)) &&
            (event.mouseMove.x <= (labelPos.x + textRect.width + 10)) &&
            (event.mouseMove.y >= (labelPos.y - 10)) &&
            (event.mouseMove.y <= (labelPos.y + textRect.height + 10)))
    {
        // The mouse is hovering the button. No need to forward it.
        forwardEvent = false;
        if (!m_isHovered)
        {
            m_isHovered = true;
            m_buttonBackground.setFillColor(
                sf::Color(
                    bgColor.r + deltaR,
                    bgColor.g + deltaG,
                    bgColor.b + deltaB
                )
            );
        }
    } else {
        if (m_isHovered)
        {
            m_isHovered = false;
            // Cancel the push state if the mouse leaves the button.
            if (m_isPushed) {
                std::cerr << "Cancel the pushed state" << std::endl;
                m_isPushed = false;
                deltaR += 30;
                deltaG += 30;
                deltaB += 30;
            }
            sf::Color bgColor = m_buttonBackground.getFillColor();
            m_buttonBackground.setFillColor(
                sf::Color(
                    bgColor.r - deltaR,
                    bgColor.g - deltaG,
                    bgColor.b - deltaB
                )
            );

        }
    }
    return forwardEvent;
}

bool Button::_onMouseButtonPressed(const sf::Event& event) {
    // The button has to be hovered first.
    bool forwardEvent = true;
    sf::Color bgColor = m_buttonBackground.getFillColor();
    if (m_isHovered) {
        if (!m_isPushed)
        {
            if (event.mouseButton.button == sf::Mouse::Left) {
                m_isPushed = true;
                m_buttonBackground.setFillColor(
                    sf::Color(
                        bgColor.r + 30,
                        bgColor.g + 30,
                        bgColor.b + 30
                    )
                );
                forwardEvent = false;
            }
        }
    }
    return forwardEvent;
}

bool Button::_onMouseButtonReleased(const sf::Event& event) {
    bool forwardEvent = true;
    sf::Color bgColor = m_buttonBackground.getFillColor();
    if (m_isHovered && m_isPushed)
    {
        if (event.mouseButton.button == sf::Mouse::Left) {
            m_isPushed = false;
            m_buttonBackground.setFillColor(
                sf::Color(
                    bgColor.r - 30,
                    bgColor.g - 30,
                    bgColor.b - 30
                )
            );
            pushEvent(
                CustomEvent(
                    reinterpret_cast<const void*>(shared_from_this().get()),
                    CustomEvent::ButtonClicked
                )
            );
            forwardEvent = false;
        }
    }
    return forwardEvent;
}

bool Button::handleEvent(const sf::Event& event) {
    bool forwardEvent = true;
    switch(event.type)
    {
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

Button& Button::setBackgroundColor(const sf::Color& color) {
	m_buttonBackground.setFillColor(color);
    return *this;
}

Button& Button::setBorderColor(const sf::Color& color) {
    m_buttonBackground.setOutlineThickness(3);
    m_buttonBackground.setOutlineColor(color);
    return *this;
}

Button& Button::setCaption(const std::string& caption) {
    std::cerr << "Button set caption" << std::endl;
    Label::setCaption(caption);
    sf::FloatRect textRect = m_caption.getLocalBounds();
    textRect.left -= 10;
    textRect.top -= 10;
    textRect.width += 20;
    textRect.height += 20;
    
    sf::Vector2f labelPos = m_caption.getPosition();

    std::cerr << "Size: " << textRect.width << " " << textRect.height
        << std::endl;
    std::cerr << "Coords: " << labelPos.x << " " << labelPos.y << std::endl;

    m_buttonBackground.setSize(sf::Vector2f(textRect.width, textRect.height));
    m_buttonBackground.setPosition(
        sf::Vector2f(labelPos.x + textRect.left,
                     labelPos.y + textRect.top)
    );
    return *this;
}

} // namespace Widget
