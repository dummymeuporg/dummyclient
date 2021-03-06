#include <cctype>
#include <iostream>
#include "widget/textbox.hpp"

namespace Widget {

Textbox::Textbox(Visual& parent)
    : Widget(parent),
      m_maxLength(-1),
      m_isTextRepeating(false),
      m_isCarretDrawn(false), m_carretIndex(0)
{
    // XXX: default
    m_shape.setOutlineThickness(5);
}

void Textbox::draw(sf::RenderWindow& renderWindow) {
    int delta = 30;
    m_renderTexture.clear(sf::Color::Transparent);
    sf::Color backgroundColor(m_shape.getFillColor());
    if (m_isFocused) {
        backgroundColor.r = m_backgroundColor.r + delta;
        backgroundColor.g = m_backgroundColor.g + delta;
        backgroundColor.b = m_backgroundColor.b + delta;
        
        if (m_carretClock.getElapsedTime().asMilliseconds() >= 500) {
            m_isCarretDrawn = !m_isCarretDrawn;
            m_carretClock.restart();
        }

    } else {
        backgroundColor.r = m_backgroundColor.r - delta;
        backgroundColor.g = m_backgroundColor.g - delta;
        backgroundColor.b = m_backgroundColor.b - delta;
        m_isCarretDrawn = false;
    }

    m_shape.setFillColor(backgroundColor);

    renderWindow.draw(m_shape);
    //m_renderTexture.draw(m_shape);
    m_text.setPosition(5, 5);
    //renderWindow.draw(m_text);
    m_renderTexture.draw(m_text);

    if (m_isCarretDrawn) {
        const sf::Vector2f& textPosition(
            m_text.findCharacterPos(m_carretIndex));
        sf::RectangleShape carret;
        carret.setPosition(textPosition.x, textPosition.y);
        carret.setSize(sf::Vector2f(2, 24));
        carret.setFillColor(sf::Color(0, 0, 0));
        //renderWindow.draw(carret);
        m_renderTexture.draw(carret);
    }

    m_renderTexture.display();
    m_sprite.setTexture(m_renderTexture.getTexture());
    renderWindow.draw(m_sprite);
}

void Textbox::_handleTextEntered(const sf::Event& event) {
    if (event.key.code == '\010'/* Backspace */) {
        if (m_carretIndex > 0) {
            m_content = m_content.substr(0, m_carretIndex-1)
                + m_content.substr(m_carretIndex);
            m_text.setString(m_content);
            --m_carretIndex;
        }
    } else if (event.text.unicode >= 0x20) {
        std::cerr << "Entered: " << event.text.unicode << std::endl;
        if (m_maxLength > 0 && m_content.size() == m_maxLength) {
            return;
        }
        m_content.insert(m_carretIndex, 1, static_cast<wchar_t>(event.text.unicode));
        std::cerr << "Content = " << m_content << std::endl;
        m_text.setString(m_content);
        m_carretIndex++;
        m_carretClock.restart();
        m_isCarretDrawn = true;
    }
}

bool Textbox::_onTextEntered(const sf::Event& event) {
    bool forwardEvent = true;
    std::cerr << "Text entered: " << event.text.unicode << std::endl;
    if (m_isTextRepeating
         && m_textRepeatClock.getElapsedTime().asMilliseconds() >= 30) {
        _handleTextEntered(event);
        m_textRepeatClock.restart();
    } else if (m_lastTextInput != event.text.unicode) {
        _handleTextEntered(event);
        m_textFirstClock.restart();
    } else if (!m_isTextRepeating
               && m_textFirstClock.getElapsedTime().asMilliseconds() >= 300) {
        m_isTextRepeating = true;
        _handleTextEntered(event);
        m_textRepeatClock.restart();
    }
        
    m_lastTextInput = event.text.unicode;
    return forwardEvent;
}

bool Textbox::_onKeyReleased(const sf::Event& event) {
    bool forwardEvent = true;
    if(m_lastKeyInput == sf::Keyboard::Left) {
        if (m_carretIndex > 0) {
            --m_carretIndex;
        }
        forwardEvent = false;
        m_carretClock.restart();
        m_isCarretDrawn = true;
    } else if (m_lastKeyInput == sf::Keyboard::Right) {
        if (m_carretIndex < m_content.size()) {
            ++m_carretIndex;
        }
        forwardEvent = false;
        m_carretClock.restart();
        m_isCarretDrawn = true;
    } 
    m_lastKeyInput = sf::Keyboard::Unknown;
    m_lastTextInput = sf::Keyboard::Unknown;
    m_isTextRepeating = false;
    m_textFirstClock.restart();
    m_textRepeatClock.restart();
    return forwardEvent;
}

bool Textbox::_onKeyPressed(const sf::Event& event) {
    bool forwardEvent = true;
    m_lastKeyInput = event.key.code;
    return forwardEvent;
}


bool Textbox::handleEvent(const sf::Event& event) {
    bool forwardEvent = Widget::handleEvent(event);
    if (!forwardEvent) {
        return forwardEvent;
    }
    switch(event.type) {
    case sf::Event::TextEntered:
        if (m_isFocused) {
            forwardEvent = _onTextEntered(event);
        }
        break;
    case sf::Event::KeyPressed:
        if (m_isFocused) {
            forwardEvent = _onKeyPressed(event);
        }
        break;
    case sf::Event::KeyReleased:
        if (m_isFocused) {
            forwardEvent = _onKeyReleased(event);
        }
        break;
    default:
        break;
    }
    return forwardEvent;
}

Textbox& Textbox::setRect(int x, int y, int width, int height) {
    Widget::setPos(x, y);
    Widget::setSize(width, height);
    m_renderTexture.create(width, height, true);
    m_shape.setPosition(x, y);
    m_shape.setSize(sf::Vector2f(width, height));
    m_sprite.setPosition(x, y);
    return *this;
}

Textbox& Textbox::setFontSize(int fontSize) {
    m_text.setCharacterSize(fontSize);
    return *this;
}

Textbox& Textbox::setFont(const std::string& fontName) {
    m_text.setFont(font(fontName));
    return *this;
}

Textbox& Textbox::setColor(const sf::Color& color) {
    m_text.setColor(color);
    return *this;
}

Textbox& Textbox::setBackgroundColor(const sf::Color& color) {
    m_backgroundColor = color;
    m_shape.setFillColor(m_backgroundColor);
    return *this;
}

Textbox& Textbox::setBorderColor(const sf::Color& color) {

    m_shape.setOutlineColor(color);
    return *this;
}

Textbox& Textbox::setBorderThickness(float thickness) {
    m_shape.setOutlineThickness(thickness);
    return *this;
}

Textbox& Textbox::setContent(const std::string& str)
{
    m_content = str;
    m_text.setString(m_content);
    m_carretIndex = 0;
    return *this;
}

Textbox& Textbox::setMaxLength(int maxLength) {
    m_maxLength = maxLength;
    return *this;
}

sf::IntRect Textbox::boundingRect() const {
    return sf::IntRect(
        m_x,
        m_y,
        static_cast<int>(m_shape.getSize().x),
        static_cast<int>(m_shape.getSize().y)
    );
}

} // namespace Widget
