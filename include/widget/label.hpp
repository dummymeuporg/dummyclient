#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class Label : public Abstract::Widget {
public:
    Label(Visual&);
    virtual void draw(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;

    const sf::Text& caption() const {
        return m_caption;
    }

    sf::Text& caption() {
        return m_caption;
    }

    sf::FloatRect getLocalBounds() const {
        return m_caption.getLocalBounds();
    }

    Label& setCaption(const std::string&);
    Label& setFontSize(int);
    Label& setColor(const sf::Color&);
    Label& setStyle(int);
    Label& setFont(const std::string&);
    void setPos(std::uint16_t, std::uint16_t) override;
    Label& setOrigin(float, float);
protected:
    sf::Text m_caption;
};

};
