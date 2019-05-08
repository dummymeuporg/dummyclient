#pragma once

#include <exception>

#include <SFML/Network.hpp>

#include "credentials.hpp"

class ClientError : public std::exception {

};

class ConnectionError : public ClientError {
public:
    const char* what() const noexcept {
        return "cannot connect to server.";
    }
};

class Client {
public:
    Client(const Credentials&);

    const Credentials& credentials() const {
        return m_credentials;
    }

    void checkData();
    void connect(const char* host, unsigned short port);
    void authenticate();

private:
    sf::TcpSocket m_socket;
    std::uint16_t m_packetSize;
    Credentials m_credentials;
    //std::shared_ptr<ClientState::State> m_state;
};
