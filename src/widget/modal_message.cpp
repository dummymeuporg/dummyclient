#include "widget/modal_message.hpp"

namespace Widget {

ModalMessage::ModalMessage(Visual& parent, const std::string& message)
    : Abstract::Widget(parent),
      m_message(std::make_shared<Label>(*this))
{
    setSize(500, 100);
    // XXX: find a way to get those dimensions dinamically.
    setPos(960/2, 720/2);
    m_backgroundRectangle.setFillColor(sf::Color(183, 109, 44));
    m_backgroundRectangle.setOutlineColor(sf::Color(94, 47, 6));
    m_backgroundRectangle.setOutlineThickness(10);
    const auto& rect(m_backgroundRectangle.getLocalBounds());
    m_backgroundRectangle.setOrigin(
        rect.left + (rect.width/2.0),
        rect.top + (rect.height/2.0)
    );

    // XXX: same as above.
    m_message->setFont("arial.ttf");
    m_message->setCaption(message);
    m_message->setFontSize(18);
    m_message->setColor(sf::Color::Black);
    m_message->setPos(0, 20);
    const auto& messageRect(m_message->getLocalBounds());
    const auto& rectOrigin(m_backgroundRectangle.getOrigin());
    m_message->setOrigin(
        (messageRect.left + messageRect.width/2.0),
        rectOrigin.y + messageRect.top
    );


}

void ModalMessage::setSize(std::uint16_t width, std::uint16_t height) {
    Widget::setSize(width, height);
    m_backgroundRectangle.setSize(sf::Vector2f(width, height));
}

void ModalMessage::setPos(std::uint16_t x, std::uint16_t y) {
    Widget::setPos(x, y);
    m_backgroundRectangle.setPosition(m_x, m_y);
}

void ModalMessage::draw(sf::RenderWindow& window) {
    // XXX: draw a centered rectangle.
    window.draw(m_backgroundRectangle);

    // Draw the label and the buttons.
    Widget::draw(window);

}

void ModalMessage::setMessage(const std::string& message) {
    m_message->setCaption(message);
}

void ModalMessage::addButton(std::shared_ptr<Button> button) {
    m_buttons.push_back(button);
}

sf::IntRect ModalMessage::boundingRect() const {
    const auto& origin(m_backgroundRectangle.getOrigin());

    return sf::IntRect(
        m_x - origin.x,
        m_y - origin.y,
        static_cast<int>(m_backgroundRectangle.getSize().x),
        static_cast<int>(m_backgroundRectangle.getSize().y)
    );
}

} // namespace Widget
