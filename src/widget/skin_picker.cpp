#include <iostream>
#include "widget/skin_picker.hpp"

namespace Widget {

SkinPicker::SkinPicker(std::vector<std::string> skinList,
                       std::shared_ptr<Widget> parent)
    : Widget(parent), m_leftBrowser(30, 3),
      m_rightBrowser(30, 3),
      m_hoveredBrowser(nullptr),
      m_skinList(std::move(skinList))
{
    m_leftBrowser.rotate(-90);
    m_leftBrowser.setFillColor(sf::Color::Green);
    m_rightBrowser.rotate(90);
    m_rightBrowser.setFillColor(sf::Color::Green);
}

SkinPicker& SkinPicker::setPos(int x, int y) {
    m_origin.x = x;
    m_origin.y = y;
    m_leftBrowser.setPosition(sf::Vector2f(m_origin.x, m_origin.y + 100));
    m_rightBrowser.setPosition(sf::Vector2f(m_origin.x + 235,
                                           m_origin.y + 40));
    return *this;
}

void SkinPicker::paint(sf::RenderWindow& window) {
    // draw the left rectangle
    window.draw(m_leftBrowser);

    // draw the sprite
    m_sprite.setTexture(texture(m_skinList[0]));
    m_sprite.setScale(4, 4);
    m_sprite.setTextureRect(sf::IntRect(24, 32 * 2, 24, 32));
    m_sprite.setPosition(sf::Vector2f(m_origin.x + 70, m_origin.y));
    window.draw(m_sprite);

    window.draw(m_rightBrowser);

}

bool SkinPicker::handleEvent(const sf::Event& event) {
    bool forwardEvent = true;
    switch(event.type)
    {
    case sf::Event::MouseButtonPressed:
        forwardEvent = _onMouseButtonPressed(event);
        break;
    case sf::Event::MouseMoved:
        forwardEvent = _onMouseMoved(event);
        break;
    default:
        break;
    }
    return forwardEvent;
}

bool SkinPicker::_isHovered(const sf::Event& event,
                            const sf::Shape& shape,
                            const sf::Vector2f&& origin)
{
    const sf::FloatRect& rect(shape.getLocalBounds());

    return event.mouseMove.x >= origin.x && event.mouseMove.y >= origin.y
        && event.mouseMove.x <= (origin.x + rect.width)
        && event.mouseMove.y <= (origin.y + rect.height);
}

bool SkinPicker::_onMouseMoved(const sf::Event& event) {
    bool forwardEvent = true;
    if (_isHovered(event, m_leftBrowser,
                   sf::Vector2f(m_origin.x, m_origin.y + 100))) {
        m_hoveredBrowser = &m_leftBrowser;
        forwardEvent = false;
        std::cerr << "Hovered left" << std::endl;
    } else if(_isHovered(event, m_rightBrowser,
                         sf::Vector2f(m_origin.x + 235, m_origin.y + 40))) {
        m_hoveredBrowser = &m_rightBrowser;
        forwardEvent = false;
        std::cerr << "hovered right" << std::endl;
    } else {
        m_hoveredBrowser = nullptr;
    }
    return forwardEvent;
}

bool SkinPicker::_onMouseButtonPressed(const sf::Event& event)
{
    bool forwardEvent = true;

    // Check the left browser
    if(event.mouseButton.button == sf::Mouse::Left)
    {

    }
    
    return forwardEvent;
}

} // namespace Widget
