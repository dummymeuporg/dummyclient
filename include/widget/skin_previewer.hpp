#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class SkinPreviewer : public Abstract::Widget {
public:
    SkinPreviewer(Visual&, std::vector<std::string> = {});
    virtual void draw(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;
    sf::IntRect boundingRect() const override;
    void showNextSkin();
    void showPreviousSkin();
    SkinPreviewer& setPos(int, int);
    SkinPreviewer& setSkinList(std::vector<std::string>&&);
    const std::string& skin() const {
        return m_skinList[m_currentSkinIndex];
    }
    void _updateSprite();
private:
    int m_currentSkinIndex;
    sf::Vector2f m_origin;
    sf::RectangleShape m_background;
    sf::Sprite m_sprite;
    std::vector<std::string> m_skinList;
};

} // namespace Widget
