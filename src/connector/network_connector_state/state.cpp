#include <dummy/server/response/response.hpp>

#include "connector/network_connector.hpp"
#include "connector/network_connector_state/state.hpp"

namespace Connector {
namespace NetworkConnectorState {

State::State(NetworkConnector& networkConnector)
    : m_networkConnector(networkConnector)
{

}

} // namespace NetworkConnectorState
} // namespace Connector

