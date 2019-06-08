#include <cmath>
#include <iostream>

#include <boost/range/irange.hpp>

#include "client.hpp"
#include "game.hpp"
#include "graphics/living.hpp"
#include "graphics/living_state/standing_state.hpp"
#include "graphics/living_state/walking_state.hpp"

#include "screen/game_screen.hpp"

namespace Screen {

GameScreen::GameScreen(
    ::Game& game,
    ::Client& client,
    std::unique_ptr<::MapView> mapView
)
    : UIScreen(game, client), m_mapView(std::move(mapView)),
      m_camera(m_player.x() + 12 * m_game.scaleFactor(),
               m_player.y() + 16 * m_game.scaleFactor()),
      m_player(
          *m_mapView,
          m_client,
          m_client.character()->skin(),
          m_client.character()->name(),
          m_client.character()->position().first,
          m_client.character()->position().second,
          game.scaleFactor(),
          m_client.character()->direction()
      ),
      m_isArrowPressed(false),
      m_direction(sf::Keyboard::Unknown),
	  m_characterDirection(DIRECTION_NONE),
	  m_isMoving(false)
{
    m_player.setX(
        m_client.character()->position().first * 8 * m_game.scaleFactor());
    m_player.setY(
        m_client.character()->position().second * 8 * m_game.scaleFactor()
    );
}

GameScreen::~GameScreen() {
}

void GameScreen::loaded() {
    m_client.ping();
    m_pingClock.restart();
    m_syncLivingsClock.restart();
}


/*
void GameScreen::syncWithModel(std::shared_ptr<Model::PlayingModel> model) {
    const std::pair<std::uint16_t, std::uint16_t>& position(
        m_client.pixelPosition()
    );
    // Synchronize local livings with the model
    std::vector<std::string> removal;
    for (const auto [name, living]: m_livings) {
        if (model->livings().find(name) == std::end(model->livings())) {
            removal.push_back(name);
        }
    }

    std::for_each(removal.begin(),
                  removal.end(),
                  [this](const std::string& name) {
                       m_livings.erase(name);
                  }
    );

    for(const auto [name, living]: model->livings()) {
        if (m_livings.find(name) == std::end(m_livings)) {
            m_livings[name] = std::make_shared<Graphics::Living>(*living);
            m_livings[name]->setPixelPosition(
                m_livings[name]->x() * 8 * m_game.scaleFactor(),
                m_livings[name]->y() * 8 * m_game.scaleFactor()
            );
            living->setPixelPosition(
                living->x() * 8 * m_game.scaleFactor(),
                living->y() * 8 * m_game.scaleFactor()
            );
        } else {
            // If the living already exists, check the position and
            // set the walking state if needed.

            if (m_livings[name]->x() != living->x() ||
                m_livings[name]->y() != living->y())
            {
                // Need to move.
                // Update the model pixel pos.
                living->setPixelPosition(
                    living->x() * 8 * m_game.scaleFactor(),
                    living->y() * 8 * m_game.scaleFactor()
                );
                
            }
            // Animate the charater.
            m_livings[name]->moveTowards(
                living->pixelX(), living->pixelY()
            );
        }
    }
}
*/

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
        _onKeyPressed(event);
        break;
    case sf::Event::KeyReleased:
        _onKeyReleased(event);
        break;
    default:
        break;
    }
}

void GameScreen::_onArrowReleased() {
	
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

	//m_client.move(xVector, yVector, *m_mapView);

    /*
    m_camera.setCenter(
        m_client.pixelPosition().first + 12 * m_game.scaleFactor(),
        m_client.pixelPosition().second + 16 * m_game.scaleFactor()
    );
    */
    
    m_camera.setCenter(
        m_player.x() + 12 * m_game.scaleFactor(),
        m_player.y() + 16 * m_game.scaleFactor()
    );
}

void GameScreen::_onKeyPressed(const sf::Event& event) {
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

void GameScreen::_onKeyReleased(const sf::Event& event) {
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
}

void GameScreen::_drawLayer(::Sprites& sprites) {
    const sf::Vector2u& windowSize(
        m_game.window().getSize()
    );
    std::int16_t x(
        static_cast<int>(m_camera.centerX()) / (16 * m_game.scaleFactor())
    );

    std::uint16_t y(
        static_cast<int>(m_camera.centerY()) / (16 * m_game.scaleFactor())
    );

    std::uint16_t deltaX(
        (m_game.width() / (16 * m_game.scaleFactor() * 2)) + 2
    );


    std::uint16_t deltaY(
        (m_game.height() / (16 * m_game.scaleFactor() * 2)) + 2
    );

    std::int16_t xStart(std::max(0, static_cast<int>(x - deltaX))),
                xEnd(std::min(static_cast<uint16_t>(x + deltaX),
                              m_mapView->width())),
                yStart(std::max(0, static_cast<int>(y - deltaY))),
                yEnd(std::min(static_cast<uint16_t>(y + deltaY),
                              m_mapView->height()));
    for(const auto x: boost::irange(xStart, xEnd)) {
        for (const auto y: boost::irange(yStart, yEnd)) {
            std::size_t index = y * m_mapView->width() + x;
            sf::Sprite& sprite = sprites.at(index);
            int windowX = ((x * 16 * m_game.scaleFactor()))
                + 4 * m_game.scaleFactor() +
                ((windowSize.x / 2) - static_cast<int>(m_camera.centerX()));
            int windowY = ((y * 16 * m_game.scaleFactor()))
                + 24 * m_game.scaleFactor() +
                ((windowSize.y / 2) - static_cast<int>(m_camera.centerY()));
            sprite.setPosition(sf::Vector2f(windowX, windowY));
        }
    }

    // Draw for real
    for(const auto x: boost::irange(xStart, xEnd)) {
        for (const auto y: boost::irange(yStart, yEnd)) {
            std::size_t index = y * m_mapView->width() + x;
            sf::Sprite& sprite = sprites.at(index);
            m_game.window().draw(sprite);
        }
    }
}

void GameScreen::_drawCharacter() {
    m_player.draw(m_game.window(), m_camera);
}

void GameScreen::_drawLivings() {
    for (auto [name, living]: m_livings) {
        living->draw(m_game.window(), m_camera);
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

/*
void GameScreen::_syncLivings() {
    std::shared_ptr<Model::PlayingModel> model =
        std::dynamic_pointer_cast<Model::PlayingModel>(m_model);
    for(auto [name, living]: m_livings) {
        if (model->livings().find(name) != std::end(model->livings())) {
            std::shared_ptr<const Graphics::Living> modelLiving =
                model->getLiving(name);

            int dstPixelX = modelLiving->pixelX();
            int dstPixelY = modelLiving->pixelY();

            // Update pixel position.
            if (living->pixelX() != dstPixelX) {
                living->setPixelX(
                    living->pixelX() + 2 * (living->pixelX() < dstPixelX) - 1
                );
            }
            if (living->pixelY() != dstPixelY) {
                living->setPixelY(
                    living->pixelY() + 2 * (living->pixelY() < dstPixelY) - 1
                );
            }

            // If the pixel positions are equal, sync server positions.
            if (living->pixelX() == dstPixelX &&
                living->pixelY() == dstPixelY)
            {
                // Sync server position.
                living->setX(modelLiving->x());
                living->setY(modelLiving->y());
            }
        }
    }
}
*/
void GameScreen::tick() {
	/*
	std::cerr << m_client.serverPosition().first <<
		", " << m_client.serverPosition().second << std::endl;
		*/
    m_player.tick();
    if (m_pingClock.getElapsedTime().asMilliseconds() >= 100) {
        //m_client.ping();
        m_pingClock.restart();
    }
    if (m_syncLivingsClock.getElapsedTime().asMicroseconds() >= 2000) {
		//_syncLivings();
        m_syncLivingsClock.restart();
    }

    if (!m_isArrowPressed && m_direction != sf::Keyboard::Unknown) {
        _onArrowPressed();
        m_tickMove.restart();
    } else {
        if (m_tickMove.getElapsedTime().asMicroseconds() >= 1700) {
            _moveCharacter(m_direction);
            m_tickMove.restart();
        }
    }
}


void GameScreen::onResponse(
    const Dummy::Server::Response::Response& response
) {
    response.accept(*this);
}

} // namespace Screen
