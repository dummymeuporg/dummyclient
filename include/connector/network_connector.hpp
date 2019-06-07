#pragma once

#include <SFML/Network.hpp>
#include "connector/connector.hpp"


namespace Dummy {
namespace Protocol {
class OutgoingPacket;
} // namespace OutgoingPacket
namespace Server {
class GameSession;

namespace Response {
class Response;
} // namespace Response
} // namespace Server
} // namespace Dummy

namespace Connector {

namespace NetworkConnectorState {
class State;
}

class NetworkConnector : public Connector {
public:
    NetworkConnector(const std::string&, unsigned short);
    virtual void sendCommand(const Dummy::Server::Command::Command&) override;

    virtual std::unique_ptr<const Dummy::Server::Response::Response>
    getResponse() override;

    void connect();
    void sendPacket(const Dummy::Protocol::OutgoingPacket&);
    void changeState(std::shared_ptr<NetworkConnectorState::State>);
private:
    std::string m_host;
    unsigned short m_port;
    sf::TcpSocket m_socket;
    std::uint16_t m_packetSize;
    std::shared_ptr<NetworkConnectorState::State> m_state;
};

} // namespace Connector
