#include "widget/skin_picker.hpp"

namespace Widget {

SkinPicker::SkinPicker(std::vector<std::string> skinList,
                       std::shared_ptr<Widget> parent)
    : Widget(parent), m_skinList(std::move(skinList))
{
}

SkinPicker& SkinPicker::setPos(int x, int y) {
    m_origin.x = x;
    m_origin.y = y;
    return *this;
}

void SkinPicker::paint(sf::RenderWindow& window) {
    sf::Sprite sprite;
    sprite.setTexture(texture(m_skinList[0]));
    sprite.setScale(4, 4);
    sprite.setTextureRect(sf::IntRect(24, 32 * 2, 24, 32));
    sprite.setPosition(sf::Vector2f(m_origin.x, m_origin.y));
    window.draw(sprite);
}

bool SkinPicker::handleEvent(const sf::Event& event) {
    return true;
}

} // namespace Widget
