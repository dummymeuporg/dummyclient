#include <iostream>

#include "widget/chatbox.hpp"
#include "widget/textbox.hpp"

namespace fs = std::filesystem;

namespace Widget {

Chatbox::Chatbox(std::shared_ptr<Widget> parent)
    : m_messageInputTextbox(std::make_shared<Textbox>()),
      m_isTypingMessage(false)
{
    m_messageInputTextbox
        ->setFontSize(18)
        .setColor(sf::Color::Black)
        .setBackgroundColor(sf::Color(184, 130, 101, 200))
        .setBorderThickness(1)
        .setBorderColor(sf::Color(103, 64, 38))
        .setRect(0, 720 - 30, 300, 30)
        .setContent("")
        .setMaxLength(35)
        .setFont("arial.ttf");
}

void Chatbox::paint(sf::RenderWindow& window) {
    m_messageInputTextbox->paint(window);
}

bool Chatbox::handleEvent(const sf::Event& event) {
    bool forwardEvent(true);
    if (m_isTypingMessage) {
        forwardEvent = m_messageInputTextbox->handleEvent(event);
    }
    return false;
}

void Chatbox::handleCustomEvent(const ::CustomEvent& event) {

    switch(event.type()) {
    case CustomEvent::Type::EnterKeyPressed:
        std::cerr << "[CHATBOX] Enter Key Pressed!" << std::endl;
        if (!m_isTypingMessage) {
            // XXX: Ugly (for now): simulate a SetFocus to the textbox.
            m_messageInputTextbox->handleCustomEvent(
                ::CustomEvent(
                    reinterpret_cast<void*>(shared_from_this().get()),
                    CustomEvent::Type::SetFocus,
                    reinterpret_cast<void*>(m_messageInputTextbox.get())
                )
            );
            m_isTypingMessage = true;
        } else {
            m_messageInputTextbox->handleCustomEvent(
                ::CustomEvent(
                    reinterpret_cast<void*>(shared_from_this().get()),
                    CustomEvent::Type::ReleaseFocus,
                    reinterpret_cast<void*>(m_messageInputTextbox.get())
                )
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

} // namespace Widget
