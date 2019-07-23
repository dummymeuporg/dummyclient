#include "server/command/ping.hpp"
#include "server/command/set_position.hpp"
#include "camera.hpp"
#include "client.hpp"
#include "map_view.hpp"
#include "graphics/player.hpp"

namespace Graphics {

Player::Player(const ::MapView& mapView,
        ::Client& client,
        const std::string& chipset,
        const std::string& name,
        std::int32_t x,
        std::int32_t y,
        std::uint8_t floor,
        std::uint16_t scaleFactor,
        Direction direction)
    : Living(mapView,
             chipset,
             name,
             24,
             32,
             x,
             y,
             floor,
             scaleFactor,
             direction),
    m_client(client)
{
    m_updatePosClock.restart();
    m_serverPosition = translateCoordsToServ(m_x, m_y);
}

void Player::updatePosition() {
    auto delta = computeDistance();
    int xStep(delta.first != 0 ? (2 * (delta.first > 0) - 1) : 0);
    int yStep(delta.second != 0 ? (2 * (delta.second > 0) - 1) : 0);
    // ...
    if (xStep > 0) {
        moveTowardsRight(delta.first);
    } else if (xStep < 0) {
        moveTowardsLeft(delta.first);
    }

    if (yStep > 0) {
        moveTowardsBottom(delta.second);
    } else if (yStep < 0) {
        moveTowardsTop(delta.second);
    }
}


void Player::tick() {
    // XXX: update position and read the others each 333 ms?
    if (m_updatePosClock.getElapsedTime().asMilliseconds() >= 333) {
        std::cerr << "TICK" << std::endl;
        m_client.sendCommand(Dummy::Server::Command::Ping());

        // Update position if needed
        auto newPosition = translateCoordsToServ(m_x, m_y);
        if (newPosition != m_serverPosition) {
            std::cerr << "UPDATE POS." << std::endl;
            m_client.sendCommand(
                Dummy::Server::Command::SetPosition(newPosition.first,
                                                    newPosition.second)
            );
            m_serverPosition = newPosition;
        }
        m_updatePosClock.restart();
    }
}

std::pair<std::uint16_t, std::uint16_t>
Player::translateCoordsToServ(
        std::int32_t x,
        std::int32_t y
    ) {
    return std::pair<std::uint16_t, std::uint16_t>(
        x / (8 * m_scaleFactor),
        y / (8 * m_scaleFactor)
    );
}

bool Player::blocksLeft() const {
    auto floor(m_client.character()->floor());
    return m_x == 0 || m_mapView.blocksAt(floor, m_x - 1, m_y);
}

bool Player::blocksRight() const {
    auto floor(m_client.character()->floor());
    return m_x ==
        ((m_mapView.width() * 16 * m_scaleFactor) - (16 * m_scaleFactor)) ||
            m_mapView.blocksAt(
                floor,
                m_x + (16 * m_scaleFactor) + 1,
                m_y
            );
}

bool Player::blocksTop() const {
    auto floor(m_client.character()->floor());

    // The character is two "blocking squares" wide.
    return m_y == 0 || m_mapView.blocksAt(floor, m_x, m_y - 1) ||
        m_mapView.blocksAt(floor, m_x + (8 * m_scaleFactor), m_y - 1);
}

bool Player::blocksBottom() const {
    auto floor(m_client.character()->floor());
    return m_y == ((m_mapView.height() * 16 * m_scaleFactor) -
        (8 * m_scaleFactor)) ||
        m_mapView.blocksAt(floor, m_x, m_y + (8 * m_scaleFactor)) ||
        m_mapView.blocksAt(floor,
                           m_x + (8 * m_scaleFactor),
                           m_y + (8 * m_scaleFactor));
}

void Player::moveTowardsRight(int delta) {
    int i = 0, step = 2 * (delta > 0) - 1;
    while (!blocksRight() && i != delta) {
        m_x += step;
        i += step;
    }
}

void Player::moveTowardsLeft(int delta) {
    int i = 0, step = 2 * (delta > 0) - 1;
    while (!blocksLeft() && i != delta) {
        m_x += step;
        i += step;
    }

}

void Player::moveTowardsTop(int delta) {
    int i = 0, step = 2 * (delta > 0) - 1;
    while (!blocksTop() && i != delta) {
        m_y += step;
        i += step;
    }
}

void Player::moveTowardsBottom(int delta) {
    int i = 0, step = 2 * (delta > 0) - 1;
    while (!blocksBottom() && i != delta) {
        m_y += step;
        i += step;
    }
}

void Player::draw(sf::RenderWindow& window, const ::Camera& camera) {
    Living::draw(window, camera);
    const sf::Vector2u& windowSize(window.getSize());
    sf::FloatRect textRect = m_displayName.getLocalBounds();
    m_displayName.setOrigin(
        textRect.left + textRect.width / 2.0f,
        textRect.top
    );
    m_displayName.setPosition(
        static_cast<int>(windowSize.x / 2) + m_x - camera.centerX() +
        w() * 1,
        static_cast<int>(windowSize.y / 2) + m_y - camera.centerY() +
        h() * 2
    );
    window.draw(m_displayName);
}


} // namespace Graphics
