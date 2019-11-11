#include "widget/game/message.hpp"

namespace Widget {

namespace Game {

Message::Message(Visual& parent) : Widget(parent) {
    setEnabled(false);
    m_rectangle.setFillColor(sf::Color(183, 109, 44));
    m_rectangle.setOutlineColor(sf::Color(94, 47, 6));
    m_rectangle.setOutlineThickness(2);
}


void Message::draw(sf::RenderWindow& window) {
    sf::Text messageText;
    messageText.setFont(font("arial.ttf"));
    messageText.setFillColor(sf::Color(0, 0, 0));
    messageText.setCharacterSize(24);
    messageText.setString(m_message);
    messageText.setPosition(m_x + 10, m_y + 10);
    window.draw(messageText);
    window.draw(m_rectangle);
}

bool Message::handleCustomEvent(const ::CustomEvent& customEvent) {
    return true;
}

void Message::setSize(std::uint16_t width, std::uint16_t height) {
    m_width = width;
    m_height = height;

    m_rectangle.setSize(sf::Vector2f(m_width, m_height));
}

void Message::setContent(const std::string& message) {
    m_message = sf::String::fromUtf8(message.begin(), message.end());
}

sf::IntRect Message::boundingRect() const {
    return sf::IntRect(m_x, m_y, m_width, m_height);
}


} // namespace Game


} // namespace Widget
