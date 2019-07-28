#pragma once
#include <sstream>

#include "widget/abstract/widget.hpp"

namespace Widget {

class Textbox : public Abstract::Widget {
public:
    Textbox(std::shared_ptr<Widget> = nullptr);
    virtual void paint(sf::RenderWindow&) override;
    virtual bool handleEvent(const sf::Event& event) override;
    virtual void handleCustomEvent(const ::CustomEvent& event) override;
    Textbox& setRect(int, int, int, int);
    Textbox& setFontSize(int);
    Textbox& setFont(const std::string& fontName);
    Textbox& setColor(const sf::Color& color);
    Textbox& setBackgroundColor(const sf::Color& color);
    Textbox& setBorderColor(const sf::Color& color);
    Textbox& setMaxLength(int);
    Textbox& setContent(const std::string& str);
    Textbox& setBorderThickness(float);
    const std::string& content() const {
        return m_content;
    }
private:

    /* Private methods */
    bool _onKeyPressed(const sf::Event&);
    bool _onKeyReleased(const sf::Event&);
    bool _onTextEntered(const sf::Event&);
    bool _onMouseMoved(const sf::Event&);
    bool _onMouseButtonPressed(const sf::Event&);
    void _handleTextEntered(const sf::Event&);

    /* Private attributes. */
    int m_maxLength; /* For text. */
    sf::RectangleShape m_shape;
    sf::Text m_text; // What the user will see.
    //std::stringstream m_content;
    std::string m_content;
    bool m_isHovered;
    bool m_isFocused;
    bool m_isTextRepeating;
    sf::Color m_backgroundColor;
    sf::Clock m_carretClock;
    sf::Clock m_textFirstClock;
    sf::Clock m_textRepeatClock;
    bool m_isCarretDrawn;
    unsigned int m_carretIndex;
    sf::Keyboard::Key m_lastKeyInput;
    sf::Keyboard::Key m_lastTextInput;
};

} // namespace Widget
