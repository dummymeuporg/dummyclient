#include <cstring>
#include <iostream>

#include "connector/connector.hpp"

#include "game.hpp"
#include "map_view.hpp"
#include "client.hpp"

Client::Client(Connector::Connector& connector,
               ::Game& game, const Credentials&& credentials)
    : m_connector(connector), m_game(game),
      m_packetSize(0),
      m_currentScreen(nullptr),
      m_credentials(std::move(credentials)),
      m_character(nullptr)
{
}

void Client::checkResponse() {
    std::unique_ptr<const Dummy::Server::Response::Response> response =
        std::move(m_connector.getResponse());

    if (nullptr != response && m_currentScreen != nullptr) {
        m_currentScreen->onResponse(*response);
    }
}

void Client::connect(const char* host, unsigned short port) {
    if(sf::Socket::Status::Done != m_socket.connect(host, port))
    {
        throw ConnectionError();
    }
    m_socket.setBlocking(false);
}

void Client::checkData() {
    sf::Socket::Status status;
    std::size_t receivedBytes;
    if (m_packetSize == 0) {
        // Read size of incoming packet.
        status = m_socket.receive(reinterpret_cast<void*>(&m_packetSize),
                                  sizeof(std::uint16_t),
                                  receivedBytes);

        if(sf::Socket::Status::NotReady == status) {
            return; // Try again.
        }
    }

    // From here, packetSize should have been set.
    std::vector<std::uint8_t> buffer(m_packetSize);
    status = m_socket.receive(reinterpret_cast<void*>(buffer.data()),
                              m_packetSize,
                              receivedBytes);
    if (m_packetSize == receivedBytes) {
        // Everything is fine. Reset the packet size and handle the data.
        Dummy::Protocol::IncomingPacket pkt(buffer);
        //m_state->onRead(pkt);
        m_packetSize = 0;
    } else {
        std::cerr << "Houston, I don't know how to handle this error."
            << std::endl;
        ::exit(-1);
    }
}

void Client::send(const std::uint8_t* data, std::size_t size) {
    m_socket.send(data, size);
}

void Client::send(const Dummy::Protocol::OutgoingPacket& packet) {
    m_socket.send(packet.buffer(), packet.size());
}

void Client::setCharacter(std::shared_ptr<Dummy::Core::Character> character) {
    m_character = character;

    m_pixelPosition.first = character->position().first
        * 8 * m_game.scaleFactor();
    m_pixelPosition.second = character->position().second
        * 8 * m_game.scaleFactor();
    
    m_serverPosition.first = character->position().first;
    m_serverPosition.second = character->position().second;
}

void Client::move(int xVector, int yVector, const MapView& mapView) {
	std::pair<std::uint16_t, std::uint16_t> servCoords;

	if (xVector == 1) {
        std::size_t edge(
            mapView.width() * 16 * m_game.scaleFactor()
            - 16 * m_game.scaleFactor() - 1
        );
		/* Cancel the movement if out of bounds */
		if (m_pixelPosition.first == edge) {
			xVector = 0;
		} else {
			/* Moving towards right */
			servCoords = std::move(
				_translateCoordsToServ(
					m_pixelPosition.first
                    + 16 * m_game.scaleFactor()
                    + 1,
					m_pixelPosition.second
				)
			);
			if (mapView.blocksAt(servCoords.first, servCoords.second))
			{
				xVector = 0; /* Cancel the movement */
			}
		}
	}
	else if (xVector == -1) {
		/* Cancel the movement if out of bounds */
		if (m_pixelPosition.first == 0) {
			xVector = 0;
		}
		else {
			/* Moving towards left */
			servCoords = std::move(
				_translateCoordsToServ(
					m_pixelPosition.first - 1,
					m_pixelPosition.second
				)
			);
			if (mapView.blocksAt(servCoords.first, servCoords.second))
			{
				xVector = 0; /* Cancel the movement */
			}
		}
	}

	if (yVector == 1) {
        std::size_t edge(
            mapView.width() * 16 * m_game.scaleFactor()
            - 8 * m_game.scaleFactor() - 1
        );
		/* Cancel the movement if out of bounds */
		if (m_pixelPosition.second == edge) {
			yVector = 0;
		}
		else {
			/* Moving towards bottom */
			servCoords = std::move(
				_translateCoordsToServ(
					m_pixelPosition.first,
					m_pixelPosition.second
                    + 8 * m_game.scaleFactor()
                    + 1
				)
			);
			if (mapView.blocksAt(servCoords.first, servCoords.second) ||
				mapView.blocksAt(servCoords.first + 1, servCoords.second))
			{
				yVector = 0; /* Cancel the movement */
			}
		}
	}
	else if (yVector == -1) {
		/* Cancel the movement if out of bounds */
		if (m_pixelPosition.second == 0) {
			yVector = 0;
		}
		else {
			/* Moving towards top */
			servCoords = std::move(
				_translateCoordsToServ(
					m_pixelPosition.first,
					m_pixelPosition.second - 1
				)
			);

			if (mapView.blocksAt(servCoords.first, servCoords.second) ||
				mapView.blocksAt(servCoords.first + 1, servCoords.second))
			{
				yVector = 0; /* Cancel the movement */
			}
		}
	}

	/* From here the vectors has been cleaned. Update position. */
	m_pixelPosition.first += xVector;
	m_pixelPosition.second += yVector;

	servCoords = std::move(
		_translateCoordsToServ(
			m_pixelPosition.first,
			m_pixelPosition.second
		)
	);

	_updateServerPosition(servCoords);
}

std::pair<std::uint16_t, std::uint16_t>
Client::_translateCoordsToServ(
    std::uint16_t x,
    std::uint16_t y
) {
    return std::pair<std::uint16_t, std::uint16_t>(
        x / (8 * m_game.scaleFactor()),
        y / (8 * m_game.scaleFactor())
    );
}

void Client::ping() {
    Dummy::Protocol::OutgoingPacket pkt;
    std::uint16_t command = 2; /* Ping. */
    pkt << command;
    send(pkt);
}

void Client::_updateServerPosition(
    const std::pair<std::uint16_t, std::uint16_t>& position
) {
    if (position != m_serverPosition) {
        Dummy::Protocol::OutgoingPacket pkt;
        std::uint16_t command = 1; /* Move */
        pkt << command << position.first << position.second;
        std::cerr << "Update position to " << position.first << ","
            << position.second << std::endl;
        send(pkt);
        m_serverPosition = position;
    }
}

void Client::sendCommand(const Dummy::Server::Command::Command& command) {
    m_connector.sendCommand(command);
}

void Client::setScreen(std::shared_ptr<Screen::Screen> screen,
                       bool savePreviousScreen)
{
    if (savePreviousScreen && m_currentScreen != nullptr) {
        m_previousScreens.push_back(m_currentScreen);
    }

    m_currentScreen = screen;
    m_currentScreen->loaded();
}

void Client::returnToPreviousScreen() {
    if (m_previousScreens.size() > 0) {
        m_currentScreen = m_previousScreens.back();
        m_previousScreens.pop_back();
        m_currentScreen->returned();
    }
}
