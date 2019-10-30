#include "widget/label.hpp"

namespace Widget {

Label::Label(Visual& parent)
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

void Label::setPos(std::uint16_t x, std::uint16_t y) {
    Widget::setPos(x, y);
    m_caption.setPosition(m_x, m_y);
}

void Label::draw(sf::RenderWindow& window) {
    window.draw(m_caption);
}

bool Label::handleEvent(const sf::Event& event) {
    return true;
}

Label& Label::setOrigin(float x, float y) {
    m_caption.setOrigin(x, y);
    return *this;
}

sf::IntRect Label::boundingRect() {
    auto bounds(m_caption.getLocalBounds());
    return sf::IntRect(
        m_x,
        m_y,
        static_cast<int>(bounds.width),
        static_cast<int>(bounds.height)
    );
}

} // namespace Widget
