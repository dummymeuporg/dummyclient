#pragma once

#include "widget/label.hpp"

namespace Widget {

class Button : public Label {
public:
    Button(Visual&);
    virtual void draw(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;
    Button& setBackgroundColor(const sf::Color&);
    Button& setBorderColor(const sf::Color&);
	Button& setCaption(const std::string&);
    Button& setIsClickable(bool);
    Button& setOrigin(float, float);
    virtual void setPos(int x, int y);
    bool isClickable() const {
        return m_isClickable;
    }
    sf::FloatRect getLocalBounds() const {
        return m_buttonBackground.getLocalBounds();
    }
private:
    bool _onMouseMoved(const sf::Event&);
    bool _onMouseButtonPressed(const sf::Event&);
    bool _onMouseButtonReleased(const sf::Event&);
    void adjustRectangle();
    sf::RectangleShape m_buttonBackground;
    bool m_isHovered;
    bool m_isPushed;
    bool m_isClickable;
};

};
