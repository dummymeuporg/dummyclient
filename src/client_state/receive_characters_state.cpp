#include "client_state/receive_characters_state.hpp"

namespace ClientState {

ReceiveCharactersState::ReceiveCharactersState(::Client& client)
    : State(client)
{
}

void ReceiveCharactersState::resume() {
    // Nothing to do for now.
    // The client will select the character later on.
}

void ReceiveCharactersState::onRead(const std::vector<std::uint8_t>& buffer) {
    // Here, we will get the server answer once the character has been either
    // created or selected.
}

} // namespace ClientState
