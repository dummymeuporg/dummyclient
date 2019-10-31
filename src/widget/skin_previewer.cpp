#include <iostream>
#include "widget/skin_previewer.hpp"

namespace Widget {

SkinPreviewer::SkinPreviewer(Visual& parent,
                             std::vector<std::string> skinList)
    : Widget(parent),
      m_currentSkinIndex(0),
      m_skinList(std::move(skinList))
{
}

SkinPreviewer& SkinPreviewer::setPos(int x, int y) {
    m_origin.x = x;
    m_origin.y = y;
    return *this;
}

void SkinPreviewer::draw(sf::RenderWindow& window) {
    // draw the sprite
    if (m_currentSkinIndex >= 0 && m_currentSkinIndex < m_skinList.size())
    {
        window.draw(m_sprite);
    }
}

bool SkinPreviewer::handleEvent(const sf::Event& event) {
    bool forwardEvent = true;
    return forwardEvent;
}

void SkinPreviewer::showNextSkin() {
    if (++m_currentSkinIndex == m_skinList.size()) {
        m_currentSkinIndex = 0;
    }
    _updateSprite();
}

void SkinPreviewer::showPreviousSkin() {
    if (--m_currentSkinIndex < 0) {
        m_currentSkinIndex = m_skinList.size() - 1;
    }
    _updateSprite();
}

SkinPreviewer& SkinPreviewer::setSkinList(std::vector<std::string>&& skinList)
{
    if (skinList.size() > 0)
    {
        m_currentSkinIndex = 0;
        m_skinList = std::move(skinList);
        _updateSprite();
    }
    return *this;
}

void SkinPreviewer::_updateSprite() {
    m_sprite.setTexture(texture(m_skinList[m_currentSkinIndex]));
    m_sprite.setScale(4, 4);
    m_sprite.setTextureRect(sf::IntRect(24, 32 * 2, 24, 32));
    m_sprite.setPosition(sf::Vector2f(m_origin.x, m_origin.y));
}

sf::IntRect SkinPreviewer::boundingRect() const {
    return sf::IntRect(m_x, m_y, 0, 0);
}

} // namespace Widget
