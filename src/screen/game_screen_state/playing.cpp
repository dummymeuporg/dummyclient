#include <memory>
#include <boost/range/irange.hpp>

#include <dummy/server/command/change_character.hpp>
#include <dummy/server/command/message.hpp>
#include <dummy/server/command/ping.hpp>
#include <dummy/server/command/teleport_map.hpp>

#include <dummy/server/response/change_character.hpp>
#include <dummy/server/response/message.hpp>
#include <dummy/server/response/ping.hpp>
#include <dummy/server/response/teleport_map.hpp>


#include "config.hpp"
#include "custom_event_queue.hpp"
#include "game.hpp"

#include "graphics/foe.hpp"
#include "graphics/living_state/standing_state.hpp"
#include "graphics/living_state/walking_state.hpp"

#include "screen/game_screen.hpp"
#include "screen/game_screen_state/playing.hpp"
#include "screen/game_screen_state/teleporting.hpp"


#include "widget/quit_message.hpp"

namespace Screen {
namespace GameScreenState {

Playing::Playing(GameScreen& gameScreen)
    : State(gameScreen),
      m_characterDirection(DIRECTION_NONE),
      m_direction(sf::Keyboard::Unknown),
      m_isArrowPressed(false),
      m_isMoving(false),
      m_debugMode(false),
      m_isTypingMessage(false),
      m_isEnterKeyPressed(false),
      m_isEscapeKeyPressed(false),
      m_isEscapeMode(false),
      m_isTeleporting(false),
      m_settingsButton(std::make_shared<Widget::IconButton>(m_gameScreen)),
      m_chatbox(std::make_shared<Widget::Chatbox>(m_gameScreen)),
      m_quitMessage(nullptr),
      m_floatWindow(std::make_shared<Widget::FloatWindow>(m_gameScreen)),
      m_currentGameMessage(
          std::make_shared<Widget::Game::Message>(m_gameScreen)
      )
{
    m_player.setX(m_client.character()->position().first * 8);
    m_player.setY(m_client.character()->position().second * 8);

    // XXX: find a better way to construct the camera.
    m_gameView.setCenter(m_player.x() + 12, m_player.y() + 16);
    m_gameView.zoom(0.5);
    m_game.window().setView(m_gameView);

    m_settingsButton->setSize(32, 32);
    m_settingsButton->setPos(0, 0);
    m_settingsButton->setColor(sf::Color(255, 0, 0));

    m_floatWindow->setEnabled(false);

    //buildEscapeMessage();
    m_quitMessage = std::make_shared<Widget::QuitMessage>(m_gameScreen);
    m_quitMessage->setEnabled(false);

    m_gameScreen.addWidget(m_settingsButton);
    m_gameScreen.addWidget(m_chatbox);
    m_gameScreen.addWidget(m_floatWindow);
    m_gameScreen.addWidget(m_quitMessage);



    m_mapView.map().setEventObserver(&m_gameScreen);


}

void Playing::loaded() {
    m_pingClock.restart();
}

void Playing::draw(sf::RenderWindow& window) {

    // Properties of GameScreen
    auto& gameView(m_gameScreen.gameView());
    auto& player(m_gameScreen.player());
    auto& mapView(m_gameScreen.mapView());
    auto& hudView(m_gameScreen.hudView());

    gameView.setCenter(player.x() + 12, player.y() + 16);
    window.setView(gameView);

    for (unsigned i = 0; i < mapView.floorViews().size(); ++i) {
        drawFloorView(i, mapView.floorView(i));
    }
    //m_gameView.setCenter(m_player.x() + 12, m_player.y() + 16);
    // Draw widgets (HUD) if needed.
    window.setView(hudView);

    for (unsigned i = 0; i < mapView.floorViews().size(); ++i) {
        drawFloorViewHUD(i, mapView.floorView(i));
    }

    // XXX: ugly.
    if (m_isEscapeMode) {
        m_quitMessage->draw(window);
    }
    m_gameScreen.drawUI(window);
}

void Playing::drawFloorView(unsigned int index, ::FloorView& floorView) {
    auto& game(m_gameScreen.game());
    auto& mapState(m_gameScreen.mapState());
    auto& player(m_gameScreen.player());

    // Draw the lower layers.
    drawSprites(floorView.bottomSprites());

    //drawLivings(index);

    // Draw the livings on the current floor.
    const auto& localFloorState(mapState.localFloorState(index));
    for (auto& [name, foe]: localFloorState.graphicFoes()) {
        foe->draw(game.window());
    }

    // Draw the character if needed.
    if (player.floor() == index) {
        drawCharacter();
    }

    drawSprites(floorView.topSprites());

    if (m_debugMode) {
        drawBlockingLayer(index, floorView);
    }
}

void Playing::drawFloorViewHUD(unsigned int index, ::FloorView& floorView)
{
    auto& game(m_gameScreen.game());
    auto& mapState(m_gameScreen.mapState());
    auto& player(m_gameScreen.player());
    auto& gameView(m_gameScreen.gameView());


    // Draw the character HUD, if needed
    if (player.floor() == index) {
        drawCharacterHUD();
    }

    // Draw the living HUD on the current floor
    const auto& localFloorState(mapState.localFloorState(index));
    for (auto& [name, foe]: localFloorState.graphicFoes()) {
        foe->drawHUD(game.window(), gameView);
    }
}

void Playing::drawSprites(Sprites& sprites) {
    auto& game(m_gameScreen.game());
    auto& mapView(m_gameScreen.mapView());

    const auto& height(static_cast<int>(mapView.height()));
    const auto& width(static_cast<int>(mapView.width()));
    for (const auto y: boost::irange(0, height)) {
        for(const auto x: boost::irange(0, width)) {
            std::size_t index = (y * mapView.width()) + x;
            sf::Sprite& sprite = sprites.at(index);

            int windowX = (x * 16);
            int windowY = (y * 16);

            // Only draw the sprite if it has a texture.
            if (nullptr != sprite.getTexture()) {
                sprite.setPosition(sf::Vector2f(windowX, windowY));
                game.window().draw(sprite);
            }
        }
    }
}

void Playing::drawBlockingLayer(unsigned int index, FloorView& floorView)
{
    auto& game(m_gameScreen.game());
    auto& mapView(m_gameScreen.mapView());

    auto maxHeight(static_cast<int>(mapView.height() * 2));
    auto maxWidth(static_cast<int>(mapView.width() * 2));
    for (const auto y: boost::irange(0, maxHeight)) {
        for(const auto x: boost::irange(0, maxWidth)) {
            std::size_t blockIndex = (y * mapView.width() * 2) + x;
            if (mapView.blocksAt(index, x*8, y*8)) {
                auto& blockingSquare(floorView.blockingSquares().at(blockIndex));
                blockingSquare.setPosition(x * 8, y * 8);
                game.window().draw(blockingSquare);
            }
        }
    }
}


void Playing::drawCharacter() {
    auto& player(m_gameScreen.player());
    auto& game(m_gameScreen.game());
    player.draw(game.window());
}

void Playing::drawCharacterHUD() {
    auto& player(m_gameScreen.player());
    auto& game(m_gameScreen.game());
    auto& gameView(m_gameScreen.gameView());

    player.drawHUD(game.window(), gameView);
}

void Playing::tick() {

    m_player.tick();
    m_mapState.tick();

    if (!m_isArrowPressed && m_direction != sf::Keyboard::Unknown) {
        onArrowPressed();
    } else {
        moveCharacter(m_direction);
    }

    //XXX: Ugly. Too much dereferencing to access a simple property.
    const auto& touchEvents(
        m_mapView.map().floors()[m_player.floor()].touchEvents()
    );
    auto pos = m_player.serverPosition();
    std::pair<std::uint16_t, std::uint16_t> normalizedPos{
        pos.first / 2,
        pos.second/2
    };
    std::uint16_t eventIndex(
        normalizedPos.second * m_mapView.width() + normalizedPos.first
    );
    if (touchEvents.find(eventIndex) != std::end(touchEvents)) {
        std::cerr << "There is a touch event!" << std::endl;
        touchEvents.at(eventIndex)->execute();
    }
}

void Playing::moveCharacter(sf::Keyboard::Key) {
    auto& player(m_gameScreen.player());
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
        player.setDirection(Dummy::Core::Character::Direction::UP);
    } else if (yVector > 0) {
        player.setDirection(Dummy::Core::Character::Direction::DOWN);
    } else if (xVector < 0) {
        player.setDirection(Dummy::Core::Character::Direction::LEFT);
    } else if (xVector > 0) {
        player.setDirection(Dummy::Core::Character::Direction::RIGHT);
    }

    player.setXMovement(xVector);
    player.setYMovement(yVector);
}

void Playing::triggerEvent(
    const std::pair<std::uint16_t, std::uint16_t>& coords
) {
    std::uint16_t index(coords.second * m_mapView.width() + coords.first);
    //XXX: Ugly. Too much dereferencing to access a simple property.
    const auto& keyPressMapEvents(
        m_mapView.map().floors()[m_player.floor()].keypressEvents()
    );

    if (keyPressMapEvents.find(index) != std::end(keyPressMapEvents)) {
        std::cerr << "There is a key press event!" << std::endl;
        keyPressMapEvents.at(index)->execute();
    }
}

void Playing::testOnKeyPressedMapEvent() {
    std::pair<std::uint16_t, uint16_t> eventCoords {
        m_player.x() / 16,
        m_player.y() / 16
    };

    switch(m_player.direction()) {
    case Dummy::Core::Character::Direction::UP:
        if (eventCoords.second > 0) {
            --eventCoords.second;
            triggerEvent(eventCoords);
        }
        break;
    case Dummy::Core::Character::Direction::LEFT:
        if (eventCoords.first > 0) {
            --eventCoords.first;
            triggerEvent(eventCoords);
        }
        break;
    case Dummy::Core::Character::Direction::RIGHT:
        if (eventCoords.first < m_mapView.width() - 1) {
            ++eventCoords.first;
            triggerEvent(eventCoords);
        }
        break;
    case Dummy::Core::Character::Direction::DOWN:
        if (eventCoords.second < m_mapView.height() - 1) {
            ++eventCoords.second;
            triggerEvent(eventCoords);
        }
    }

}

void Playing::onKeyPressed(const sf::Event& event) {

    if (m_gameScreen.game().config().interactKey() == event.key.code) {
        testOnKeyPressedMapEvent();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            || sf::Keyboard::isKeyPressed(m_game.config().upKey())) {
        m_characterDirection |= DIRECTION_UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
            || sf::Keyboard::isKeyPressed(m_game.config().rightKey())) {
        m_characterDirection |= DIRECTION_RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
            || sf::Keyboard::isKeyPressed(m_game.config().downKey())) {
        m_characterDirection |= DIRECTION_DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
            || sf::Keyboard::isKeyPressed(m_game.config().leftKey())) {
        m_characterDirection |= DIRECTION_LEFT;
    }

    if (m_characterDirection != DIRECTION_NONE && !m_isMoving) {
        m_gameScreen.pushEvent(
            CustomEvent(
                &m_gameScreen,
                CustomEvent::MovementActive,
                &m_gameScreen
            )
        );
        m_isMoving = true;
    }
}

void
Playing::visitResponse(const Dummy::Server::Response::Message& message) {
    // XXX: condition ugly. m_player should have a name attribute.
    //if (message.author() != m_client.character()->id()) {
        m_mapState.say(message.author(), message.content());
    //}
}

void
Playing::visitResponse(const Dummy::Server::Response::Ping& ping) {
    for (const auto& update: ping.mapUpdates()) {
        m_mapState.update(*update);
    }
}

void
Playing::visitResponse(const Dummy::Server::Response::SetPosition&) {
    // Nothing to do.
}

void
Playing::visitResponse(
    const Dummy::Server::Response::ChangeCharacter& changeCharacter
) {
    m_client.character()->setPosition(changeCharacter.position());
    m_client.character()->setMapLocation(changeCharacter.mapLocation());
    m_client.returnToPreviousScreen();
}

void
Playing::visitResponse(
    const Dummy::Server::Response::TeleportMap&
) {
    // Should be handled by the 'Teleporting' state.
}

void Playing::onTeleport(
    const std::string& destinationMap,
    std::uint16_t x,
    std::uint16_t y,
    std::uint8_t floor
) {
    auto self(shared_from_this());
    std::cerr << "Teleport to: " << destinationMap << "("
        << x << ", " << y << ", " << static_cast<int>(floor) << ")"
        << std::endl;
    m_client.sendCommand(
        std::make_unique<const Dummy::Server::Command::TeleportMap>(
            destinationMap, x*2, y*2, floor, "main"
        )
    );
    m_client.character()->setMapLocation(destinationMap);
    m_client.character()->setPosition({x*2, y*2});

    // XXX: Change state!
    m_gameScreen.setState(std::make_shared<Teleporting>(m_gameScreen));
}

void Playing::onMessage(const std::string& message) {
    //std::cerr << "Message: " << message << std::endl;
    m_currentGameMessage->setContent(message);
    m_currentGameMessage->setEnabled(true);
}

void Playing::buildEscapeMessage() {
    //m_quitMessage = std::make_shared<Widget::QuitMessage>(m_gameScreen);
    m_quitMessage->setEnabled(true);
}

void Playing::removeEscapeMessage() {
    //m_gameScreen.removeChild(m_quitMessage);
    m_quitMessage->setEnabled(false);
}

void Playing::toggleEscapeMode() {
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

bool Playing::handleEvent(const sf::Event& event) {
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

bool Playing::onButtonClicked(const ::CustomEvent &event) {
    if (event.target() == m_settingsButton.get()) {
        std::cerr << "Clicked on settings button." << std::endl;
        m_floatWindow->setEnabled(!m_floatWindow->isEnabled());
        return false;
    }
    return true;
}

bool Playing::handleCustomEvent(const ::CustomEvent& event) {
    bool forwardEvent(true);
    switch(event.type()) {
    case CustomEvent::LeftClick:
        forwardEvent = onButtonClicked(event);
        break;
    case CustomEvent::Type::MovementActive:
        m_player.changeState(
            std::make_shared<Graphics::LivingState::WalkingState>(m_player)
        );
        forwardEvent = false;
        break;
    case CustomEvent::Type::MovementInactive:
        m_player.changeState(
            std::make_shared<Graphics::LivingState::StandingState>(m_player)
        );
        forwardEvent = false;
        break;
    case CustomEvent::Type::EscapeKeyPressed:
        toggleEscapeMode();
        forwardEvent = false;
        break;
    // From escape modal box:
    case CustomEvent::CancelButtonClicked:
        if (m_isEscapeMode) {
            removeEscapeMessage();
            m_isEscapeMode = false;
        }
        forwardEvent = false;
        break;
    case CustomEvent::ChangeCharacterButtonClicked:
        m_client.sendCommand(
            std::make_unique<const Dummy::Server::Command::ChangeCharacter>()
        );
        // XXX: Lock the screen?
        forwardEvent = false;
        break;
    case CustomEvent::QuitButtonClicked:
        m_game.quit();
        forwardEvent = false;
        break;
    default:
        forwardEvent = true;
        break;
    }
    return forwardEvent;
}

void Playing::onArrowReleased() {

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
        !sf::Keyboard::isKeyPressed(m_game.config().upKey()) &&
        !sf::Keyboard::isKeyPressed(m_game.config().leftKey()) &&
        !sf::Keyboard::isKeyPressed(m_game.config().downKey()) &&
        !sf::Keyboard::isKeyPressed(m_game.config().rightKey()))
    {
        m_gameScreen.pushEvent(
            CustomEvent(
                &m_gameScreen,
                CustomEvent::MovementInactive,
                &m_gameScreen
            )
        );
        m_isArrowPressed = false;
        m_direction = sf::Keyboard::Unknown;
    }
}

void Playing::onArrowPressed() {
    if (!m_isArrowPressed) {
        m_gameScreen.pushEvent(
            CustomEvent(
                &m_gameScreen,
                CustomEvent::MovementActive,
                &m_gameScreen
            )
        );
        m_isArrowPressed = true;
    }
}

void Playing::onKeyReleased(const sf::Event& event) {
    std::cerr << "Key released code: " << event.key.code << std::endl;
    if (sf::Keyboard::Enter == event.key.code && m_isEnterKeyPressed) {
        std::cerr << "Enter key released!" << std::endl;
        m_isEnterKeyPressed = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            !sf::Keyboard::isKeyPressed(m_game.config().upKey())) {
        m_characterDirection &= (DIRECTION_ALL ^ DIRECTION_UP);
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            !sf::Keyboard::isKeyPressed(m_game.config().rightKey())) {
        m_characterDirection &= (DIRECTION_ALL ^ DIRECTION_RIGHT);
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
            !sf::Keyboard::isKeyPressed(m_game.config().downKey())) {
        m_characterDirection &= (DIRECTION_ALL ^ DIRECTION_DOWN);
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            !sf::Keyboard::isKeyPressed(m_game.config().leftKey())) {
        m_characterDirection &= (DIRECTION_ALL ^ DIRECTION_LEFT);
    }

    if (m_characterDirection == DIRECTION_NONE && m_isMoving) {
        m_gameScreen.pushEvent(
            ::CustomEvent(
                &m_gameScreen,
                CustomEvent::MovementInactive,
                &m_gameScreen
            )
        );
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

void Playing::onTextEntered(const sf::Event& event) {
    if ('\r' == event.text.unicode) {
        if (!m_isEnterKeyPressed) {
            m_gameScreen.pushEvent(::CustomEvent(
                &m_gameScreen,
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
            m_gameScreen.pushEvent(
                ::CustomEvent(
                    &m_gameScreen,
                    CustomEvent::EscapeKeyPressed,
                    &m_gameScreen
                )
            );
            m_isEscapeKeyPressed = true;
        }
    } else if (m_isTypingMessage) {
        // Forward the event to the chatbox.
        m_chatbox->handleEvent(event);
    }
}

} // namespace GameScreenState
} // namespace State
