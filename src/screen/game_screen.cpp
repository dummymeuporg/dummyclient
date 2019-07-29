#include <cmath>
#include <iostream>

#include <boost/range/irange.hpp>

#include <dummy/server/command/message.hpp>
#include <dummy/server/command/ping.hpp>
#include <dummy/server/response/ping.hpp>

#include "widget/chatbox.hpp"

#include "client.hpp"
#include "game.hpp"
#include "graphics/foe.hpp"
#include "graphics/living_state/standing_state.hpp"
#include "graphics/living_state/walking_state.hpp"
#include "level_view.hpp"

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
      m_chatbox(std::make_shared<Widget::Chatbox>()),
      m_isTypingMessage(false),
      m_isEnterKeyPressed(false)
{
    m_player.setX(m_client.character()->position().first * 8);
    m_player.setY(m_client.character()->position().second * 8);

    // XXX: find a better way to construct the camera.
    m_gameView.setCenter(m_player.x() + 12, m_player.y() + 16);
    m_gameView.zoom(0.5);
    m_game.window().setView(m_gameView);

    addWidget(m_chatbox);
}

GameScreen::~GameScreen() {
}

void GameScreen::loaded() {
    m_client.ping();
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
    default:
        break;
    }

}

void GameScreen::handleEvent(const sf::Event& event)
{
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
}

void GameScreen::onArrowReleased() {
	
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
        pushEvent(
            CustomEvent(
                reinterpret_cast<void*>(shared_from_this().get()),
                CustomEvent::MovementInactive,
                reinterpret_cast<void*>(shared_from_this().get())
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
                reinterpret_cast<void*>(shared_from_this().get()),
                CustomEvent::MovementActive,
                reinterpret_cast<void*>(shared_from_this().get())
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
		pushEvent(
			CustomEvent(
				reinterpret_cast<void*>(shared_from_this().get()),
				CustomEvent::MovementActive,
				reinterpret_cast<void*>(shared_from_this().get())
			)
		);
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
		pushEvent(
			CustomEvent(
				reinterpret_cast<void*>(shared_from_this().get()),
				CustomEvent::MovementInactive,
				reinterpret_cast<void*>(shared_from_this().get())
			)
		);
		m_isMoving = false;
	}

    // XXX: Ugly.
    if (m_isTypingMessage) {
        // Forward the event to the chatbox.
        m_chatbox->handleEvent(event);
    }
}

void GameScreen::onTextEntered(const sf::Event& event) {
    if ('\r' == event.text.unicode) {
        if (!m_isEnterKeyPressed) {
            pushEvent(
                ::CustomEvent(
                    reinterpret_cast<void*>(shared_from_this().get()),
                    CustomEvent::EnterKeyPressed,
                    reinterpret_cast<void*>(m_chatbox.get())
                )
            );
            m_isEnterKeyPressed = true;
            if (m_isTypingMessage) {
                // XXX: Get message and send it.
                std::string messageToSend(m_chatbox->typedMessage());
                m_chatbox->clearMessageInputTextbox();
                std::cerr << "Sent " << messageToSend << std::endl;
                m_player.say(messageToSend);
                m_client.sendCommand(
                    Dummy::Server::Command::Message(messageToSend)
                );
            }
            m_isTypingMessage = !m_isTypingMessage;
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

void GameScreen::drawLevelView(unsigned int index, LevelView& levelView)
{
    // Draw the lower layers.
    drawSprites(levelView.bottomSprites());

    drawLivings(index);

    // Draw the character if needed.
    if (m_player.floor() == index) {
        drawCharacter();
    }

    // Draw the livings on the current floor.
    const auto& localFloorState(m_mapState.localFloorState(index));
    for (auto& [name, foe]: localFloorState.graphicFoes()) {
        foe->draw(m_game.window());
    }

    drawSprites(levelView.topSprites());

    if (m_debugMode) {
        drawBlockingLayer(index, levelView);
    }
}

void GameScreen::drawBlockingLayer(unsigned int index, LevelView& levelView) {
    auto maxHeight(static_cast<int>(m_mapView->height() * 2));
    auto maxWidth(static_cast<int>(m_mapView->width() * 2));
    for (const auto y: boost::irange(0, maxHeight)) {
        for(const auto x: boost::irange(0, maxWidth)) {
            std::size_t blockIndex = (y * m_mapView->width() * 2) + x;
            if (m_mapView->blocksAt(index, x*8, y*8)) {
                auto& blockingSquare(levelView.blockingSquares().at(blockIndex));
                blockingSquare.setPosition(x * 8, y * 8);
                m_game.window().draw(blockingSquare);
            }
        }
    }
}


void GameScreen::drawCharacter() {

    m_player.draw(m_game.window());
}

void GameScreen::drawLivings(std::uint8_t index) {
    auto& graphicFoes(m_mapState.localFloorState(index).graphicFoes());
    for (auto& [name, foe]: graphicFoes) {
        foe->draw(m_game.window());
    }
}

void GameScreen::draw() {
    m_game.window().setView(m_gameView);
    m_gameView.setCenter(m_player.x() + 12, m_player.y() + 16);
    for (unsigned i = 0; i < m_mapView->levelViews().size(); ++i) {
        drawLevelView(i, m_mapView->levelView(i));
    }
    // Draw widgets (HUD) if needed.
    m_game.window().setView(m_hudView);
    UIScreen::draw();

}

void GameScreen::tick() {
    m_player.tick();
    m_mapState.tick();
    if (m_pingClock.getElapsedTime().asMilliseconds() >= 100) {
        m_client.sendCommand(Dummy::Server::Command::Ping());
        m_pingClock.restart();
    }

    if (!m_isArrowPressed && m_direction != sf::Keyboard::Unknown) {
        onArrowPressed();
    } else {
        moveCharacter(m_direction);
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

} // namespace Screen
