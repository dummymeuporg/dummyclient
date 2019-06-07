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

void
NetworkConnector::sendCommand(const Dummy::Server::Command::Command& command) {
    // XXX: convert the command to an outgoing packet, then send it
    // through network
    m_state->sendCommand(command);
}

std::unique_ptr<const Dummy::Server::Response::Response>
NetworkConnector::getResponse() {
    // XXX: read packet through network then build a response
    return nullptr;
}

void NetworkConnector::sendPacket(const Dummy::Protocol::OutgoingPacket& pkt) {
    m_socket.send(pkt.buffer(), pkt.size());
}


} // namespace Connector
