#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class Label : public Abstract::Widget {
public:
    Label(std::shared_ptr<Widget>, ::ResourceProvider&, ::CustomEventQueue&);
    virtual void paint(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;

    const sf::Text& caption() const {
        return m_caption;
    }

    sf::Text& caption() {
        return m_caption;
    }

    Label& setCaption(const std::string&);
    Label& setFontSize(int);
    Label& setColor(const sf::Color&);
    Label& setStyle(int);
    Label& setFont(const std::string&);
    Label& setPos(int, int);
protected:
    /*
    std::string m_caption;
    int m_fontSize;
    sf::Color m_color;
    std::uint32_t style;
    std::string m_font;
*/

    sf::Text m_caption;
};

};
