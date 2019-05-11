#include <cstring>
#include <iostream>

#include "client.hpp"

Client::Client(const Credentials&& credentials)
    : m_packetSize(0), m_credentials(std::move(credentials)), m_state(nullptr),
      m_screen(nullptr)
{
}

void Client::connect(const char* host, unsigned short port) {
    if(sf::Socket::Status::Done != m_socket.connect(host, port))
    {
        throw ConnectionError();
    }
    m_socket.setBlocking(false);

    m_state = std::make_shared<ClientState::InitialState>(*this); 
    m_state->resume();
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
    std::cerr << "Packet size: " << m_packetSize << std::endl;
    std::cerr << "ReceivedBytes: " << receivedBytes << std::endl;
    if (m_packetSize == receivedBytes) {
        // Everything is fine. Reset the packet size and handle the data.
        std::cerr << "I got data! " << buffer.size() << std::endl;
        m_state->onRead(buffer);
        m_packetSize = 0;
    } else {
        std::cerr << "Houston, I don't know how to handle this error."
            << std::endl;
        ::exit(-1);
    }
}

void Client::changeState(std::shared_ptr<ClientState::State> state) {
    m_state = state;
    m_state->resume();
}

void Client::setScreen(std::shared_ptr<Screen::Screen> screen) {
    m_screen = screen;
}

void Client::update() {
    m_screen->notify();
}
