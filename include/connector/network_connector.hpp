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

using CommandPtr = std::shared_ptr<const Dummy::Server::Command::Command>;

class NetworkConnector : public Connector {
public:
    NetworkConnector(const std::string&, unsigned short);
    void start() override;
    void sendCommand(CommandPtr) override;

    void close();

    void sendPacket(const Dummy::Protocol::OutgoingPacket&);
    void changeState(std::shared_ptr<NetworkConnectorState::State>);
    ResponsePtr getResponse() override;
private:
    void connect();
    std::string m_host;
    unsigned short m_port;
    sf::TcpSocket m_socket;
    std::uint16_t m_packetSize;
    std::shared_ptr<NetworkConnectorState::State> m_state;
};

} // namespace Connector
