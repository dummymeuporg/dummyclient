#include <cstring>
#include <iostream>

#include "client.hpp"

Client::Client(const Credentials& credentials)
    : m_packetSize(0), m_credentials(credentials)
{
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
        std::cerr << buffer.data() << std::endl;
    } else {
        std::cerr << "Houston, I don't know how to handle this error."
            << std::endl;
    }
}

void Client::authenticate()
{
    const std::string& account(m_credentials.account());
    const std::uint8_t* sessionID(m_credentials.sessionID());
    // send account and uuid to the server.
    std::vector<std::uint8_t> buffer(
        sizeof(std::uint16_t) + // holds the size of the packet
        sizeof(std::uint16_t) + // holds the size of the account name
        account.size() + // holds the account
        16 // holds the uuid.
    );
    *(reinterpret_cast<std::uint16_t*>(buffer.data())) =
        buffer.size() - sizeof(std::uint16_t);
    *(reinterpret_cast<std::uint16_t*>(buffer.data()) + 1) =
        account.size();

    // Put the account
    std::copy(account.begin(),
              account.end(),
              buffer.data() + 2 * sizeof(std::uint16_t)
    );

    // Put the session ID
    ::memcpy(buffer.data() + (2 * sizeof(std::uint16_t) + account.size()),
             sessionID,
             16);

    // Send the packet.
    m_socket.send(buffer.data(), buffer.size());

}
