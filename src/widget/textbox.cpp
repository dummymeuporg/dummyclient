#include "widget/textbox.hpp"

namespace Widget {

Textbox::Textbox(std::shared_ptr<Widget> parent) : Widget(parent)
{

}

void Textbox::paint(sf::RenderWindow& renderWindow) {
    renderWindow.draw(m_shape);
    const sf::Vector2f& shapePos(m_shape.getPosition());
    m_text.setPosition(shapePos.x + 5, shapePos.y + 5);
    renderWindow.draw(m_text);
}

bool Textbox::handleEvent(const sf::Event& event) {
    return true;
}

Textbox& Textbox::setRect(int x, int y, int width, int height) {
    m_shape.setPosition(x, y);
    m_shape.setSize(sf::Vector2f(width, height));
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
    m_shape.setFillColor(color);
    return *this;
}

Textbox& Textbox::setBorderColor(const sf::Color& color) {
    m_shape.setOutlineThickness(5);
    m_shape.setOutlineColor(color);
    return *this;
}

Textbox& Textbox::setContent(const std::string& str)
{
    m_content.flush();
    m_content << str;
    m_text.setString(m_content.str());
    return *this;
}

} // namespace Widget
