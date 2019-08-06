#include <iostream>
#include "widget/quit_message.hpp"

namespace Widget {

QuitMessage::QuitMessage(Visual& parent)
    : ModalMessage(parent, "Do you want to quit?"),
      m_quitButton(std::make_shared<Button>(*this)),
      m_changeCharacterButton(std::make_shared<Button>(*this)),
      m_cancelButton(std::make_shared<Button>(*this))
{

    const auto& rectOrigin(m_backgroundRectangle.getOrigin());
    m_quitButton->setFont("arial.ttf");
    m_quitButton->setFontSize(18);
    m_quitButton->setBackgroundColor(sf::Color(183, 109, 44));
    m_quitButton->setBorderColor(sf::Color(94, 47, 6));
    m_quitButton->setColor(sf::Color::Black);
    m_quitButton->setPos(20, 55); // Relative posision.
    m_quitButton->setOrigin(rectOrigin.x, rectOrigin.y);
    m_quitButton->setCaption("Quit");

    m_changeCharacterButton->setFont("arial.ttf");
    m_changeCharacterButton->setFontSize(18);
    m_changeCharacterButton->setBackgroundColor(sf::Color(183, 109, 44));
    m_changeCharacterButton->setBorderColor(sf::Color(94, 47, 6));
    m_changeCharacterButton->setColor(sf::Color::Black);
    m_changeCharacterButton->setPos(130, 55); // Relative posision.
    m_changeCharacterButton->setOrigin(rectOrigin.x, rectOrigin.y);
    m_changeCharacterButton->setCaption("Change character");

    m_cancelButton->setFont("arial.ttf");
    m_cancelButton->setFontSize(18);
    m_cancelButton->setBackgroundColor(sf::Color(183, 109, 44));
    m_cancelButton->setBorderColor(sf::Color(94, 47, 6));
    m_cancelButton->setColor(sf::Color::Black);
    m_cancelButton->setPos(375, 55); // Relative posision.
    m_cancelButton->setOrigin(rectOrigin.x, rectOrigin.y);
    m_cancelButton->setCaption("Cancel");

    addButton(m_quitButton);
    addButton(m_changeCharacterButton);
    addButton(m_cancelButton);
}

void QuitMessage::handleCustomEvent(const ::CustomEvent& event) {
    if (event.source() == m_quitButton.get()) {
        std::cerr << "Quit button clicked!" << std::endl;
        pushEvent(::CustomEvent(
            this, ::CustomEvent::Type::QuitButtonClicked, &m_parent)
        );
    } else if (event.source() == m_changeCharacterButton.get()) {
        std::cerr << "Change character button clicked!" << std::endl;
        pushEvent(::CustomEvent(
            this, ::CustomEvent::Type::ChangeCharacterButtonClicked, &m_parent)
        );
    } else if (event.source() == m_cancelButton.get()) {
        pushEvent(::CustomEvent(
            this, ::CustomEvent::Type::CancelButtonClicked, &m_parent)
        );
        std::cerr << "Cancel button clicked!";
    }
}
} // namespace Widget
