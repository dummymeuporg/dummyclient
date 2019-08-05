#include "widget/quit_message.hpp"

namespace Widget {

QuitMessage::QuitMessage(Visual& parent)
    : ModalMessage(parent),
      m_quitButton(std::make_shared<Button>(*this)),
      m_changeCharacterButton(std::make_shared<Button>(*this)),
      m_cancelButton(std::make_shared<Button>(*this))
{

    const auto& rectanglePosition(m_backgroundRectangle.getPosition());

    m_quitButton->setFont("arial.ttf");
    m_quitButton->setFontSize(18);
    m_quitButton->setBackgroundColor(sf::Color(183, 109, 44));
    m_quitButton->setBorderColor(sf::Color(94, 47, 6));
    m_quitButton->setColor(sf::Color::Black);
    m_quitButton->setPos(20, 70); // Relative posision.
    m_quitButton->setCaption("Quit");

    m_changeCharacterButton->setFont("arial.ttf");
    m_changeCharacterButton->setFontSize(18);
    m_changeCharacterButton->setBackgroundColor(sf::Color(183, 109, 44));
    m_changeCharacterButton->setBorderColor(sf::Color(94, 47, 6));
    m_changeCharacterButton->setColor(sf::Color::Black);
    m_changeCharacterButton->setPos(90, 70); // Relative posision.
    m_changeCharacterButton->setCaption("Change character");

    m_cancelButton->setFont("arial.ttf");
    m_cancelButton->setFontSize(18);
    m_cancelButton->setBackgroundColor(sf::Color(183, 109, 44));
    m_cancelButton->setBorderColor(sf::Color(94, 47, 6));
    m_cancelButton->setColor(sf::Color::Black);
    m_cancelButton->setPos(200, 70); // Relative posision.
    m_cancelButton->setCaption("Cancel");

    m_message->setFont("arial.ttf");
    m_message->setFontSize(18);
    m_message->setCaption("Do you want to quit?");
    m_message->setColor(sf::Color::Black);

    addButton(m_quitButton);
    addButton(m_changeCharacterButton);
    addButton(m_cancelButton);
}

} // namespace Widget
