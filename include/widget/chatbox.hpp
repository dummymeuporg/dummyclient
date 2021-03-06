#pragma once

#include "widget/abstract/widget.hpp"

namespace Widget {

class Textbox;

class Chatbox : public Abstract::Widget {
public:
    Chatbox(Visual&);
    void draw(sf::RenderWindow&) override;
    bool handleEvent(const sf::Event& event) override;
    bool handleCustomEvent(const ::CustomEvent& event) override;
    sf::IntRect boundingRect() const override;
    const std::string& typedMessage() const;
    void clearMessageInputTextbox();
private:
    bool m_isTypingMessage;
    std::shared_ptr<Textbox> m_messageInputTextbox;
};

}
