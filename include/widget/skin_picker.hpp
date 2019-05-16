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
    bool _isHovered(const sf::Event&, const sf::Shape&, const sf::Vector2f&&);
    bool _onMouseButtonPressed(const sf::Event&);
    bool _onMouseMoved(const sf::Event&);

    sf::Vector2f m_origin;
    sf::RectangleShape m_background;
    sf::Sprite m_sprite;
    sf::CircleShape m_leftBrowser, m_rightBrowser;
    const sf::Shape* m_hoveredBrowser;
    std::vector<std::string> m_skinList;
};

} // namespace Widget
