#include "widget/modal_message.hpp"

namespace Widget {

ModalMessage::ModalMessage(std::shared_ptr<Widget> parent)
    : Abstract::Widget(parent),
      m_message(std::make_shared<Label>())
{
    m_backgroundRectangle.setSize(sf::Vector2f(500, 100));
    m_backgroundRectangle.setFillColor(sf::Color(183, 109, 44));
    m_backgroundRectangle.setOutlineColor(sf::Color(94, 47, 6));
    m_backgroundRectangle.setOutlineThickness(10);
    const auto& textRect(m_backgroundRectangle.getLocalBounds());
    m_backgroundRectangle.setOrigin(
        textRect.left + (textRect.width/2.0),
        textRect.top + (textRect.height/2.0)
    );
}

void ModalMessage::paint(sf::RenderWindow& window) {
    // XXX: draw a centered rectangle.
    const auto& windowSize(window.getSize());

    m_backgroundRectangle.setPosition(windowSize.x/2, windowSize.y/2);

    const auto& textRect(m_backgroundRectangle.getLocalBounds());
    const auto& messageRect(m_message->getLocalBounds());

    window.draw(m_backgroundRectangle);

    // draw the label
    m_message->setOrigin(
        messageRect.left + (messageRect.width / 2),
        messageRect.top
    );

    // - 30 so the message gets a bit on the top of the rectangle.
    m_message->setPos((windowSize.x/2), windowSize.y/2 - 30);


    m_message->paint(window);

    // Draw the buttons.
    const auto& rectanglePos(m_backgroundRectangle.getPosition());
    for (auto& button: m_buttons) {
        button->paint(window);
    }
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
