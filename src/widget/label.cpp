#include "widget/label.hpp"

namespace Widget {

Label::Label(std::shared_ptr<Widget> parent)
    : Widget(parent) {}

Label& Label::setCaption(const std::string& caption) {
    m_caption.setString(caption);
    return *this;
}

Label& Label::setFontSize(int fontSize) {
    m_caption.setCharacterSize(fontSize);
    return *this;
}

Label& Label::setColor(const sf::Color& color) {
    m_caption.setColor(color);
    return *this;
}

Label& Label::setStyle(int style) {
    m_caption.setStyle(style);
    return *this;
}

Label& Label::setFont(const std::string& fontName) {
    m_caption.setFont(font(fontName));
    return *this;
}

Label& Label::setPos(int x, int y) {
    Widget::setPos(x, y);
    m_caption.setPosition(x, y);
    return *this;
}

void Label::paint(sf::RenderWindow& window) {
    window.draw(m_caption);
}

bool Label::handleEvent(const sf::Event& event) {
    return true;
}

Label& Label::setOrigin(float x, float y) {
    m_caption.setOrigin(x, y);
    return *this;
}

} // namespace Widget
