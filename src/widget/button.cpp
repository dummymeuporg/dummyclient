#include <iostream>
#include "widget/button.hpp"

namespace Widget {

Button::Button(std::shared_ptr<Widget> parent,
               ::ResourceProvider& resourceProvider)
    : Label(parent, resourceProvider)
{    
}

void Button::paint(sf::RenderWindow& window) {
    // First paint the background, then the label
    window.draw(m_buttonBackground);
    Label::paint(window);
}

void Button::handleEvent(const sf::Event& event) {

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
