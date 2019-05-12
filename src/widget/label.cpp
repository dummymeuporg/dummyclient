#include "widget/label.hpp"

namespace Widget {

Label::Label(std::shared_ptr<Widget> parent,
               ::ResourceProvider& resourceProvider)
    : Widget(parent, resourceProvider) {}

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
    m_caption.setPosition(x, y);
    return *this;
}

void Label::paint(sf::RenderWindow& window) {
    window.draw(m_caption);
}

bool Label::handleEvent(const sf::Event& event) {
    return true;
}

} // namespace Widget
