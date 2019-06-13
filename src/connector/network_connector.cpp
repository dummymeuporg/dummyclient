#include <iostream>
#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "server/command/command.hpp"
#include "server/response/response.hpp"
#include "connector/network_connector.hpp"
#include "connector/network_connector_state/initial_state.hpp"

namespace Connector {

NetworkConnector::NetworkConnector(const std::string& host,
                                   unsigned short port)
    : m_host(host), m_port(port), m_packetSize(0),
      m_state(std::make_shared<NetworkConnectorState::InitialState>(*this))
{

}

void NetworkConnector::connect() {
    if (sf::Socket::Status::Done != m_socket.connect(m_host, m_port)) {
        throw ConnectionError();
    }
    m_socket.setBlocking(false);
}

void NetworkConnector::close() {
    m_socket.disconnect();
}

void
NetworkConnector::sendCommand(const Dummy::Server::Command::Command& command) {
    m_state->sendCommand(command);
}


void NetworkConnector::changeState(
    std::shared_ptr<NetworkConnectorState::State> state
) {
    m_state = state;
}

std::unique_ptr<const Dummy::Server::Response::Response>
NetworkConnector::getResponse() {
    sf::Socket::Status status;
    std::size_t receivedBytes;
    if (m_packetSize == 0) {
        // Read size of incoming packet.
        status = m_socket.receive(reinterpret_cast<void*>(&m_packetSize),
                                  sizeof(std::uint16_t),
                                  receivedBytes);

        if (sf::Socket::Status::Disconnected == status) {
            std::cerr << "Error: disconnected." << std::endl;
            ::exit(EXIT_FAILURE);
        } else if(sf::Socket::Status::NotReady == status) {
            return nullptr; // Try again.
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
        m_packetSize = 0;
        return m_state->getResponse(pkt);
    } else {
        std::cerr << "Houston, I don't know how to handle this error."
            << std::endl;
        ::exit(EXIT_FAILURE);
    }

    return nullptr;
}

void NetworkConnector::sendPacket(const Dummy::Protocol::OutgoingPacket& pkt) {
    m_socket.send(pkt.buffer(), pkt.size());
}


} // namespace Connector
