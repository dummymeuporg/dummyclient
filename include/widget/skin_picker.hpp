#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class SkinPicker : public Abstract::Widget {
public:
    SkinPicker(std::vector<std::string> = {},
               std::shared_ptr<Widget> = nullptr);
    virtual void paint(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;
    SkinPicker& setPos(int, int);
private:
    sf::Vector2f m_origin;
    sf::RectangleShape m_background;
    sf::CircleShape m_leftBrowser, m_rightBrowser;
    std::vector<std::string> m_skinList;
};

} // namespace Widget
