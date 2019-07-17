#include "server/command/set_position.hpp"
#include "client.hpp"
#include "map_view.hpp"
#include "graphics/player.hpp"

namespace Graphics {

Player::Player(const ::MapView& mapView,
        ::Client& client,
        const std::string& chipset,
        const std::string& name,
        std::size_t x, std::size_t y,
        std::size_t scaleFactor,
        Direction direction)
    : Living(mapView, chipset, name, 24, 32, x, y, scaleFactor, direction),
    m_client(client)
{
}


void Player::tick() {
    if (m_movingClock.getElapsedTime().asMilliseconds() >= 16 - m_velocity)
    {
        _move(m_xMovement, m_yMovement);
        m_movingClock.restart();
    }
}

std::pair<std::uint16_t, std::uint16_t>
    Player::_translateCoordsToServ(
            std::uint16_t x,
            std::uint16_t y
            ) {
        return std::pair<std::uint16_t, std::uint16_t>(
                x / (8 * m_scaleFactor),
                y / (8 * m_scaleFactor)
                );
    }


void Player::_move(int xVector, int yVector) {
    std::pair<std::uint16_t, std::uint16_t> servCoords = 
        _translateCoordsToServ(m_x, m_y);
    auto tmpCoords(servCoords);
    auto floor(m_client.character()->floor());

    if (xVector == 1) {
        std::size_t edge(
                m_mapView.width() * 16 * m_scaleFactor
                - 16 * m_scaleFactor - m_scaleFactor
                );
        /* Cancel the movement if out of bounds */
        if (m_x == edge) {
            xVector = 0;
        } else {
            /* Moving towards right */
            tmpCoords = std::move(
                _translateCoordsToServ(
                    m_x
                    + 16 * m_scaleFactor
                    + m_scaleFactor,
                    m_y
                    )
                );
            if (m_mapView.blocksAt(floor, tmpCoords.first, tmpCoords.second))
            {
                xVector = 0; /* Cancel the movement */
            }
        }
    }
    else if (xVector == -1) {
        /* Cancel the movement if out of bounds */
        if (m_x == 0) {
            xVector = 0;
        }
        else {
            /* Moving towards left */
            tmpCoords = std::move(
                    _translateCoordsToServ(
                        m_x - m_scaleFactor,
                        m_y
                        )
                    );
            if (m_mapView.blocksAt(floor, tmpCoords.first, tmpCoords.second))
            {
                xVector = 0; /* Cancel the movement */
            }
        }
    }

    if (yVector == 1) {
        std::size_t edge(
                m_mapView.height() * 16 * m_scaleFactor
                - 8 * m_scaleFactor - m_scaleFactor
                );
        /* Cancel the movement if out of bounds */
        if (m_y == edge) {
            yVector = 0;
        }
        else {
            /* Moving towards bottom */
            tmpCoords = std::move(
                    _translateCoordsToServ(
                        m_x,
                        m_y
                        + 8 * m_scaleFactor
                        + m_scaleFactor
                        )
                    );
            if (m_mapView.blocksAt(floor, tmpCoords.first, tmpCoords.second) ||
                    m_mapView.blocksAt(floor,
                                       tmpCoords.first + 1,
                                       tmpCoords.second))
            {
                yVector = 0; /* Cancel the movement */
            }
        }
    }
    else if (yVector == -1) {
        /* Cancel the movement if out of bounds */
        if (m_y == 0) {
            yVector = 0;
        }
        else {
            /* Moving towards top */
            tmpCoords = std::move(
                    _translateCoordsToServ(
                        m_x,
                        m_y - m_scaleFactor
                        )
                    );

            if (m_mapView.blocksAt(floor, tmpCoords.first, tmpCoords.second) ||
                    m_mapView.blocksAt(floor, tmpCoords.first + 1,
                        tmpCoords.second))
            {
                yVector = 0; /* Cancel the movement */
            }
        }
    }

    /* From here the vectors have been cleaned. Update position. */
    m_x += xVector * m_scaleFactor;
    m_y += yVector * m_scaleFactor;

    std::pair<std::uint16_t, std::uint16_t> newCoords(
        _translateCoordsToServ(m_x, m_y)
    );
    if (servCoords != newCoords) {
        std::cerr << "Update coords to server! " <<
            newCoords.first << ", " << newCoords.second << std::endl;
        m_client.sendCommand(
            Dummy::Server::Command::SetPosition(newCoords.first,
                newCoords.second)
        );
    }
}

} // namespace Graphics
