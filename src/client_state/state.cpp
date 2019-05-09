#include "client_state/state.hpp"
#include "client.hpp"

namespace ClientState
{

State::State(::Client& client) : m_client(client) {}

} // namespace ClientState
