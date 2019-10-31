#include <iostream>
#include "widget/button.hpp"

namespace Widget {

Button::Button(Visual& parent)
    : Label(parent),
      m_isHovered(false),
      m_isPushed(false),
      m_isClickable(true)
{    
}

void Button::draw(sf::RenderWindow& window) {
    // First paint the background, then the label
    window.draw(m_buttonBackground);
    Label::draw(window);
}

void Button::handleCustomEvent(const ::CustomEvent& event) {
    sf::Color bgColor = m_buttonBackground.getFillColor();
    switch(event.type()) {
    case CustomEvent::Type::MouseEntered:
        std::cerr << "Mouse entered!" << std::endl;
        setBackgroundColor(
            sf::Color(
                bgColor.r + 30,
                bgColor.g + 30,
                bgColor.b + 30
            )
        );
        break;
    case CustomEvent::Type::MouseLeft:
        std::cerr << "Mouse left!" << std::endl;
        setBackgroundColor(
            sf::Color(
                bgColor.r - 30,
                bgColor.g - 30,
                bgColor.b - 30
            )
        );
        break;
    case CustomEvent::Type::LeftClick:
        std::cerr << "Mouse click!" << std::endl;
        setBackgroundColor(
            sf::Color(
                bgColor.r + 10,
                bgColor.g + 10,
                bgColor.b + 10
            )
        );
        break;
    default:
        break;
    }
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
    adjustRectangle();
    return *this;
}

Button& Button::setIsClickable(bool clickable) {
    m_isClickable = clickable;
    return *this;
}

void Button::setPos(int x, int y) {
    Label::setPos(x, y);
    adjustRectangle();
}

void Button::adjustRectangle() {
    sf::FloatRect textRect = m_caption.getLocalBounds();
    textRect.left -= 10;
    textRect.top -= 10;
    textRect.width += 20;
    textRect.height += 20;

    sf::Vector2f labelPos = m_caption.getPosition();

    m_buttonBackground.setSize(sf::Vector2f(textRect.width, textRect.height));
    m_buttonBackground.setPosition(
        sf::Vector2f(labelPos.x + textRect.left,
                     labelPos.y + textRect.top)
    );
}

Button& Button::setOrigin(float x, float y) {
    Label::setOrigin(x, y);
    m_buttonBackground.setOrigin(x, y);
    return *this;
}

sf::IntRect Button::boundingRect() const {
    const auto& bounds(m_caption.getLocalBounds());
    return sf::IntRect(
        m_x - 10,
        m_y - 10,
        static_cast<int>(bounds.width) + 20,
        static_cast<int>(bounds.height) + 20
    );
}


} // namespace Widget
