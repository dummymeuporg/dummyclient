#pragma once

#include <exception>

#include <SFML/Network.hpp>

#include "credentials.hpp"

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
