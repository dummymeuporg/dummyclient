#pragma once

#include "widget/label.hpp"

namespace Widget {

class Button : public Label {
public:
    Button(std::shared_ptr<Widget>, ::ResourceProvider&);
    virtual void paint(sf::RenderWindow&) override;
    virtual void handleEvent(const sf::Event& event) override;
    Button& setBackgroundColor(const sf::Color&);
    Button& setBorderColor(const sf::Color&);
	Button& setCaption(const std::string&);
private:
    sf::RectangleShape m_buttonBackground;
};

};
