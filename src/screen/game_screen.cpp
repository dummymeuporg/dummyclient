#include <cmath>
#include <iostream>

#include <boost/range/irange.hpp>

#include <dummy/server/command/change_character.hpp>
#include <dummy/server/command/message.hpp>
#include <dummy/server/command/ping.hpp>

#include <dummy/server/response/change_character.hpp>
#include <dummy/server/response/message.hpp>
#include <dummy/server/response/ping.hpp>

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
      m_isArrowPressed(false),
      m_direction(sf::Keyboard::Unknown),
	  m_characterDirection(DIRECTION_NONE),
	  m_isMoving(false),
      m_mapState(*m_mapView),
      m_gameView(sf::FloatRect(0,
                               0,
                               m_game.width(),
                               m_game.height())),
      m_hudView(sf::FloatRect(0,
                              0,
                              m_game.width(),
                              m_game.height())),
      m_debugMode(false),
      m_chatbox(std::make_shared<Widget::Chatbox>(*this)),
      m_isTypingMessage(false),
      m_isEnterKeyPressed(false),
      m_isEscapeKeyPressed(false),
      m_isEscapeMode(false),
      m_quitMessage(nullptr)
{
    m_player.setX(m_client.character()->position().first * 8);
    m_player.setY(m_client.character()->position().second * 8);

    // XXX: find a better way to construct the camera.
    m_gameView.setCenter(m_player.x() + 12, m_player.y() + 16);
    m_gameView.zoom(0.5);
    m_game.window().setView(m_gameView);

    addWidget(m_chatbox);

    m_mapView->map().setEventObserver(this);
}

GameScreen::~GameScreen() {
}

void GameScreen::loaded() {
    //m_client.ping();
    m_pingClock.restart();
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
    switch(event.type) {
    case sf::Event::KeyPressed:
        onKeyPressed(event);
        break;
    case sf::Event::KeyReleased:
        onKeyReleased(event);
        break;
    case sf::Event::TextEntered:
        onTextEntered(event);
        break;
    default:
        break;
    }
    return true;
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

void GameScreen::moveCharacter(sf::Keyboard::Key key) {

	int xVector = 0;
	int yVector = 0;

	if (m_characterDirection & DIRECTION_RIGHT) {
		++xVector;
	}

	if (m_characterDirection & DIRECTION_LEFT) {
		--xVector;
	}

	if (m_characterDirection & DIRECTION_UP) {
		--yVector;
	}

	if (m_characterDirection & DIRECTION_DOWN) {
		++yVector;
	}

	if (yVector < 0) {
		m_player.setDirection(Dummy::Core::Character::Direction::UP);
	} else if (yVector > 0) {
		m_player.setDirection(Dummy::Core::Character::Direction::DOWN);
	} else if (xVector < 0) {
		m_player.setDirection(Dummy::Core::Character::Direction::LEFT);
	} else if (xVector > 0) {
		m_player.setDirection(Dummy::Core::Character::Direction::RIGHT);
	}

    m_player.setXMovement(xVector);
    m_player.setYMovement(yVector);
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

void GameScreen::drawSprites(Sprites& sprites) {
    const auto& height(static_cast<int>(m_mapView->height()));
    const auto& width(static_cast<int>(m_mapView->width()));
    for (const auto y: boost::irange(0, height)) {
        for(const auto x: boost::irange(0, width)) {
            std::size_t index = (y * m_mapView->width()) + x;
            sf::Sprite& sprite = sprites.at(index);

            int windowX = (x * 16);
            int windowY = (y * 16);

            // Only draw the sprite if it has a texture.
            if (nullptr != sprite.getTexture()) {
                sprite.setPosition(sf::Vector2f(windowX, windowY));
                m_game.window().draw(sprite);
            }
        }
    }
}

void GameScreen::toggleEscapeMode() {
    if (!m_isEscapeMode) {
        // Instantiate the modal message. Display it.
        buildEscapeMessage();
    } else {
        // Remove the modal message.
        //m_quitMessage.reset();
        removeEscapeMessage();
    }
    m_isEscapeMode = !m_isEscapeMode;
}

void GameScreen::buildEscapeMessage() {
    m_quitMessage = std::make_shared<Widget::QuitMessage>(*this);
}

void GameScreen::removeEscapeMessage() {
    removeChild(m_quitMessage);
}

void GameScreen::drawFloorViewHUD(unsigned int index, FloorView& floorView) {
    /*
    drawLivingsHUD(index);
    if (m_player.floor() == index) {
        drawCharacterHUD();
    }
    */

    // Draw the character HUD, if needed
    if (m_player.floor() == index) {
        drawCharacterHUD();
    }

    // Draw the living HUD on the current floor
    const auto& localFloorState(m_mapState.localFloorState(index));
    for (auto& [name, foe]: localFloorState.graphicFoes()) {
        foe->drawHUD(m_game.window(), m_gameView);
    }

}

void GameScreen::drawFloorView(unsigned int index, FloorView& floorView)
{
    // Draw the lower layers.
    drawSprites(floorView.bottomSprites());

    //drawLivings(index);

    // Draw the character if needed.
    if (m_player.floor() == index) {
        drawCharacter();
    }

    // Draw the livings on the current floor.
    const auto& localFloorState(m_mapState.localFloorState(index));
    for (auto& [name, foe]: localFloorState.graphicFoes()) {
        foe->draw(m_game.window());
    }

    drawSprites(floorView.topSprites());

    if (m_debugMode) {
        drawBlockingLayer(index, floorView);
    }
}

void GameScreen::drawBlockingLayer(unsigned int index, FloorView& floorView) {
    auto maxHeight(static_cast<int>(m_mapView->height() * 2));
    auto maxWidth(static_cast<int>(m_mapView->width() * 2));
    for (const auto y: boost::irange(0, maxHeight)) {
        for(const auto x: boost::irange(0, maxWidth)) {
            std::size_t blockIndex = (y * m_mapView->width() * 2) + x;
            if (m_mapView->blocksAt(index, x*8, y*8)) {
                auto& blockingSquare(floorView.blockingSquares().at(blockIndex));
                blockingSquare.setPosition(x * 8, y * 8);
                m_game.window().draw(blockingSquare);
            }
        }
    }
}


void GameScreen::drawCharacter() {

    m_player.draw(m_game.window());
}

void GameScreen::drawCharacterHUD() {
    m_player.drawHUD(m_game.window(), m_gameView);
}

void GameScreen::drawLivings(std::uint8_t index) {
    auto& graphicFoes(m_mapState.localFloorState(index).graphicFoes());
    for (auto& [name, foe]: graphicFoes) {
        foe->draw(m_game.window());
    }
}

void GameScreen::draw(sf::RenderWindow& window) {
    m_gameView.setCenter(m_player.x() + 12, m_player.y() + 16);
    window.setView(m_gameView);

    for (unsigned i = 0; i < m_mapView->floorViews().size(); ++i) {
        drawFloorView(i, m_mapView->floorView(i));
    }
    //m_gameView.setCenter(m_player.x() + 12, m_player.y() + 16);
    // Draw widgets (HUD) if needed.
    window.setView(m_hudView);

    for (unsigned i = 0; i < m_mapView->floorViews().size(); ++i) {
        drawFloorViewHUD(i, m_mapView->floorView(i));
    }

    // XXX: ugly.
    if (m_isEscapeMode) {
        m_quitMessage->draw(window);
    }
    UIScreen::draw(window);
}

void GameScreen::tick() {
    m_player.tick();
    m_mapState.tick();

    if (!m_isArrowPressed && m_direction != sf::Keyboard::Unknown) {
        onArrowPressed();
    } else {
        moveCharacter(m_direction);
    }

    //XXX: Ugly. Too much dereferencing to access a simple property.
    const auto& touchEvents(
        m_mapView->map().floors()[m_player.floor()].touchEvents()
    );
    auto pos = m_player.serverPosition();
    std::pair<std::uint16_t, std::uint16_t> normalizedPos{
        pos.first / 2,
        pos.second/2
    };
    std::uint16_t eventIndex(
        normalizedPos.second * m_mapView->width() + normalizedPos.first
    );
    if (touchEvents.find(eventIndex) != std::end(touchEvents)) {
        std::cerr << "There is a touch event!" << std::endl;
        touchEvents.at(eventIndex)->execute();
    }
}


void GameScreen::onResponse(
    const Dummy::Server::Response::Response& response
) {
    response.accept(*this);
}

void GameScreen::visitResponse(
    const Dummy::Server::Response::SetPosition& setPosition
) {
    // XXX: Nothing to do for now!
}


void GameScreen::visitResponse(
    const Dummy::Server::Response::Ping& ping
) {
    for (const auto& update: ping.mapUpdates()) {
        m_mapState.update(*update);
    }
}

void GameScreen::visitResponse(
    const Dummy::Server::Response::Message& message
) {
    // XXX: condition ugly. m_player should have a name attribute.
    if (message.author() != m_client.character()->name()) {
        m_mapState.say(message.author(), message.content());
    }
}

void GameScreen::visitResponse(
    const Dummy::Server::Response::ChangeCharacter& changeCharacter
)
{
    auto self(shared_from_this());
    m_client.character()->setPosition(changeCharacter.position());
    m_client.character()->setMapLocation(changeCharacter.mapLocation());
    m_client.returnToPreviousScreen();
}

void GameScreen::onMessage(const std::string& message) {
    std::cerr << "Message: " << message << std::endl;
}


void GameScreen::onTeleport(
    const std::string& destinationMap,
    std::uint16_t x,
    std::uint16_t y,
    std::uint8_t floor
) {
    std::cerr << "Teleport to: " << destinationMap << "("
        << x << ", " << y << ", " << static_cast<int>(floor) << ")"
        << std::endl;
}


} // namespace Screen
