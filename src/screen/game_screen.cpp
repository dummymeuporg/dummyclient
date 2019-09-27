#include <cmath>
#include <iostream>

#include <boost/range/irange.hpp>

#include <dummy/server/command/change_character.hpp>
#include <dummy/server/command/message.hpp>
#include <dummy/server/command/ping.hpp>
#include <dummy/server/command/teleport_map.hpp>

#include <dummy/server/response/change_character.hpp>
#include <dummy/server/response/message.hpp>
#include <dummy/server/response/ping.hpp>
#include <dummy/server/response/teleport_map.hpp>

#include "widget/button.hpp"
#include "widget/chatbox.hpp"
#include "widget/quit_message.hpp"

#include "client.hpp"
#include "game.hpp"
#include "graphics/foe.hpp"
#include "graphics/living_state/standing_state.hpp"
#include "graphics/living_state/walking_state.hpp"
#include "floor_view.hpp"

#include "screen/game_screen.hpp"
#include "screen/loading_screen.hpp"

#include "screen/game_screen_state/playing_state.hpp"

namespace Screen {

GameScreen::GameScreen(
    ::Game& game,
    ::Client& client,
    std::unique_ptr<::MapView> mapView
)
    : UIScreen(game, client),
      m_mapView(std::move(mapView)),
      m_player(
          *m_mapView,
          m_client,
          m_client.character()->skin(),
          m_client.character()->name(),
          m_client.character()->position().first,
          m_client.character()->position().second,
          m_client.character()->floor(),
          game.scaleFactor(),
          m_client.character()->direction()
      ),
      m_mapState(*m_mapView),
      m_gameView(sf::FloatRect(0,
                               0,
                               m_game.width(),
                               m_game.height())),
      m_hudView(sf::FloatRect(0,
                              0,
                              m_game.width(),
                              m_game.height())),
      m_state(std::make_shared<GameScreenState::PlayingState>(*this))

{
}

GameScreen::~GameScreen() {
}

void GameScreen::loaded() {
    m_state->loaded();
}

void GameScreen::handleCustomEvent(const ::CustomEvent& event) {
    UIScreen::handleCustomEvent(event);
    switch(event.type()) {
    case CustomEvent::Type::MovementActive:
        m_player.changeState(
            std::make_shared<Graphics::LivingState::WalkingState>(m_player)
        );
        break;
    case CustomEvent::Type::MovementInactive:
        m_player.changeState(
            std::make_shared<Graphics::LivingState::StandingState>(m_player)
        );
        break;
    case CustomEvent::Type::EscapeKeyPressed:
        toggleEscapeMode();
        break;
    // From escape modal box:
    case CustomEvent::CancelButtonClicked:
        if (m_isEscapeMode) {
            removeEscapeMessage();
            m_isEscapeMode = false;
        }
        break;
    case CustomEvent::ChangeCharacterButtonClicked:
        m_client.sendCommand(
            std::make_unique<const Dummy::Server::Command::ChangeCharacter>()
        );
        // XXX: Lock the screen?
        break;
    case CustomEvent::QuitButtonClicked:
        m_game.quit();
        break;
    default:
        break;
    }

}

bool GameScreen::handleEvent(const sf::Event& event) {
    bool forward = UIScreen::handleEvent(event);
    if (!forward) {
        return forward;
    }
    return m_state->handleEvent(event);
}

void GameScreen::onArrowReleased() {
	
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
        pushEvent(
            CustomEvent(
                this,
                CustomEvent::MovementInactive,
                this
            )
        );
        m_isArrowPressed = false;
		m_direction = sf::Keyboard::Unknown;
    }
}

void GameScreen::onArrowPressed() {
    if (!m_isArrowPressed) {
        pushEvent(
            CustomEvent(
                this,
                CustomEvent::MovementActive,
                this
            )
        );
        m_isArrowPressed = true;
    }
}

void GameScreen::onKeyPressed(const sf::Event& event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_characterDirection |= DIRECTION_UP;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_characterDirection |= DIRECTION_RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_characterDirection |= DIRECTION_DOWN;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_characterDirection |= DIRECTION_LEFT;
	}

	if (m_characterDirection != DIRECTION_NONE && !m_isMoving) {
        pushEvent(CustomEvent(this, CustomEvent::MovementActive, this));
		m_isMoving = true;
	}
}

void GameScreen::onKeyReleased(const sf::Event& event) {
    if (sf::Keyboard::Enter == event.key.code && m_isEnterKeyPressed) {
        std::cerr << "Enter key released!" << std::endl;
        m_isEnterKeyPressed = false;
    }
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_characterDirection &= (DIRECTION_ALL ^ DIRECTION_UP);
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_characterDirection &= (DIRECTION_ALL ^ DIRECTION_RIGHT);
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_characterDirection &= (DIRECTION_ALL ^ DIRECTION_DOWN);
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_characterDirection &= (DIRECTION_ALL ^ DIRECTION_LEFT);
	}

	if (m_characterDirection == DIRECTION_NONE && m_isMoving) {
        pushEvent(::CustomEvent(this, CustomEvent::MovementInactive, this));
		m_isMoving = false;
	}

    // XXX: Ugly.
    if (m_isTypingMessage) {
        // Forward the event to the chatbox.
        m_chatbox->handleEvent(event);
    }

    // XXX: same as above. I should use a fancy state pattern.
    if (m_isEscapeKeyPressed) {
        m_isEscapeKeyPressed = false;
    }
}

void GameScreen::onTextEntered(const sf::Event& event) {
    if ('\r' == event.text.unicode) {
        if (!m_isEnterKeyPressed) {
            pushEvent(::CustomEvent(
                this,
                CustomEvent::EnterKeyPressed,
                m_chatbox.get()
            ));
            m_isEnterKeyPressed = true;
            if (m_isTypingMessage) {
                // XXX: Get message and send it.
                std::string messageToSend(m_chatbox->typedMessage());
                m_chatbox->clearMessageInputTextbox();
                std::cerr << "Sent " << messageToSend << std::endl;
                m_player.say(messageToSend);
                m_client.sendCommand(
                    std::make_unique<Dummy::Server::Command::Message>(
                        messageToSend
                    )
                );
            }
            m_isTypingMessage = !m_isTypingMessage;
        }
    } else if ('\033' == event.text.unicode) {
        std::cerr << "Escape pressed" << std::endl;
        if (!m_isEscapeKeyPressed) {
            pushEvent(
                ::CustomEvent(this, CustomEvent::EscapeKeyPressed, this)
            );
            m_isEscapeKeyPressed = true;
        }
    } else if (m_isTypingMessage) {
        // Forward the event to the chatbox.
        m_chatbox->handleEvent(event);
    }
}


void GameScreen::draw(sf::RenderWindow& window) {
    m_state->draw(window);
}

void GameScreen::drawUI(sf::RenderWindow& window) {
    UIScreen::draw(window);
}

void GameScreen::tick() {
    m_state->tick();
}


void GameScreen::onResponse(
    const Dummy::Server::Response::Response& response
) {
    response.accept(*this);
}

void GameScreen::visitResponse(
    const Dummy::Server::Response::SetPosition& setPosition
) {
    m_state->visitResponse(setPosition);
}


void GameScreen::visitResponse(
    const Dummy::Server::Response::Ping& ping
) {
    m_state->visitResponse(ping);
}

void GameScreen::visitResponse(
    const Dummy::Server::Response::Message& message
) {
    m_state->visitResponse(message);
}

void GameScreen::visitResponse(
    const Dummy::Server::Response::ChangeCharacter& changeCharacter
)
{
    auto self(shared_from_this());
    m_state->visitResponse(changeCharacter);
}

void GameScreen::visitResponse(
    const Dummy::Server::Response::TeleportMap& teleportMap
)
{
    auto self(shared_from_this());
    m_state->visitResponse(teleportMap);
}

void GameScreen::onMessage(const std::string& message) {
    m_state->onMessage(message);
}

void GameScreen::addWidget(std::shared_ptr<Widget::Abstract::Widget> widget) {
    UIScreen::addWidget(widget);
}

void GameScreen::onTeleport(
    const std::string& destinationMap,
    std::uint16_t x,
    std::uint16_t y,
    std::uint8_t floor
) {
    m_state->onTeleport(destinationMap, x, y, floor);
}

void GameScreen::pushEvent(CustomEvent&& customEvent) {
    GameElement::pushEvent(std::move(customEvent));
}


} // namespace Screen
