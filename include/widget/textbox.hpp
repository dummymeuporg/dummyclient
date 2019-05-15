#pragma once
#include <sstream>

#include "widget/abstract/widget.hpp"

namespace Widget {

class Textbox : public Abstract::Widget {
public:
    Textbox(std::shared_ptr<Widget>);
    virtual void paint(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;
    Textbox& setRect(int, int, int, int);
    Textbox& setFontSize(int);
    Textbox& setFont(const std::string& fontName);
    Textbox& setColor(const sf::Color& color);
    Textbox& setBackgroundColor(const sf::Color& color);
    Textbox& setBorderColor(const sf::Color& color);
    Textbox& setContent(const std::string& str);
    std::string content() const {
        return m_content.str();
    }
private:
    sf::RectangleShape m_shape;
    sf::Text m_text; // What the user will see.
    std::stringstream m_content;
};

} // namespace Widget
