#pragma once

#include <exception>
#include <memory>

#include <SFML/Network.hpp>

#include "core/character.hpp"
#include "protocol/outgoing_packet.hpp"

#include "credentials.hpp"
#include "screen/screen.hpp"

#include "server/command/command.hpp"
#include "server/response/response.hpp"

class ClientError : public std::exception {

};

class ConnectionError : public ClientError {
public:
    virtual const char* what() const noexcept override {
        return "cannot connect to server";
    }
};

class ReceiveError : public ClientError {
public:
    virtual const char* what() const noexcept override {
        return "cannot receive data from server";
    }
};

namespace Connector {
class Connector;
}

class MapView;

class Client {
public:
    Client(Connector::Connector&,
           ::Game&,
           const Credentials&&);

    const Credentials& credentials() const {
        return m_credentials;
    }

    sf::TcpSocket& socket() {
        return m_socket;
    }
    void checkData();
    void checkResponse();
    void connect(const char* host, unsigned short port);
    void authenticate();
    void update();
    void ping();
    void send(const std::uint8_t*, std::size_t);
    void send(const Dummy::Protocol::OutgoingPacket&);

    ::Game& game() {
        return m_game;
    }

    const std::string& account() const {
        return m_credentials.account();
    }

    std::shared_ptr<Dummy::Core::Character> character() const {
        return m_character;
    }

    const std::pair<std::uint16_t, std::uint16_t> pixelPosition() const {
        return m_pixelPosition;
    }

    const std::pair<std::uint16_t, std::uint16_t> serverPosition() const {
        return m_serverPosition;
    }

    void sendCommand(const Dummy::Server::Command::Command&);
    void onResponse(const Dummy::Server::Response::Response&);

	void move(int, int, const MapView&);

    void setCharacter(std::shared_ptr<Dummy::Core::Character>);
    void _updateServerPosition(const std::pair<std::uint16_t, std::uint16_t>&);

    void setScreen(std::shared_ptr<Screen::Screen>, bool = false);
    void returnToPreviousScreen();
    std::shared_ptr<Screen::Screen> screen() {
        return m_currentScreen;
    }

private:
    std::pair<std::uint16_t, std::uint16_t> _translateCoordsToServ(
        std::uint16_t, std::uint16_t);
    Connector::Connector& m_connector;
    ::Game& m_game;
    std::shared_ptr<Screen::Screen> m_currentScreen;
    std::vector<std::shared_ptr<Screen::Screen>> m_previousScreens;
    sf::TcpSocket m_socket;
    std::uint16_t m_packetSize;
    Credentials m_credentials;
    std::shared_ptr<Dummy::Core::Character> m_character;
    std::pair<std::uint16_t, std::uint16_t> m_pixelPosition;
    std::pair<std::uint16_t, std::uint16_t> m_serverPosition;
};
