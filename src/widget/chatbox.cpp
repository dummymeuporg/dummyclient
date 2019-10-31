#include <iostream>

#include "widget/chatbox.hpp"
#include "widget/textbox.hpp"

namespace fs = std::filesystem;

namespace Widget {

Chatbox::Chatbox(Visual& parent)
    : Widget(parent),
      m_isTypingMessage(false),
      m_messageInputTextbox(std::make_shared<Textbox>(*this))
{
    setPos(0, 720 - 30);
    m_width = 300;
    m_height = 30;
    m_messageInputTextbox
        ->setFontSize(18)
        .setColor(sf::Color::Black)
        .setBackgroundColor(sf::Color(184, 130, 101, 200))
        .setBorderThickness(1)
        .setBorderColor(sf::Color(103, 64, 38))
        .setRect(m_x, m_y, m_width, m_height)
        .setContent("")
        .setMaxLength(35)
        .setFont("arial.ttf");

}

void Chatbox::draw(sf::RenderWindow& window) {
    m_messageInputTextbox->draw(window);
}

bool Chatbox::handleEvent(const sf::Event& event) {
    bool forwardEvent(true);
    if (m_isTypingMessage) {
        forwardEvent = m_messageInputTextbox->handleEvent(event);
    }
    return forwardEvent;
}

void Chatbox::handleCustomEvent(const ::CustomEvent& event) {

    switch(event.type()) {
    case CustomEvent::Type::EnterKeyPressed:
        std::cerr << "[CHATBOX] Enter Key Pressed!" << std::endl;
        if (!m_isTypingMessage) {
            // XXX: Ugly (for now): simulate a SetFocus to the textbox.
            m_messageInputTextbox->handleCustomEvent(
                ::CustomEvent(this, CustomEvent::Type::SetFocus, this)
            );
            m_isTypingMessage = true;
        } else {
            m_messageInputTextbox->handleCustomEvent(
                ::CustomEvent(this, CustomEvent::Type::ReleaseFocus, this)
            );
            m_isTypingMessage = false;
        }
        break;
    default:
        break;
    }
}

const std::string& Chatbox::typedMessage() const {
    return m_messageInputTextbox->content();
}

void Chatbox::clearMessageInputTextbox() {
    m_messageInputTextbox->setContent("");
}

sf::IntRect Chatbox::boundingRect() const {
    return sf::IntRect(
        m_x,
        m_y,
        m_width,
        m_height
    );
}

} // namespace Widget
