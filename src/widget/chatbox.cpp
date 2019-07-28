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
        .setFont("arial.ttf");
}

void Chatbox::paint(sf::RenderWindow& window) {
    m_messageInputTextbox->paint(window);
}

bool Chatbox::handleEvent(const sf::Event& event) {
    return true;
}

void Chatbox::handleCustomEvent(const ::CustomEvent& event) {
    switch(event.type()) {
    case CustomEvent::Type::EnterKeyPressed:
        break;
    default:
        break;
    }
}

} // namespace Widget
