#pragma once

#include <exception>
#include <memory>

#include <SFML/Network.hpp>

#include "client_state/initial_state.hpp"
#include "credentials.hpp"
#include "screen/screen.hpp"

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
    Client(::Game&, const Credentials&&);

    const Credentials& credentials() const {
        return m_credentials;
    }

    sf::TcpSocket& socket() {
        return m_socket;
    }

    void checkData();
    void connect(const char* host, unsigned short port);
    void authenticate();
    void changeState(std::shared_ptr<ClientState::State>);
    void update();

    ::Game& game() {
        return m_game;
    }

    // Model accessors
    const std::vector<void*>& characters() const {
        return m_characters;
    }

    const std::string& account() const {
        return m_account;
    }

    void setAccount(std::string account) {
        m_account = std::move(account);
    }

private:
    ::Game& m_game;
    sf::TcpSocket m_socket;
    std::uint16_t m_packetSize;
    Credentials m_credentials;
    std::shared_ptr<ClientState::State> m_state;

    // Model
    std::string m_account;
    std::vector<void*> m_characters;
};
