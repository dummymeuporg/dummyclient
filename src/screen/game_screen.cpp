#include <iostream>

#include <boost/range/irange.hpp>

#include "client.hpp"
#include "game.hpp"
#include "graphics/living.hpp"
#include "graphics/living_state/standing_state.hpp"
#include "graphics/living_state/walking_state.hpp"
#include "model/playing_model.hpp"

#include "screen/game_screen.hpp"

namespace Screen {

GameScreen::GameScreen(
    ::Game& game,
    ::Client& client,
    std::unique_ptr<::MapView> mapView
)
    : UIScreen(game, client), m_mapView(std::move(mapView)),
      m_originX((game.width() / 2) - 48),
      m_originY((game.height() / 2) - 64),
      m_player(
          m_client,
          m_client.character()->skin(),
          m_client.character()->name(),
          m_originX,
          m_originY,
          m_client.character()->direction()
      ),
      m_isArrowPressed(false),
      m_direction(sf::Keyboard::Unknown)
{
}

void GameScreen::loaded() {
    m_client.ping();
    m_pingClock.restart();
}

void GameScreen::notify() {
    std::shared_ptr<Model::PlayingModel> model =
        std::dynamic_pointer_cast<Model::PlayingModel>(m_model);

    if (model != nullptr) {
        std::cerr << "[GameScreen] Updates." << std::endl;


        // Synchronize local livings with the model
        for (const auto [name, living]: m_livings) {
            if (model->livings().find(name) == std::end(model->livings())) {
                std::cerr << "Bye bye " << name << std::endl;
                m_livings.erase(name);
            }
        }

        for(const auto [name, living]: model->livings()) {
            std::cerr << name << " at "
                << living->x() << ", " << living->y() << std::endl;
            if (m_livings.find(name) == std::end(m_livings)) {
                m_livings[name] = std::make_shared<Graphics::Living>(*living);
                std::cerr << "New living at " << m_livings[name]->x() << ", "
                    << m_livings[name]->y() << std::endl;
            } else {
                // If the living already exists, check the position and
                // set the walking state if needed.
                std::cerr << "Move living at " << living->x() << ", "
                    << living->y() << std::endl;
                m_livings[name]->moveTowards(living->x(), living->y());
            }
        }
    }
        
}

void GameScreen::handleCustomEvent(const ::CustomEvent& event) {
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
        //_onKeyPressed(event);
        break;
    case sf::Event::KeyReleased:
        //_onKeyReleased(event);
        break;
    default:
        break;
    }
}

void GameScreen::_onArrowReleased() {
    if (m_isArrowPressed) {
        pushEvent(
            CustomEvent(
                reinterpret_cast<void*>(shared_from_this().get()),
                CustomEvent::MovementInactive,
                reinterpret_cast<void*>(shared_from_this().get())
            )
        );
        m_isArrowPressed = false;
    }
}

void GameScreen::_onArrowPressed() {
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

void GameScreen::_moveCharacter(sf::Keyboard::Key key) {
    switch(key) {
    case sf::Keyboard::Up:
        m_player.setDirection(Dummy::Core::Character::Direction::UP);
        m_client.moveUp(*m_mapView);
        break;
    case sf::Keyboard::Right:
        m_player.setDirection(Dummy::Core::Character::Direction::RIGHT);
        m_client.moveRight(*m_mapView);
        break;
    case sf::Keyboard::Down:
        m_player.setDirection(Dummy::Core::Character::Direction::DOWN);
        m_client.moveDown(*m_mapView); 
        break;
    case sf::Keyboard::Left:
        m_player.setDirection(Dummy::Core::Character::Direction::LEFT);
        m_client.moveLeft(*m_mapView);
        break;
    default:
        break;
    }
}

void GameScreen::_onKeyPressed(const sf::Event& event) {
}

void GameScreen::_onKeyReleased(const sf::Event& event) {
    switch(event.key.code) {
    case sf::Keyboard::Up:
    case sf::Keyboard::Right:
    case sf::Keyboard::Down:
    case sf::Keyboard::Left:
        _onArrowReleased();
        break;
    default:
        break;
    }

}

void GameScreen::_drawLayer(::Sprites& sprites) {
    const std::pair<std::uint16_t, std::uint16_t>& position(
        m_client.pixelPosition()
    );
    std::int16_t x(position.first / 64), y(position.second / 64);
    std::int16_t xStart(std::max(0, x - 12)),
                xEnd(std::min(static_cast<uint16_t>(x + 12),
                              m_mapView->width())),
                yStart(std::max(0, y - 8)),
                yEnd(std::min(static_cast<uint16_t>(y + 8),
                              m_mapView->height()));
    for(const auto x: boost::irange(xStart, xEnd)) {
        for (const auto y: boost::irange(yStart, yEnd)) {
            std::size_t index = y * m_mapView->width() + x;
            sf::Sprite& sprite = sprites.at(index);
            sprite.setScale(4, 4);
            sprite.setPosition(
                sf::Vector2f(
                    m_originX + ((x * 64) - position.first + 16),
                    m_originY + ((y * 64) - position.second + 96)
                )
            );
            m_game.window().draw(sprite);
        }
    }
}

void GameScreen::_drawCharacter() {
    m_player.setPixelPosition(m_originX, m_originY);
    m_player.draw(m_game.window());
}

void GameScreen::_drawLivings() {
    const std::pair<std::uint16_t, std::uint16_t>& position(
        m_client.pixelPosition()
    );
    for (auto [name, living]: m_livings) {
        // translate pos according to the player
        living->setPixelPosition(
            m_originX + living->x() * 32 - position.first,
            m_originY + living->y() * 32 - position.second
        );
        living->draw(m_game.window());
    }
}

void GameScreen::draw() {
    // Draw the map
    _drawLayer(m_mapView->firstLayerSprites());
    _drawLayer(m_mapView->secondLayerSprites());
    _drawLivings();
    _drawCharacter();
    _drawLayer(m_mapView->thirdLayerSprites());
    _drawLayer(m_mapView->fourthLayerSprites());
    // Draw widgets (HUD) if needed.
    UIScreen::draw();
}

void GameScreen::_syncLivings() {
    for(const auto [name, living]: m_livings) {
    }
}

void GameScreen::tick() {

    if (m_pingClock.getElapsedTime().asMilliseconds() >= 300) {
        std::cerr << "Ping! " << m_client.serverPosition().first << ", "
            << m_client.serverPosition().second << std::endl;
        m_client.ping();
        m_pingClock.restart();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_direction = sf::Keyboard::Up;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_direction = sf::Keyboard::Right;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_direction = sf::Keyboard::Down;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_direction = sf::Keyboard::Left;
    } else {
        m_direction = sf::Keyboard::Unknown;
    }

    if (m_direction == sf::Keyboard::Unknown) {
        if (m_isArrowPressed) {
            _onArrowReleased();
        }
        return;
    }

    if (!m_isArrowPressed && m_direction != sf::Keyboard::Unknown) {
        _onArrowPressed();
        m_tickMove.restart();
    } else {
        if (m_tickMove.getElapsedTime().asMicroseconds() >= 1700) {
            _moveCharacter(m_direction);
            _syncLivings();
            m_tickMove.restart();
        }
    }
}

} // namespace Screen
