#include "widget/modal_message.hpp"

namespace Widget {

ModalMessage::ModalMessage(Visual& parent)
    : Abstract::Widget(parent),
      m_message(std::make_shared<Label>(*this))
{
    setSize(500, 100);
    m_backgroundRectangle.setFillColor(sf::Color(183, 109, 44));
    m_backgroundRectangle.setOutlineColor(sf::Color(94, 47, 6));
    m_backgroundRectangle.setOutlineThickness(10);
    const auto& textRect(m_backgroundRectangle.getLocalBounds());
    m_backgroundRectangle.setOrigin(
        textRect.left + (textRect.width/2.0),
        textRect.top + (textRect.height/2.0)
    );
}

void ModalMessage::setSize(std::uint16_t width, std::uint16_t height) {
    Widget::setSize(width, height);
    m_backgroundRectangle.setSize(sf::Vector2f(width, height));
}

void ModalMessage::onDraw(sf::RenderWindow& window) {
    // XXX: draw a centered rectangle.
    const auto& windowSize(window.getSize());

    m_backgroundRectangle.setPosition(windowSize.x/2, windowSize.y/2);

    const auto& textRect(m_backgroundRectangle.getLocalBounds());
    const auto& messageRect(m_message->getLocalBounds());

    window.draw(m_backgroundRectangle);

}

bool ModalMessage::handleEvent(const sf::Event &event) {
    return true;
}

void ModalMessage::setMessage(const std::string& message) {
    m_message->setCaption(message);
}

void ModalMessage::addButton(std::shared_ptr<Button> button) {
    m_buttons.push_back(button);
}

} // namespace Widget
