#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class SkinPreviewer : public Abstract::Widget {
public:
    SkinPreviewer(std::vector<std::string> = {},
                  std::shared_ptr<Widget> = nullptr);
    virtual void paint(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;
    void showNextSkin();
    void showPreviousSkin();
    SkinPreviewer& setPos(int, int);
private:
    int m_currentSkinIndex;
    sf::Vector2f m_origin;
    sf::RectangleShape m_background;
    sf::Sprite m_sprite;
    std::vector<std::string> m_skinList;
};

} // namespace Widget
