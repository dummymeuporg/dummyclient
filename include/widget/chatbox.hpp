#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class Textbox;

class Chatbox : public Abstract::Widget {
public:
    Chatbox(std::shared_ptr<Widget> = nullptr);
    void paint(sf::RenderWindow&) override;
    bool handleEvent(const sf::Event& event) override;
    void handleCustomEvent(const ::CustomEvent& event) override;
    const std::string& typedMessage() const;
    void clearMessageInputTextbox();
private:
    bool m_isTypingMessage;
    std::shared_ptr<Textbox> m_messageInputTextbox;
};

}
