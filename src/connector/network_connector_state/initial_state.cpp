#include "server/command/command.hpp"
#include "server/response/response.hpp"
#include "connector/network_connector.hpp"
#include "connector/network_connector_state/initial_state.hpp"

namespace Connector {
namespace NetworkConnectorState {

InitialState::InitialState(NetworkConnector& networkConnector)
    : State(networkConnector)
{

}

void
InitialState::sendCommand(
    const Dummy::Server::Command::Command& command
) {

}


std::unique_ptr<const Dummy::Server::Response::Response>
InitialState::getResponse(Dummy::Protocol::IncomingPacket& packet)
{
    return nullptr;
}



} // namespace NetworkConnectorState
} // namespace Connector
