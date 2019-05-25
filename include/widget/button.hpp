#pragma once

#include "widget/label.hpp"

namespace Widget {

class Button : public Label {
public:
    Button(std::shared_ptr<Widget> = nullptr);
    virtual void paint(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;
    Button& setBackgroundColor(const sf::Color&);
    Button& setBorderColor(const sf::Color&);
	Button& setCaption(const std::string&);
    Button& setEnabled(bool enabled);
    bool enabled() const {
        return m_isEnabled;
    }
private:
    bool _onMouseMoved(const sf::Event&);
    bool _onMouseButtonPressed(const sf::Event&);
    bool _onMouseButtonReleased(const sf::Event&);
    sf::RectangleShape m_buttonBackground;
    bool m_isHovered;
    bool m_isPushed;
    bool m_isEnabled;
};

};
